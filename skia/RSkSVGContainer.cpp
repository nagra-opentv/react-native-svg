
/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <unordered_map>

#include "ReactSkia/RSkThirdPartyFabricComponentsProvider.h"
#include "RSkComponentRNSVGCircle.h"
#include "RSkComponentRNSVGDefs.h"
#include "RSkComponentRNSVGEllipse.h"
#include "RSkComponentRNSVGGroup.h"
#include "RSkComponentRNSVGLine.h"
#include "RSkComponentRNSVGPath.h"
#include "RSkComponentRNSVGRect.h"
#include "RSkComponentRNSVGText.h"
#include "RSkComponentRNSVGTSpan.h"
#include "RSkComponentRNSVGUse.h"
#include "RSkComponentRNSVGSvgView.h"
#include "RSkSVGContainer.h"

#define RNS_LOG_MODE_FOR_CONTAINER RNS_LOG_DEBUG

namespace facebook {
namespace react {

RSkSVGContainer::RSkSVGContainer(const ShadowView &shadowView,
                                 RnsShell::LayerType layerType,
                                 SkSVGTag tag)
    : INHERITED(shadowView,layerType,tag){}

RSkSVGContainer::~RSkSVGContainer() {
  childRSkNodeList_.clear();
  nodeIDMapper_.reset();
}

RSkSVGNode* RSkSVGContainer::getRSKSvgNodeFromComponent(std::shared_ptr<RSkComponent> component) {

  static std::unordered_map<std::string, RSkSVGNode* (*)(std::shared_ptr<RSkComponent>)> s_mapStringValues={
    { "RNSVGView",getRSKSVGNode<RSkComponentRNSVGSvgView>},
    { "RNSVGGroup",getRSKSVGNode<RSkComponentRNSVGGroup>},
    { "RNSVGCircle",getRSKSVGNode<RSkComponentRNSVGCircle>},
    { "RNSVGRect",getRSKSVGNode<RSkComponentRNSVGRect>},
    { "RNSVGEllipse",getRSKSVGNode<RSkComponentRNSVGEllipse>},
    { "RNSVGPath",getRSKSVGNode<RSkComponentRNSVGPath>},
    { "RNSVGLine",getRSKSVGNode<RSkComponentRNSVGLine>},
    { "RNSVGText",getRSKSVGNode<RSkComponentRNSVGText>},
    { "RNSVGTSpan",getRSKSVGNode<RSkComponentRNSVGTSpan>},
    { "RNSVGDefs",getRSKSVGNode<RSkComponentRNSVGDefs>},
    { "RNSVGUse",getRSKSVGNode<RSkComponentRNSVGUse>}
  };

  std::string componentName=component->getComponentData().componentName;

  if(s_mapStringValues.find(componentName.c_str()) != s_mapStringValues.end()) {
    return s_mapStringValues[componentName.c_str()](component);
  } else {
    return nullptr;
  }
}

void RSkSVGContainer::mountChildComponent(
    std::shared_ptr<RSkComponent> childComponent,
    const int index) {

  RNS_LOG_MODE_FOR_CONTAINER("Parent Componet :" << this->getComponentData().componentName<<" holding child :" << childComponent->getComponentData().componentName);

  if(!childComponent || !childComponent.get()) {
    RNS_LOG_ERROR("Invalid child component received");
    return;
  }

  auto node=getRSKSvgNodeFromComponent(childComponent);
  if(node) {
    auto sksvgNode =sk_sp<SkSVGNode>(node);
    RNS_LOG_MODE_FOR_CONTAINER("Child Node type  : "<<(int)node->tag());
    if(!node->nodeName.empty()) {
      RNS_LOG_MODE_FOR_CONTAINER("Child Node has ID : "<<node->nodeName);
      nodeIDMapper_.set(SkString(node->nodeName),sksvgNode);
    }

    // If Child Node is of type of container , Merge it's defMap with it's Parent
    auto nodeContainer=dynamic_cast<RSkSVGContainer *>(node);
    if(nodeContainer) {
      auto mergeFn= [&](SkString keyName,sk_sp<SkSVGNode> *value){
        nodeIDMapper_.set(keyName,*value);
      };
      nodeContainer->nodeIDMapper_.foreach(mergeFn);
    }

    // Insert child RSkSVGNode in to List
    size_t indexAt = std::min((size_t)index, childRSkNodeList_.size());
    RNS_LOG_MODE_FOR_CONTAINER("Insert Child at index : " << indexAt );
    childRSkNodeList_.insert(childRSkNodeList_.begin() + indexAt, sksvgNode);

    //If this parent is SVGView , set itself as Root
    if(this->tag() == SkSVGTag::kSvg) {
      node->setRoot(this);
    }
  }

  RNS_LOG_MODE_FOR_CONTAINER("RSK SVG Def Map Size for component : "<< this->getComponentData().componentName << " : "<<nodeIDMapper_.count());
  RNS_LOG_MODE_FOR_CONTAINER("RSK SVG container Size for the Parent : "<<childRSkNodeList_.size());
}

void RSkSVGContainer::unmountChildComponent(
    std::shared_ptr<RSkComponent> oldChildComponent,
    const int index) {
  RNS_LOG_MODE_FOR_CONTAINER("Parent :"<<getComponentData().componentName<<
                    "recieved unmount for child :" << oldChildComponent->getComponentData().componentName<<
                    "@ index : "<<index);
  if(index >= childRSkNodeList_.size()) {
    RNS_LOG_ERROR("Invalid index passed for remove");
    return;
  }
  // If the respective node has entry In Def ID Mapper , remove it from all teh containers
  auto node=static_cast<RSkSVGNode *>(childRSkNodeList_[index].get());
  if(node && (!node->nodeName.empty())) {
    auto node=dynamic_cast<RSkSVGContainer *>(rootNode_);
    if(node) {
     node->removeDefEntry(node->nodeName);
    }
  }
  childRSkNodeList_.erase(childRSkNodeList_.begin() + index);
}

void RSkSVGContainer::OnPaint(SkCanvas *canvas) {
  RNS_LOG_DEBUG(" Paint for Svg Elements handled via RNSSVG element ");
}

bool RSkSVGContainer::hasChildren() const {
  return !childRSkNodeList_.empty();
}

void RSkSVGContainer::onRender(const SkSVGRenderContext& ctx) const {
  for (int i = 0; i < childRSkNodeList_.size(); ++i) {
    RNS_LOG_MODE_FOR_CONTAINER(" Child Tag : "<<(int)childRSkNodeList_[i]->tag());
    childRSkNodeList_[i]->render(ctx);
  }
}

void RSkSVGContainer::setRoot(RSkSVGNode * rootNode) {

  if(!rootNode) return;

  if(rootNode && (rootNode->tag() == SkSVGTag::kSvg)) {
    rootNode_=rootNode;
    RNS_LOG_MODE_FOR_CONTAINER("setRoot for child :"<<(int)tag());
  }

  for (int i = 0; i < childRSkNodeList_.size(); ++i) {
    RNS_LOG_MODE_FOR_CONTAINER(" setRoot for Child  with Tag : "<<(int)childRSkNodeList_[i]->tag());
    auto node=static_cast<RSkSVGNode *>(childRSkNodeList_[i].get());
    if(node) {
     node->setRoot(rootNode);
    }
  }
}

void RSkSVGContainer::removeDefEntry(std::string key) {

  nodeIDMapper_.remove(SkString(key));//remove from self
  //Remove from children
  for (auto &item: childRSkNodeList_) {
    RNS_LOG_MODE_FOR_CONTAINER(" Erase Entries from Child containers : "<<(int)item->tag());
    auto node=dynamic_cast<RSkSVGContainer *>(item.get());
    if(node) {
     node->removeDefEntry(key);
    }
  }
}

#ifdef ENABLE_SVG_CHILD_HIERARCHY_DEBUG
void RSkSVGContainer::printChildList() {
  for (int i = 0; i < childRSkNodeList_.size(); ++i) {
    RNS_LOG_INFO(" Child Node Tag : "<<(int)childRSkNodeList_[i]->tag());
    auto node=dynamic_cast<RSkSVGContainer *>(childRSkNodeList_[i].get());
    if(node) {
      RNS_LOG_INFO("Child Node is a container");
      node->printChildList();
     }
  }
}
#endif //ENABLE_SVG_CHILD_HIERARCHY_DEBUG

} // namespace react
} // namespace facebook

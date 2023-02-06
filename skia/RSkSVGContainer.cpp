
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
#include "RSkComponentRNSVGUse.h"
#include "RSkComponentRNSVGSvgView.h"
#include "RSkSVGContainer.h"

namespace facebook {
namespace react {

RSkSVGContainer::RSkSVGContainer(const ShadowView &shadowView,
                                                   RnsShell::LayerType layerType,
                                                   SkSVGTag t)
    : INHERITED(shadowView,layerType,t){}

RSkSVGContainer::~RSkSVGContainer() {
  childRSkNodeList_.clear();
  nodeIDMapper_.reset();
}

RSkSVGNode* RSkSVGContainer::getRSkSVGNodeForComponentWithName(std::shared_ptr<RSkComponent> component) {

  static std::unordered_map<std::string, RSkSVGNode* (*)(std::shared_ptr<RSkComponent>)> s_mapStringValues={
    { "RNSVGView",getRSKSVGNodeFor<RSkComponentRNSVGSvgView>},
    { "RNSVGGroup",getRSKSVGNodeFor<RSkComponentRNSVGGroup>},
    { "RNSVGCircle",getRSKSVGNodeFor<RSkComponentRNSVGCircle>},
    { "RNSVGRect",getRSKSVGNodeFor<RSkComponentRNSVGRect>},
    { "RNSVGEllipse",getRSKSVGNodeFor<RSkComponentRNSVGEllipse>},
    { "RNSVGPath",getRSKSVGNodeFor<RSkComponentRNSVGPath>},
    { "RNSVGLine",getRSKSVGNodeFor<RSkComponentRNSVGLine>},
    { "RNSVGDefs",getRSKSVGNodeFor<RSkComponentRNSVGDefs>},
    { "RNSVGUse",getRSKSVGNodeFor<RSkComponentRNSVGUse>}
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

  RNS_LOG_DEBUG("Parent Componet :" << this->getComponentData().componentName<<" holding child :" << childComponent->getComponentData().componentName);

  if(!childComponent || !childComponent.get()) {
    RNS_LOG_ERROR("Invalid child component received");
    return;
  }

  auto node=getRSkSVGNodeForComponentWithName(childComponent);
  if(node) {
    auto sksvgNode =sk_sp<SkSVGNode>(node);
    RNS_LOG_DEBUG("Child Node type  : "<<(int)node->tag());
    if(!node->nodeName.empty()) {
      RNS_LOG_DEBUG("Child Node has ID : "<<node->nodeName);
      nodeIDMapper_.set(SkString(node->nodeName),sksvgNode);
    }

    // If Child Node is of type of container , Merge it's defMap with it's Parent
    auto nodeContainer=GET_DERIVED_OBJECT_FROM(node,RSkSVGContainer);
    if(nodeContainer) {
      auto mergeFn= [&](SkString keyName,sk_sp<SkSVGNode> *value){
        nodeIDMapper_.set(keyName,*value);
      };
      nodeContainer->nodeIDMapper_.foreach(mergeFn);
    }

    // Insert child RSkSVGNode in to List
    size_t indexAt = std::min((size_t)index, childRSkNodeList_.size());
    RNS_LOG_DEBUG("Insert Child at index : " << indexAt );
    childRSkNodeList_.insert(childRSkNodeList_.begin() + indexAt, sksvgNode);
  }

  RNS_LOG_DEBUG("RSK SVG Def Map Size for component : "<< this->getComponentData().componentName << " : "<<nodeIDMapper_.count());
  RNS_LOG_DEBUG("RSK SVG container Size for the Parent : "<<childRSkNodeList_.size());
}

void RSkSVGContainer::unmountChildComponent(
    std::shared_ptr<RSkComponent> oldChildComponent,
    const int index) {
  RNS_LOG_DEBUG("Parent :"<<getComponentData().componentName<<
                "recieved unmount for child :" << oldChildComponent->getComponentData().componentName<<
                "@ index : "<<index);
  if(index >= childRSkNodeList_.size()) {
    RNS_LOG_ERROR("Invalid index passed for remove");
    return;
  }
  // If the respective node has entry In Def ID Mapper , remove there as well
  auto node=GET_DERIVED_OBJECT_FROM(childRSkNodeList_[index].get(),RSkSVGNode);
  if(node && (!node->nodeName.empty())) {
    nodeIDMapper_.remove(SkString(node->nodeName));
  }
  RNS_LOG_DEBUG("Remove Child at index : " << index );
  //TODO : (" Remove Child from Parent def Map As well");
  childRSkNodeList_.erase(childRSkNodeList_.begin() + index);
}

void RSkSVGContainer::OnPaint(SkCanvas *canvas) {
  RNS_LOG_DEBUG(" Paint for Svg Elements handled via RNSSVG element ");
}

bool RSkSVGContainer::hasChildren() const {
  return !childRSkNodeList_.empty();
}

void RSkSVGContainer::onRender(const SkSVGRenderContext& ctx) const {
   RNS_LOG_DEBUG("---Render Childern---");
  for (int i = 0; i < childRSkNodeList_.size(); ++i) {
    RNS_LOG_DEBUG(" Child Tag : "<<(int)childRSkNodeList_[i]->tag());
    childRSkNodeList_[i]->render(ctx);
  }
}

#ifdef ENABLE_SVG_CHILD_HIERARCHY_DEBUG
void RSkSVGContainer::printChildList() {
  for (int i = 0; i < childRSkNodeList_.size(); ++i) {
    RNS_LOG_INFO(" Child Node Tag : "<<(int)childRSkNodeList_[i]->tag());
    auto node=GET_DERIVED_OBJECT_FROM(childRSkNodeList_[i].get(),RSkSVGContainer);
    if(node) {
      RNS_LOG_INFO("Child Node is a container");
      node->printChildList();
     }
  }
}
#endif //ENABLE_SVG_CHILD_HIERARCHY_DEBUG

} // namespace react
} // namespace facebook

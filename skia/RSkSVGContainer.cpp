
/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

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
  rskNodeIDMapper.reset();
}
void RSkSVGContainer::mountChildComponent(
    std::shared_ptr<RSkComponent> childComponent,
    const int index) {

  RNS_LOG_MODE_FOR_CONTAINER("Parent :"<<getComponentData().componentName<<
                    "recieved mount for child :" << childComponent->getComponentData().componentName<<
                    "@ index : "<<index);

  if(!childComponent || !childComponent.get()) {
    RNS_LOG_ERROR("Invalid child component received");
    return;
  }
  /*
                      RSkComponent
                     /
  RSkSVGComponentNode
                     \
                      RSkSVGNode
  */
// Type convert from base class RSkComponent to base class RSkSVGNode
  RSkSVGNode* rskSvgNode=dynamic_cast<RSkSVGComponentNode *>(childComponent.get());
  if(rskSvgNode) {
    RNS_LOG_MODE_FOR_CONTAINER("Child Node type  : "<<(int)rskSvgNode->tag());
    if(!rskSvgNode->svgNodeId.empty()) {
      RNS_LOG_MODE_FOR_CONTAINER("Child Node has ID : "<<rskSvgNode->svgNodeId);
      rskNodeIDMapper.set(SkString(rskSvgNode->svgNodeId),rskSvgNode);
    }

    // If Child Node is of type of container , Merge it's defMap with it's Parent & drop it's own
    auto nodeContainer=dynamic_cast<RSkSVGContainer *>(rskSvgNode);
    if(nodeContainer) {
      auto mergeFn= [&](SkString keyName,RSkSVGNode** value){
        rskNodeIDMapper.set(keyName,*value);
      };
      nodeContainer->rskNodeIDMapper.foreach(mergeFn);
      nodeContainer->rskNodeIDMapper.reset();
    }

    //If this parent is SVGView , set itself as Root
    if(this->tag() == SkSVGTag::kSvg) {
      rskSvgNode->setRoot(this);
    }
  }

  // Insert child RSkSVGNode in to List
  size_t indexAt = std::min((size_t)index, childRSkNodeList_.size());
  RNS_LOG_MODE_FOR_CONTAINER("Insert Child at index : " << indexAt );
  childRSkNodeList_.insert(childRSkNodeList_.begin() + indexAt, rskSvgNode);

  RNS_LOG_MODE_FOR_CONTAINER("RSK SVG Def Map Size for component : "<< this->getComponentData().componentName << " : "<<rskNodeIDMapper.count());
  RNS_LOG_MODE_FOR_CONTAINER("RSK SVG container Size for the Parent : "<<childRSkNodeList_.size());
}

void RSkSVGContainer::unmountChildComponent(
    std::shared_ptr<RSkComponent> oldChildComponent,
    const int index) {
  RNS_LOG_MODE_FOR_CONTAINER("Parent :"<<getComponentData().componentName<<
                    "recieved unmount for child :" << oldChildComponent->getComponentData().componentName<<
                    "@ index : "<<index);

  if(index >= childRSkNodeList_.size()) {
    RNS_LOG_ERROR("Invalid index passed for unmountChildComponent : "<<index);
    return;
  }
  if(childRSkNodeList_[index] == nullptr) {
    RNS_LOG_ERROR("Unmount Called for UnSupported SVG Element : "<<oldChildComponent->getComponentData().componentName);
    return;
  }

  // If the respective node has entry In Def ID Mapper , remove it
  auto node=childRSkNodeList_[index];
  if(node && (!node->svgNodeId.empty())) {
    auto rootNode=dynamic_cast<RSkSVGContainer *>(rootNode_);
    if(rootNode) {
     rootNode->rskNodeIDMapper.remove(SkString(node->svgNodeId));
    }
  }
  childRSkNodeList_.erase(childRSkNodeList_.begin() + index);
}

void RSkSVGContainer::OnPaint(SkCanvas *canvas) {
  RNS_LOG_DEBUG(" Paint for Svg Elements handled via RNSVGView element ");
}

bool RSkSVGContainer::hasChildren() const {
  return !childRSkNodeList_.empty();
}

void RSkSVGContainer::onRender(const SkSVGRenderContext& ctx) const {
  for (int i = 0; i < childRSkNodeList_.size(); ++i) {
    if(childRSkNodeList_[i] != nullptr) {
      RNS_LOG_MODE_FOR_CONTAINER(" Child Tag : "<<(int)childRSkNodeList_[i]->tag());
      childRSkNodeList_[i]->render(ctx);
    }
  }
}

void RSkSVGContainer::setRoot(RSkSVGNode * rootNode) {

  if(!rootNode) return;

  if(rootNode && (rootNode->tag() == SkSVGTag::kSvg)) {
    rootNode_=rootNode;
    RNS_LOG_MODE_FOR_CONTAINER("setRoot for child :"<<(int)tag());
  }

  for (int i = 0; i < childRSkNodeList_.size(); ++i) {
    if(childRSkNodeList_[i] != nullptr) {
      RNS_LOG_MODE_FOR_CONTAINER(" setRoot for Child  with Tag : "<<(int)childRSkNodeList_[i]->tag());
      auto node=childRSkNodeList_[i];
      if(node) {
       node->setRoot(rootNode);
      }
    }
  }
}

#ifdef ENABLE_SVG_CHILD_HIERARCHY_DEBUG
void RSkSVGContainer::printChildList() {
  for (int i = 0; i < childRSkNodeList_.size(); ++i) {
    if(childRSkNodeList_[i] != nullptr) {
      RNS_LOG_INFO(" Child Node Tag : "<<(int)childRSkNodeList_[i]->tag());
      auto node=dynamic_cast<RSkSVGContainer *>(childRSkNodeList_[i]);
      if(node) {
        RNS_LOG_INFO("Child Node is a container");
        node->printChildList();
       }
    }
  }
}
#endif //ENABLE_SVG_CHILD_HIERARCHY_DEBUG

} // namespace react
} // namespace facebook

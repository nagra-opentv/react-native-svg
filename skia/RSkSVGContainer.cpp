
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

    // Insert child RSkSVGNode in to List
    childRSkNodeList_.insert(std::make_pair(index, rskSvgNode));

    //If this parent is SVGView , set itself as Root
    if(this->tag() == SkSVGTag::kSvg) {
      rootNode_=this;
      rskSvgNode->setRoot(this);
    }
  }

  RNS_LOG_MODE_FOR_CONTAINER("RSK SVG Def Map Size for component : "<< this->getComponentData().componentName << " : "<<rskNodeIDMapper.count());
  RNS_LOG_MODE_FOR_CONTAINER("RSK SVG container Size for the Parent : "<<childRSkNodeList_.size());
}

void RSkSVGContainer::unmountChildComponent(
    std::shared_ptr<RSkComponent> oldChildComponent,
    const int index) {
  RNS_LOG_MODE_FOR_CONTAINER("Parent :"<<getComponentData().componentName<<
                    "recieved unmount for child :" << oldChildComponent->getComponentData().componentName<<
                    "@ index : "<<index);

  auto it = childRSkNodeList_.find(index);

  if(it == childRSkNodeList_.end()) {
    RNS_LOG_ERROR("Received unmount request for not supported svg Elements or may be invalid index passed : "<<index);
    return;
  }

  // If the respective node has entry In Def ID Mapper , remove it
  auto rskSvgnode=it->second;
  if(rskSvgnode && (!rskSvgnode->svgNodeId.empty())) {
    auto rootNode=dynamic_cast<RSkSVGContainer *>(rootNode_);
    if(rootNode) {
      rootNode->rskNodeIDMapper.remove(SkString(rskSvgnode->svgNodeId));
    }
  }
  childRSkNodeList_.erase(index);
}

void RSkSVGContainer::OnPaint(SkCanvas *canvas) {
  RNS_LOG_DEBUG(" Paint for Svg Elements handled via RNSVGView element ");
}

bool RSkSVGContainer::hasChildren() const {
  return !childRSkNodeList_.empty();
}

void RSkSVGContainer::onRender(const SkSVGRenderContext& ctx) const {
  for (auto &item : childRSkNodeList_) {
    RNS_LOG_MODE_FOR_CONTAINER(" Child Tag : "<<(int)item.second->tag());
    item.second->render(ctx);
  }
}

void RSkSVGContainer::setRoot(RSkSVGNode * rootNode) {
  rootNode_=rootNode;
  for (auto &item : childRSkNodeList_) {
    item.second->setRoot(rootNode);
  }
}

#ifdef ENABLE_SVG_CHILD_HIERARCHY_DEBUG
void RSkSVGContainer::printChildList() {
  for (auto &item : childRSkNodeList_) {
    RNS_LOG_INFO(" Child Node Tag : "<<(int)item.second->tag());
    auto node=dynamic_cast<RSkSVGContainer *>(item.second);
    if(node) {
      RNS_LOG_INFO("Child Node is a container");
      node->printChildList();
    }
  }
}
#endif //ENABLE_SVG_CHILD_HIERARCHY_DEBUG

} // namespace react
} // namespace facebook

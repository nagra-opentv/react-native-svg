
/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "include/core/SkPath.h"

#include "RSkSVGContainer.h"
#include "ReactSkia/RSkThirdPartyFabricComponentsProvider.h"
#include "ReactSkia/utils/RnsUtils.h"

namespace facebook {
namespace react {

#define DOWN_CAST_TO_CLASS(object,class) dynamic_cast<class *>(object)

RSkSVGContainer::RSkSVGContainer(SkSVGTag t) : INHERITED(t) { }

RSkSVGContainer::~RSkSVGContainer() {
  childRSkNodeList_.clear();
  nodeIDMapper_.reset();
}

void RSkSVGContainer::addChildAtIndex(std::shared_ptr<RSkComponent> childComponent,size_t index) {

  if(!childComponent || !childComponent.get()) {
    RNS_LOG_ERROR("Invalid child component received");
    return;
  }
  // continue ,If the component is an SVG element & has registered it's provider 
  if(RSkThirdPartyFabricComponentsProvider(childComponent->getComponentData().componentName)) {

    auto node=RSkSVGNode::getRSkSVGNodeForComponetWithName(childComponent);
    if(node) {
     auto sksvgNode =sk_sp<SkSVGNode>(node);
     RNS_LOG_INFO("Child Node type  : "<<(int)node->tag());
     //RNS_LOG_ERROR("sksvgNode->unique() ::: "<<sksvgNode->unique());
     if(!node->nodeName.empty()) {
     RNS_LOG_INFO("Child Node has ID : "<<node->nodeName);
     nodeIDMapper_.set(SkString(node->nodeName),sksvgNode);
     }
     //RNS_LOG_ERROR("sksvgNode->unique() ::: "<<sksvgNode->unique());
     // If Child Node is of type of container , Merge it's defMap with it's Parent
     if(DOWN_CAST_TO_CLASS(node,RSkSVGContainer)) {
      auto mergeFn= [&](SkString keyName,sk_sp<SkSVGNode> *value){
      RNS_LOG_ERROR("  MERGING child Defs with It's Parent" );
      nodeIDMapper_.set(keyName,*value);
      };
      DOWN_CAST_TO_CLASS(node,RSkSVGContainer)->nodeIDMapper_.foreach(mergeFn);
     }
     // Insert child RSkSVGNode in to List
     size_t indexAt = std::min(index, childRSkNodeList_.size());
     RNS_LOG_DEBUG("Insert Child at index : " << indexAt );
     childRSkNodeList_.insert(childRSkNodeList_.begin() + indexAt, sksvgNode);
    // RNS_LOG_ERROR("sksvgNode->unique() ::: "<<sksvgNode->unique());
    }

    RNS_LOG_INFO("RSK SVG Def Map Size for component : "<< childComponent->getComponentData().componentName << " : "<<nodeIDMapper_.count());
    RNS_LOG_INFO("RSK SVG container Size for the Parent : "<<childRSkNodeList_.size());
  }
}

void RSkSVGContainer::removeChildAtIndex(std::shared_ptr<RSkComponent> childComponent,size_t index) {
  if(index >= childRSkNodeList_.size()) {
    RNS_LOG_ERROR("Invalid index passed for remove");
    return;
  }
  // If the respective node has entry In Def ID Mapper , remove there as well
  auto node=static_cast<RSkSVGNode *>(childRSkNodeList_[index].get());
  if(!node->nodeName.empty()) {
    nodeIDMapper_.remove(SkString(node->nodeName));
  }
  RNS_LOG_DEBUG("Remove Child at index : " << index );
  childRSkNodeList_.erase(childRSkNodeList_.begin() + index);
}

bool RSkSVGContainer::hasChildren() const {
  return !childRSkNodeList_.empty();
}

void RSkSVGContainer::onRender(const SkSVGRenderContext& ctx) const {
   RNS_LOG_INFO("---Render Childern---");
  for (int i = 0; i < childRSkNodeList_.size(); ++i) {
    RNS_LOG_INFO(" Child Tag : "<<(int)childRSkNodeList_[i]->tag());
    childRSkNodeList_[i]->render(ctx);
  }
}

void RSkSVGContainer::printChildList() {
  for (int i = 0; i < childRSkNodeList_.size(); ++i) {
    RNS_LOG_INFO(" Child Tag : "<<(int)childRSkNodeList_[i]->tag());
    if(DOWN_CAST_TO_CLASS(childRSkNodeList_[i].get(),RSkSVGContainer)) {
      RNS_LOG_INFO("Child Node Is  a container ");
      DOWN_CAST_TO_CLASS(childRSkNodeList_[i].get(),RSkSVGContainer)->printChildList();
     }
  }
}

} // namespace react
} // namespace facebook

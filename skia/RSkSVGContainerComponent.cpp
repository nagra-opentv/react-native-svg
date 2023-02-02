
/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "include/core/SkPath.h"

#include "ReactSkia/RSkThirdPartyFabricComponentsProvider.h"
#include "RSkComponentRNSVGCircle.h"
#include "RSkComponentRNSVGDefs.h"
#include "RSkComponentRNSVGEllipse.h"
#include "RSkComponentRNSVGGroup.h"
#include "RSkComponentRNSVGPath.h"
#include "RSkComponentRNSVGRect.h"
#include "RSkComponentRNSVGUse.h"
#include "RSkComponentRNSVGSvgView.h"
#include "RSkSVGContainerComponent.h"

namespace facebook {
namespace react {

namespace {
RSkSVGNode* getRSkSVGNodeForComponetWithName(std::shared_ptr<RSkComponent> component) { 

  enum componentName {
    RNSVGCircle,
    RNSVGRect,
    RNSVGEllipse,
    RNSVGPath,
    RNSVGDefs,
    RNSVGUse,
    RNSVGGroup,
    RNSVGView
  };
  static std::map<std::string, enum componentName> s_mapStringValues ={
    { "RNSVGCircle", RNSVGCircle},
    { "RNSVGRect",RNSVGRect},
    { "RNSVGEllipse",RNSVGEllipse},
    { "RNSVGPath",RNSVGPath},
    { "RNSVGDefs",RNSVGDefs},
    { "RNSVGUse",RNSVGUse},
    { "RNSVGGroup",RNSVGGroup},
    { "RNSVGView",RNSVGView}
  };

  std::string componentName=component->getComponentData().componentName;

  int index =-1;
  if(s_mapStringValues.find(componentName.c_str()) != s_mapStringValues.end()) {
    index = s_mapStringValues[componentName.c_str()];
  } 

  switch(index) {
  case RNSVGCircle:
    RNS_LOG_INFO(" SVG COMPONENT :" <<componentName.c_str());
    return static_cast<RSkComponentRNSVGCircle *>(component.get());
  break;
  case RNSVGRect:
    RNS_LOG_INFO(" SVG COMPONENT :" <<componentName.c_str());
    return static_cast<RSkComponentRNSVGRect *>(component.get());
  break;
  case RNSVGEllipse:
    RNS_LOG_INFO(" SVG COMPONENT :" <<componentName.c_str());
    return static_cast<RSkComponentRNSVGEllipse *>(component.get());
  break;
  case RNSVGPath:
    RNS_LOG_INFO(" SVG COMPONENT :" <<componentName.c_str());
    return static_cast<RSkComponentRNSVGPath *>(component.get());
  break;
  case RNSVGDefs:
    RNS_LOG_INFO(" SVG COMPONENT :" <<componentName.c_str());
    return static_cast<RSkComponentRNSVGDefs *>(component.get());
  break;
  case RNSVGUse:
    RNS_LOG_INFO(" SVG COMPONENT :" <<componentName.c_str());
    return static_cast<RSkComponentRNSVGUse *>(component.get());
  break;
  case RNSVGGroup:
    RNS_LOG_INFO(" SVG COMPONENT :" <<componentName.c_str());
    return static_cast<RSkComponentRNSVGGroup *>(component.get());
  break;
  case RNSVGView:
    RNS_LOG_INFO(" SVG COMPONENT :" <<componentName.c_str());
    return static_cast<RSkComponentRNSVGSvgView *>(component.get());
  break;
  default:
    RNS_LOG_INFO(" SVG COMPONENT :UNKNOWN Class ");
    return nullptr;
  break;
 }

}

} //namespace

#define DOWN_CAST_TO_CLASS(object,class) dynamic_cast<class *>(object)

RSkSVGContainerComponent::RSkSVGContainerComponent(const ShadowView &shadowView,
                                                   RnsShell::LayerType layerType,
                                                   SkSVGTag t)
    : RSkComponent(shadowView,layerType),
      RSkSVGNode(t) {}

RSkSVGContainerComponent::~RSkSVGContainerComponent() {
  childRSkNodeList_.clear();
  nodeIDMapper_.reset();
}

void RSkSVGContainerComponent::mountChildComponent(
    std::shared_ptr<RSkComponent> childComponent,
    const int index) {
  
  RNS_LOG_INFO("Parent Componet :" << this->getComponentData().componentName<<" holding child :" << childComponent->getComponentData().componentName);

  if(!childComponent || !childComponent.get()) {
    RNS_LOG_ERROR("Invalid child component received");
    return;
  }

  auto node=getRSkSVGNodeForComponetWithName(childComponent);
  if(node) {
    auto sksvgNode =sk_sp<SkSVGNode>(node);
    RNS_LOG_INFO("Child Node type  : "<<(int)node->tag());
    if(!node->nodeName.empty()) {
    RNS_LOG_INFO("Child Node has ID : "<<node->nodeName);
    nodeIDMapper_.set(SkString(node->nodeName),sksvgNode);
    }
    // If Child Node is of type of container , Merge it's defMap with it's Parent
    if(DOWN_CAST_TO_CLASS(node,RSkSVGContainerComponent)) {
      auto mergeFn= [&](SkString keyName,sk_sp<SkSVGNode> *value){
      RNS_LOG_ERROR("  MERGING child Defs with It's Parent" );
      nodeIDMapper_.set(keyName,*value);
      };
      DOWN_CAST_TO_CLASS(node,RSkSVGContainerComponent)->nodeIDMapper_.foreach(mergeFn);
    }
    // Insert child RSkSVGNode in to List
    size_t indexAt = std::min((size_t)index, childRSkNodeList_.size());
    RNS_LOG_DEBUG("Insert Child at index : " << indexAt );
    childRSkNodeList_.insert(childRSkNodeList_.begin() + indexAt, sksvgNode);
  }

  RNS_LOG_INFO("RSK SVG Def Map Size for component : "<< this->getComponentData().componentName << " : "<<nodeIDMapper_.count());
  RNS_LOG_INFO("RSK SVG container Size for the Parent : "<<childRSkNodeList_.size());
}

void RSkSVGContainerComponent::unmountChildComponent(
    std::shared_ptr<RSkComponent> oldChildComponent,
    const int index) {
  RNS_LOG_INFO("RSkSVGContainerComponent recieved unmount for child :" << oldChildComponent->getComponentData().componentName);
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

void RSkSVGContainerComponent::OnPaint(SkCanvas *canvas) {
  RNS_LOG_INFO(" Paint for cvg Elements handled via RNSSVG element ");
}

bool RSkSVGContainerComponent::hasChildren() const {
  return !childRSkNodeList_.empty();
}

void RSkSVGContainerComponent::onRender(const SkSVGRenderContext& ctx) const {
   RNS_LOG_INFO("---Render Childern---");
  for (int i = 0; i < childRSkNodeList_.size(); ++i) {
    RNS_LOG_INFO(" Child Tag : "<<(int)childRSkNodeList_[i]->tag());
    childRSkNodeList_[i]->render(ctx);
  }
}

void RSkSVGContainerComponent::printChildList() {
  for (int i = 0; i < childRSkNodeList_.size(); ++i) {
    RNS_LOG_INFO(" Child Tag : "<<(int)childRSkNodeList_[i]->tag());
    if(DOWN_CAST_TO_CLASS(childRSkNodeList_[i].get(),RSkSVGContainerComponent)) {
      RNS_LOG_INFO("Child Node Is  a container ");
      DOWN_CAST_TO_CLASS(childRSkNodeList_[i].get(),RSkSVGContainerComponent)->printChildList();
     }
  }
}

} // namespace react
} // namespace facebook

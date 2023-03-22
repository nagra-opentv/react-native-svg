
/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "RSkSVGContainer.h"

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

  RNS_LOG_DEBUG("Parent :"<<getComponentData().componentName<<
                "recieved mount for child :" << childComponent->getComponentData().componentName<<
                "@ index : "<<index);

  if(!childComponent || !childComponent.get()) {
    RNS_LOG_ERROR("Invalid or not supported svg component received for mounting ");
    return;
  }

  RSkSVGNode* rskSvgNode=dynamic_cast<RSkSVGComponentNode *>(childComponent.get());
  if(rskSvgNode) {
    if(!rskSvgNode->svgNodeId.empty()) {
      rskNodeIDMapper.set(SkString(rskSvgNode->svgNodeId),rskSvgNode);
    }

    // If the type of a Child Node is a container,then combine its defMap with that of its parent and discard its own.
    auto nodeContainer=dynamic_cast<RSkSVGContainer *>(rskSvgNode);
    if(nodeContainer) {
      auto mergeFn= [&](SkString keyName,RSkSVGNode** value){
        rskNodeIDMapper.set(keyName,*value);
      };
      nodeContainer->rskNodeIDMapper.foreach(mergeFn);
      nodeContainer->rskNodeIDMapper.reset();
    }

    childRSkNodeList_.insert(std::make_pair(index, rskSvgNode));

    if(this->tag() == SkSVGTag::kSvg) {
      rootNode_=this;
      rskSvgNode->setRootNode(this);
    }
  }
}

void RSkSVGContainer::unmountChildComponent(
    std::shared_ptr<RSkComponent> oldChildComponent,
    const int index) {
  RNS_LOG_DEBUG("Parent :"<<getComponentData().componentName<<
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

bool RSkSVGContainer::onPrepareToRender(SkSVGRenderContext* ctx) const {
  /*For  colorType- uri/BRUSH_REF, inheritence  to be handled in RSKSVG*/
  RNS_LOG_INFO(__func__<<" For component : "<<getComponentData().componentName);
  auto inheritColor =[&](RSkSVGNode* childNode, std::string colorType,RNSVGColorFillStruct colorStruct){
    auto node=dynamic_cast<RSkSVGComponentNode *>(childNode);
    RNS_LOG_ERROR(" child component : "<<node->getComponentData().componentName);

    if((std::find (childNode->renderablePropList.begin(), childNode->renderablePropList.end(), colorType) == childNode->renderablePropList.end())) {
      RNS_LOG_INFO(colorType << "Not available for childNode : ");
      if((std::find (renderablePropList.begin(), renderablePropList.end(), colorType) != renderablePropList.end())) {
              RNS_LOG_INFO(colorType << "But Parent Has : ");

        if(colorStruct.type == RNSVGColorType::BRUSH_REF) {
          RNS_LOG_INFO(" colorStruct.type is BrushRef");
          (colorType == "fill") ? (childNode->fillColor=colorStruct) : (childNode->strokeColor=colorStruct);
        }
      }
    }
  };

  for (auto &item:childRSkNodeList_) {
    inheritColor(item.second,"fill",fillColor);
    inheritColor(item.second,"stroke",strokeColor);
    auto containerNode=dynamic_cast<RSkSVGContainer *>(item.second);
    if(containerNode) {
      containerNode->RSkSVGContainer::onPrepareToRender(ctx);
    }
  }
  return this->INHERITED::onPrepareToRender(ctx);
}

void RSkSVGContainer::onRender(const SkSVGRenderContext& ctx) const {
  for (auto &item : childRSkNodeList_) {
  #ifdef ENABLE_SVG_RENDER_DEBUG
    RSkComponent* componetNode=dynamic_cast<RSkSVGComponentNode *>(item.second);
    RNS_LOG_INFO(" Rendering Child Element  : "<<componetNode->getComponentData().componentName);
  #endif/*ENABLE_SVG_RENDER_DEBUG*/
    item.second->render(ctx);
  }
}

void RSkSVGContainer::setRootNode(RSkSVGNode * rootNode) {
  rootNode_=rootNode;
  for (auto &item : childRSkNodeList_) {
    item.second->setRootNode(rootNode);
  }
}

#ifdef ENABLE_SVG_RENDER_DEBUG
void RSkSVGContainer::printChildList() {
  for (auto &item : childRSkNodeList_) {
    RSkComponent* componetNode=dynamic_cast<RSkSVGComponentNode *>(item.second);
    if(componetNode) {
      RNS_LOG_INFO(" Child Componet : "<<componetNode->getComponentData().componentName<<
                   " @Index = "<<item.first);
      auto node=dynamic_cast<RSkSVGContainer *>(item.second);
      if(node) {
        RNS_LOG_INFO(" Container Info For component : "<<node->getComponentData().componentName << "\n" <<
                     "-------------------------------"<<"\n"<<
                     " No of Def Elements   : "<<rskNodeIDMapper.count()<<"\n"<<
                     " No of Child Element/s: "<<childRSkNodeList_.size()<<"\n"<<
                     "-------------------------------");
        node->printChildList();
      }
    }
  }
}
#endif //ENABLE_SVG_RENDER_DEBUG

} // namespace react
} // namespace facebook

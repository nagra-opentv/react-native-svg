
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

  #ifdef ENABLE_RSKSVG_RENDER_DEBUG
  RNS_LOG_INFO("Parent :"<<getComponentData().componentName<<
                "recieved mount for child :" << childComponent->getComponentData().componentName<<
                "@ index : "<<index);
  #endif/*ENABLE_RSKSVG_RENDER_DEBUG*/

  if(!childComponent || !childComponent.get()) {
    RNS_LOG_ERROR("Invalid or not supported svg component received for mounting ");
    return;
  }

  RSkSVGNode* rskSvgNode=dynamic_cast<RSkSVGComponentNode *>(childComponent.get());
  if(rskSvgNode) {
    if(!rskSvgNode->svgNodeId.empty()) {
      rskNodeIDMapper.set(SkString(rskSvgNode->svgNodeId),rskSvgNode);
    }

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
      rootSvgNode=this;
      rskSvgNode->setRootSvgNode(this);
    }
  }
}

void RSkSVGContainer::unmountChildComponent(
    std::shared_ptr<RSkComponent> oldChildComponent,
    const int index) {

  #ifdef ENABLE_RSKSVG_RENDER_DEBUG
  RNS_LOG_INFO("Parent :"<<getComponentData().componentName<<
                "recieved unmount for child :" << oldChildComponent->getComponentData().componentName<<
                "@ index : "<<index);
  #endif /*ENABLE_RSKSVG_RENDER_DEBUG*/

  auto it = childRSkNodeList_.find(index);

  if(it == childRSkNodeList_.end()) {
    RNS_LOG_ERROR("Received unmount request for not supported svg Elements or may be invalid index passed : "<<index);
    return;
  }

  auto rskSvgnode=it->second;
  if(rskSvgnode && (!rskSvgnode->svgNodeId.empty())) {
    auto rootNode=dynamic_cast<RSkSVGContainer *>(rootSvgNode);
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
  auto inheritColor =[&](RSkSVGNode* childNode, std::string colorType,RNSVGColorFillStruct colorStruct){

    if((std::find (childNode->renderablePropList.begin(), childNode->renderablePropList.end(), colorType) == childNode->renderablePropList.end())) {

      if((std::find (renderablePropList.begin(), renderablePropList.end(), colorType) != renderablePropList.end())) {

        (colorType == "fill") ? (childNode->fillColor=colorStruct) : (childNode->strokeColor=colorStruct);
        #ifdef ENABLE_RSKSVG_PROPS_DEBUG
          RNS_LOG_INFO(" Child Component : "<<getRSkSvgComponentName(childNode)<<
                       " inherits - "<<  ((colorType == "fill") ? "FillProps":"StrokeProps") <<
                       " from it's parent : "<< getComponentData().componentName <<
                       " Color URL: " <<colorStruct.brushRef
                      );
        #endif /*ENABLE_RSKSVG_PROPS_DEBUG*/

      }
    }
  };

  for (auto &item:childRSkNodeList_) {
    inheritColor(item.second,"fill",fillColor);
    inheritColor(item.second,"stroke",strokeColor);
  }
  return this->INHERITED::onPrepareToRender(ctx);
}

void RSkSVGContainer::onRender(const SkSVGRenderContext& ctx) const {
  for (auto &item : childRSkNodeList_) {
  #ifdef ENABLE_RSKSVG_RENDER_DEBUG
    RNS_LOG_INFO(" Rendering Child Element  : "<<getRSkSvgComponentName(static_cast<RSkSVGComponentNode *>(item.second)));
  #endif/*ENABLE_RSKSVG_RENDER_DEBUG*/
    item.second->render(ctx);
  }
}

void RSkSVGContainer::setRootSvgNode(RSkSVGNode * rootNode) {
  rootSvgNode=rootNode;
  for (auto &item : childRSkNodeList_) {
    item.second->setRootSvgNode(rootNode);
  }
}

#ifdef ENABLE_SVG_RENDER_DEBUG
void RSkSVGContainer::printChildList() {
  for (auto &item : childRSkNodeList_) {
    RNS_LOG_INFO(" Child Component : "<<getRSkSvgComponentName(item.second)<<
                 " @Index = "<<item.first);
    auto node=dynamic_cast<RSkSVGContainer *>(item.second);
    if(node) {
      RNS_LOG_INFO(" Container Info For component : "<<getRSkSvgComponentName(node) << "\n" <<
                   "-------------------------------"<<"\n"<<
                   " No of Def Elements   : "<<rskNodeIDMapper.count()<<"\n"<<
                   " No of Child Element/s: "<<childRSkNodeList_.size()<<"\n"<<
                   "-------------------------------");
      node->printChildList();
    }
  }
}
#endif //ENABLE_SVG_RENDER_DEBUG

} // namespace react
} // namespace facebook

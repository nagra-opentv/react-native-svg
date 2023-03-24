/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "RSkComponentRNSVGCircle.h"
#include "RSkComponentRNSVGDefs.h"
#include "RSkComponentRNSVGEllipse.h"
#include "RSkComponentRNSVGGroup.h"
#include "RSkComponentRNSVGLine.h"
#include "RSkComponentRNSVGLinearGradient.h"
#include "RSkComponentRNSVGPath.h"
#include "RSkComponentRNSVGRect.h"
#include "RSkComponentRNSVGText.h"
#include "RSkComponentRNSVGTSpan.h"
#include "RSkComponentRNSVGUse.h"
#include "RSkComponentRNSVGSvgView.h"
#include "RSkSVGComponentNode.h"

namespace facebook {
namespace react {

SkSize RSkSVGComponentNode::getContainerSize() const {
  if( rootSvgNode && (rootSvgNode->tag() == SkSVGTag::kSvg)) {
    auto node=dynamic_cast<RSkComponentRNSVGSvgView *>(rootSvgNode);
    if(node) {
      return node->getContainerSize();
    }
  }
  return SkSize::Make(0, 0);
}

void RSkSVGComponentNode::invalidateLayer(){
/*
  TODO: To enhance performance, consider the following tasks:
    1. Batch the InvalidateLayer calls and perform them once for the entire SVG container.
    2. When a layer is invalidated, mark only the dirty region of the respective SVG element instead of the entire container.
*/
  if(rootSvgNode) {
    auto rootSvgContainerNode=static_cast<RSkComponentRNSVGSvgView *>(rootSvgNode);
    if(rootSvgContainerNode) {
       rootSvgContainerNode->drawAndSubmit(RnsShell::LayerInvalidateAll);
       #ifdef ENABLE_RSKSVG_RENDER_DEBUG
       RNS_LOG_INFO(" Invalidating SVG Container on behalf of child SVG Element  : "<<getRSkSvgComponentName(this));
       #endif /*ENABLE_RSKSVG_RENDER_DEBUG*/
    }
  }
}

std::string RSkSVGComponentNode::getRSkSvgComponentName(RSkSVGNode *node) const {
  if(node) {
    RSkComponent* componetNode=static_cast<RSkSVGComponentNode *>(node);
    return componetNode->getComponentData().componentName;
  }
  std::string emptyString;
  return emptyString;
}

const RNSVGCommonRenderableProps * RSkSVGComponentNode::getCommonRenderableProps(RSkSVGNode* node) const{

  if(!node) return nullptr;

  static std::unordered_map<std::string, const RNSVGCommonRenderableProps* (*)(RSkComponent * )> s_mapStringValues={
    { "RNSVGView",getCommonRenderablePropsFromComponent<RSkComponentRNSVGSvgView,RNSVGSvgViewProps>},
    { "RNSVGGroup",getCommonRenderablePropsFromComponent<RSkComponentRNSVGGroup,RNSVGGroupProps>},
    { "RNSVGCircle",getCommonRenderablePropsFromComponent<RSkComponentRNSVGCircle,RNSVGCircleProps>},
    { "RNSVGRect",getCommonRenderablePropsFromComponent<RSkComponentRNSVGRect,RNSVGRectProps>},
    { "RNSVGEllipse",getCommonRenderablePropsFromComponent<RSkComponentRNSVGEllipse,RNSVGEllipseProps>},
    { "RNSVGPath",getCommonRenderablePropsFromComponent<RSkComponentRNSVGPath,RNSVGPathProps>},
    { "RNSVGLine",getCommonRenderablePropsFromComponent<RSkComponentRNSVGLine,RNSVGLineProps>},
    { "RNSVGLinearGradient",getCommonRenderablePropsFromComponent<RSkComponentRNSVGLinearGradient,RNSVGLinearGradientProps>},
    { "RNSVGText",getCommonRenderablePropsFromComponent<RSkComponentRNSVGText,RNSVGTextProps>},
    { "RNSVGTSpan",getCommonRenderablePropsFromComponent<RSkComponentRNSVGTSpan,RNSVGTSpanProps>},
    { "RNSVGDefs",getCommonRenderablePropsFromComponent<RSkComponentRNSVGDefs,RNSVGDefsProps>},
    { "RNSVGUse",getCommonRenderablePropsFromComponent<RSkComponentRNSVGUse,RNSVGUseProps>}
  };
  auto componentNode = static_cast<RSkSVGComponentNode *>(node);
  std::string componentName=getRSkSvgComponentName(componentNode);

  if(s_mapStringValues.find(componentName) != s_mapStringValues.end()) {
    return s_mapStringValues[componentName](componentNode);
  } else {
    return nullptr;
  }
}

} // namespace react
} // namespace facebook


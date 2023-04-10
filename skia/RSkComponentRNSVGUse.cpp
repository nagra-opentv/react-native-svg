/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "RSkComponentRNSVGUse.h"
#include "RSkComponentRNSVGSvgView.h"

namespace facebook {
namespace react {

RSkComponentRNSVGUse::RSkComponentRNSVGUse(const ShadowView &shadowView)
    : INHERITED(shadowView,LAYER_TYPE_VIRTUAL,SkSVGTag::kUse){}

RnsShell::LayerInvalidateMask  RSkComponentRNSVGUse::updateComponentProps(SharedProps newViewProps,bool forceUpdate) {
  
  auto const &newRNSVGUseProps = *std::static_pointer_cast<RNSVGUseProps const>(newViewProps);

#ifdef ENABLE_RSKSVG_PROPS_DEBUG
  RNS_LOG_INFO("\n" <<
               "===Native Props for SVG Element Use==="<< "\n" <<
               " X      : "<<newRNSVGUseProps.x << "\n" <<
               " Y      : "<<newRNSVGUseProps.y << "\n" <<
               " Href   : "<<newRNSVGUseProps.href.c_str() << "\n" <<
               " Width  : "<<newRNSVGUseProps.width << "\n" <<
               " Height : "<<newRNSVGUseProps.height << "\n" <<
               "======================================");
#endif/*ENABLE_RSKSVG_PROPS_DEBUG*/

  setLengthAttribute(SkSVGAttribute::kX,newRNSVGUseProps.x);
  setLengthAttribute(SkSVGAttribute::kY,newRNSVGUseProps.y);
  setAttribute(SkSVGAttribute::kHref,SkSVGStringValue(SkString(newRNSVGUseProps.href)));
  setLengthAttribute(SkSVGAttribute::kWidth,newRNSVGUseProps.width);
  setLengthAttribute(SkSVGAttribute::kHeight,newRNSVGUseProps.height);

  setCommonRenderableProps(newRNSVGUseProps);
  setCommonNodeProps(newRNSVGUseProps);

  invalidateParentSvgContainer();

  return RnsShell::LayerInvalidateAll;
}

void RSkComponentRNSVGUse::onSetAttribute(SkSVGAttribute attr, const SkSVGValue& attrValue) {
  switch (attr) {
    case SkSVGAttribute::kHref:
      if (const auto* href = attrValue.as<SkSVGStringValue>()) {
        href_ = *href;
      }
      break;
    case SkSVGAttribute::kX:
      if (const auto* x = attrValue.as<SkSVGLengthValue>()) {
        x_ = *x;
      }
      break;
    case SkSVGAttribute::kY:
      if (const auto* y = attrValue.as<SkSVGLengthValue>()) {
        y_ = *y;
      }
      break;
    default:
      this->INHERITED::onSetAttribute(attr, attrValue);
  }
}

bool RSkComponentRNSVGUse::onPrepareToRender(SkSVGRenderContext* renderContext) const {

  if (href_.isEmpty() || !INHERITED::onPrepareToRender(renderContext)) {
    return false;
  }

  if (x_.value() || y_.value()) {
    // Restored when the local SkSVGRenderContext leaves scope.
    renderContext->saveOnce();
    renderContext->canvas()->translate(x_.value(), y_.value());
  }

  return true;
}

void RSkComponentRNSVGUse::onRender(const SkSVGRenderContext& renderContext) const {
  if(rootSvgNode) {
    auto rootSvgContainerNode=static_cast<RSkComponentRNSVGSvgView *>(rootSvgNode);
    if(rootSvgContainerNode) {
       RSkSVGNode**  nodeRef = rootSvgContainerNode->rskNodeIDMapper.find(href_);
      if (nodeRef && (*nodeRef)) {

       // Apply Host props on Def node. On render completion reset it.
        bool resetHrefNodeProps{false};
        if(!renderablePropList.empty()) {
          auto const &newRNSVGUseProps = *std::static_pointer_cast<RNSVGUseProps const>(getComponentData().props);
          (*nodeRef)->setCommonRenderableProps(newRNSVGUseProps);
          resetHrefNodeProps=true;
        }

        (*nodeRef)->render(renderContext);

        // Reset Def node with it's own props
        if(resetHrefNodeProps) {
          auto const renderableProps = getCommonRenderableProps(*nodeRef);
          if(renderableProps) {
            (*nodeRef)->setCommonRenderableProps(*renderableProps);
          }
        }
      } else {
        RNS_LOG_ERROR(" The specified Href for the component is not available : "<<href_.c_str());
        return;
      }
    }
  }
}

} // namespace react
} // namespace facebook

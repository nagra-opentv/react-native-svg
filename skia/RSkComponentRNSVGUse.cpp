/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "RSkComponentRNSVGUse.h"

namespace facebook {
namespace react {

RSkComponentRNSVGUse::RSkComponentRNSVGUse(const ShadowView &shadowView)
    : INHERITED(shadowView,LAYER_TYPE_VIRTUAL,SkSVGTag::kUse){}

RnsShell::LayerInvalidateMask  RSkComponentRNSVGUse::updateComponentProps(SharedProps newViewProps,bool forceUpdate) {
  auto component = getComponentData();

  auto const &newRNSVGUseProps = *std::static_pointer_cast<RNSVGUseProps const>(newViewProps);
  
  RNS_LOG_DEBUG( " Width :: "<<component.layoutMetrics.frame.size.width<<" Height :: "<<component.layoutMetrics.frame.size.height<< " X:: "<<component.layoutMetrics.frame.origin.x<< " Y:: "<<component.layoutMetrics.frame.origin.y);

#ifdef ENABLE_NATIVE_PROPS_DEBUG
  RNS_LOG_INFO("\n" <<
               "===Native Props for SVG Element Use==="<< "\n" <<
               " Y      : "<<newRNSVGUseProps.y << "\n" <<
               " Href   : "<<newRNSVGUseProps.href.c_str() << "\n" <<
               " Width  : "<<newRNSVGUseProps.width << "\n" <<
               " Height : "<<newRNSVGUseProps.height << "\n" <<
               "======================================");
#endif/*ENABLE_NATIVE_PROPS_DEBUG*/

  setLengthAttribute(SkSVGAttribute::kX,newRNSVGUseProps.x);
  setLengthAttribute(SkSVGAttribute::kY,newRNSVGUseProps.y);
  setAttribute(SkSVGAttribute::kHref,SkSVGStringValue(SkString(newRNSVGUseProps.href)));
  setLengthAttribute(SkSVGAttribute::kWidth,newRNSVGUseProps.width);
  setLengthAttribute(SkSVGAttribute::kHeight,newRNSVGUseProps.height);

  setCommonRenderableProps(newRNSVGUseProps);
  setCommonNodeProps(newRNSVGUseProps);

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

bool RSkComponentRNSVGUse::onPrepareToRender(SkSVGRenderContext* ctx) const {

  if (href_.isEmpty() || !INHERITED::onPrepareToRender(ctx)) {
    return false;
  }

  if (x_.value() || y_.value()) {
    // Restored when the local SkSVGRenderContext leaves scope.
    ctx->saveOnce();
    ctx->canvas()->translate(x_.value(), y_.value());
  }

  return true;
}

void RSkComponentRNSVGUse::onRender(const SkSVGRenderContext& ctx) const {

  const auto ref = ctx.findNodeById(href_);
  if (!ref) {
    RNS_LOG_ERROR(" !!! Id not Found !!!!");
    return;
  }
  ref->render(ctx);
}

} // namespace react
} // namespace facebook
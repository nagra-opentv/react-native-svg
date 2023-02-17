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
  setNativeProps(newRNSVGUseProps);
  setCommonRenderableProps(newRNSVGUseProps);
  setCommonNodeProps(newRNSVGUseProps);

  return RnsShell::LayerInvalidateAll;
}

inline void  RSkComponentRNSVGUse::setNativeProps(const RNSVGUseProps &nativeProps) {

#ifdef ENABLE_NATIVE_PROPS_DEBUG
  RNS_LOG_INFO(" X  : "<<nativeProps.x <<
               " Y  : "<<nativeProps.y <<
               " Href : "<<nativeProps.href.c_str()<<
               " Width : "<<nativeProps.width<<
               " Height : "<<nativeProps.height);
#endif/*ENABLE_NATIVE_PROPS_DEBUG*/

  setLengthAttribute(SkSVGAttribute::kX,nativeProps.x);
  setLengthAttribute(SkSVGAttribute::kY,nativeProps.y);
  setAttribute(SkSVGAttribute::kHref,SkSVGStringValue(SkString(nativeProps.href)));
  setLengthAttribute(SkSVGAttribute::kWidth,nativeProps.width);
  setLengthAttribute(SkSVGAttribute::kHeight,nativeProps.height);

}

void RSkComponentRNSVGUse::onSetAttribute(SkSVGAttribute attr, const SkSVGValue& v) {
  switch (attr) {
    case SkSVGAttribute::kHref:
      if (const auto* href = v.as<SkSVGStringValue>()) {
        href_ = *href;
      }
      break;
    case SkSVGAttribute::kX:
      if (const auto* x = v.as<SkSVGLengthValue>()) {
        x_ = *x;
      }
      break;
    case SkSVGAttribute::kY:
      if (const auto* y = v.as<SkSVGLengthValue>()) {
        y_ = *y;
      }
      break;
    default:
      this->INHERITED::onSetAttribute(attr, v);
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
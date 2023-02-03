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
    : RSkComponent(shadowView,LAYER_TYPE_VIRTUAL),
      INHERITED(SkSVGTag::kUse) {}

RnsShell::LayerInvalidateMask  RSkComponentRNSVGUse::updateComponentProps(SharedProps newViewProps,bool forceUpdate) {
  auto component = getComponentData();

  auto const &newRNSVGUseProps = *std::static_pointer_cast<RNSVGUseProps const>(newViewProps);
  
  RNS_LOG_DEBUG( " Width :: "<<component.layoutMetrics.frame.size.width<<" Height :: "<<component.layoutMetrics.frame.size.height<< " X:: "<<component.layoutMetrics.frame.origin.x<< " Y:: "<<component.layoutMetrics.frame.origin.y);
  setNativeProps(newRNSVGUseProps);
  setCommonRenderableProps(newRNSVGUseProps);
  setCommonNodeProps(newRNSVGUseProps);
 
  return RnsShell::LayerInvalidateNone;
}

inline RnsShell::LayerInvalidateMask  RSkComponentRNSVGUse::setNativeProps(const RNSVGUseProps &nativeProps) {

  RNS_LOG_INFO(" X: "<<nativeProps.x);
  RNS_LOG_INFO(" Y: "<<nativeProps.y);
  RNS_LOG_INFO(" Href: "<<nativeProps.href.c_str());
  RNS_LOG_INFO(" Width: "<<nativeProps.width);
  RNS_LOG_INFO(" Height: "<<nativeProps.height);

  setLengthAttribute(SkSVGAttribute::kX,nativeProps.x.c_str());
  setLengthAttribute(SkSVGAttribute::kY,nativeProps.y.c_str());
  setAttribute(SkSVGAttribute::kHref,SkSVGStringValue(SkString(nativeProps.href.c_str())));
  setLengthAttribute(SkSVGAttribute::kWidth,nativeProps.width.c_str());
  setLengthAttribute(SkSVGAttribute::kHeight,nativeProps.height.c_str());

  return RnsShell::LayerInvalidateNone;
}

void RSkComponentRNSVGUse::mountChildComponent(
    std::shared_ptr<RSkComponent> newChildComponent,
    const int index) {
  RNS_LOG_INFO("cannot append child nodes to an SVG Element Use.");
}

void RSkComponentRNSVGUse::unmountChildComponent(
    std::shared_ptr<RSkComponent> oldChildComponent,
    const int index) {
  RNS_LOG_INFO(" SVG Element use can't have child ");
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

  RNS_LOG_INFO("---onPrepareToRender For Use Component--- : "<<href_.c_str());

  if (href_.isEmpty() || !INHERITED::onPrepareToRender(ctx)) {
    return false;
  }

  if (x_.value() || y_.value()) {
    // Restored when the local SkSVGRenderContext leaves scope.
    ctx->saveOnce();
    ctx->canvas()->translate(x_.value(), y_.value());
  }
  RNS_LOG_INFO("---onPrepareToRender For Use Component--- : "<<href_.c_str());

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
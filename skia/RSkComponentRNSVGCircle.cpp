/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "RSkComponentRNSVGCircle.h"

namespace facebook {
namespace react {

RSkComponentRNSVGCircle::RSkComponentRNSVGCircle(const ShadowView &shadowView)
    : RSkComponent(shadowView,LAYER_TYPE_DEFAULT),
      INHERITED(SkSVGTag::kCircle) {}

void RSkComponentRNSVGCircle::mountChildComponent(std::shared_ptr<RSkComponent> newChildComponent,const int index) {
  RNS_LOG_INFO("cannot append child nodes to an SVG shape.\n");
}

void RSkComponentRNSVGCircle::unmountChildComponent(std::shared_ptr<RSkComponent> oldChildComponent,const int index) {
  RNS_LOG_INFO(" SVG Element Circle can't have child ");
}

RnsShell::LayerInvalidateMask  RSkComponentRNSVGCircle::updateComponentProps(SharedProps newViewProps,bool forceUpdate) {

  auto component = getComponentData();

  auto const &newRNSVGCircleProps = *std::static_pointer_cast<RNSVGCircleProps const>(newViewProps);

  RNS_LOG_DEBUG( " Width :: "<<component.layoutMetrics.frame.size.width<<" Height :: "<<component.layoutMetrics.frame.size.height<< " X:: "<<component.layoutMetrics.frame.origin.x<< " Y:: "<<component.layoutMetrics.frame.origin.y);

  setNativeProps(newRNSVGCircleProps);
  setCommonRenderableProps(newRNSVGCircleProps);
  setCommonNodeProps(newRNSVGCircleProps);

  return RnsShell::LayerInvalidateNone;
}

RnsShell::LayerInvalidateMask  RSkComponentRNSVGCircle::setNativeProps(const RNSVGCircleProps &nativeProps) {

  RNS_LOG_INFO(" CX: "<<nativeProps.cx);
  RNS_LOG_INFO(" CY: "<<nativeProps.cy);
  RNS_LOG_INFO(" r: "<<nativeProps.r);
  
  setLengthAttribute(SkSVGAttribute::kCx,nativeProps.cx.c_str());
  setLengthAttribute(SkSVGAttribute::kCy,nativeProps.cy.c_str());
  setLengthAttribute(SkSVGAttribute::kR,nativeProps.r.c_str());

  return RnsShell::LayerInvalidateNone;
}

void RSkComponentRNSVGCircle::onSetAttribute(SkSVGAttribute attr, const SkSVGValue& v) {

  switch (attr) {
    case SkSVGAttribute::kCx:
      if (const auto* cx = v.as<SkSVGLengthValue>()) {
        cx_ =*cx;
      }
      break;
    case SkSVGAttribute::kCy:
      if (const auto* cy = v.as<SkSVGLengthValue>()) {
        cy_ =*cy;
      }
      break;
    case SkSVGAttribute::kR:
      if (const auto* r = v.as<SkSVGLengthValue>()) {
        r_ =*r;
      }
      break;
    default:
      this->INHERITED::onSetAttribute(attr, v);
    }
}

void RSkComponentRNSVGCircle::onDraw(SkCanvas* canvas, const SkSVGLengthContext& lctx,
                         const SkPaint& paint, SkPathFillType) const {

  SkScalar cx = lctx.resolve(cx_, SkSVGLengthContext::LengthType::kHorizontal);
  SkScalar cy = lctx.resolve(cy_, SkSVGLengthContext::LengthType::kVertical);
  SkScalar  r = lctx.resolve(r_ , SkSVGLengthContext::LengthType::kOther);

  if (r > 0) {
    canvas->drawCircle(cx, cy, r, paint);
  }
 
}

} // namespace react
} // namespace facebook

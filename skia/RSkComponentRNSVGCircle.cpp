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
    : INHERITED(shadowView,LAYER_TYPE_VIRTUAL,SkSVGTag::kCircle) {}

RnsShell::LayerInvalidateMask  RSkComponentRNSVGCircle::updateComponentProps(SharedProps newViewProps,bool forceUpdate) {

  auto const &newRNSVGCircleProps = *std::static_pointer_cast<RNSVGCircleProps const>(newViewProps);

  setNativeProps(newRNSVGCircleProps);
  setCommonRenderableProps(newRNSVGCircleProps);
  setCommonNodeProps(newRNSVGCircleProps);

  return RnsShell::LayerInvalidateAll;
}

void RSkComponentRNSVGCircle::setNativeProps(const RNSVGCircleProps &nativeProps) {

  RNS_LOG_DEBUG(" CX: "<<nativeProps.cx);
  RNS_LOG_DEBUG(" CY: "<<nativeProps.cy);
  RNS_LOG_DEBUG(" r: "<<nativeProps.r);
  
  setLengthAttribute(SkSVGAttribute::kCx,nativeProps.cx);
  setLengthAttribute(SkSVGAttribute::kCy,nativeProps.cy);
  setLengthAttribute(SkSVGAttribute::kR,nativeProps.r);

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

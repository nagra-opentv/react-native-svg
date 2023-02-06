/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */


#include "RSkComponentRNSVGEllipse.h"

namespace facebook {
namespace react {

RSkComponentRNSVGEllipse::RSkComponentRNSVGEllipse(const ShadowView &shadowView)
    : INHERITED(shadowView,LAYER_TYPE_VIRTUAL,SkSVGTag::kEllipse){}

RnsShell::LayerInvalidateMask  RSkComponentRNSVGEllipse::updateComponentProps(SharedProps newViewProps,bool forceUpdate) {

  auto const &newRNSVGEllipseProps = *std::static_pointer_cast<RNSVGEllipseProps const>(newViewProps);

  setNativeProps(newRNSVGEllipseProps);
  setCommonRenderableProps(newRNSVGEllipseProps);
  setCommonNodeProps(newRNSVGEllipseProps);

  return RnsShell::LayerInvalidateAll;
}

void  RSkComponentRNSVGEllipse::setNativeProps(const RNSVGEllipseProps &nativeProps) {

  RNS_LOG_DEBUG(" CX: "<<nativeProps.cx);
  RNS_LOG_DEBUG(" CY: "<<nativeProps.cy);
  RNS_LOG_DEBUG(" RX: "<<nativeProps.rx);
  RNS_LOG_DEBUG(" RY: "<<nativeProps.ry);

  setLengthAttribute(SkSVGAttribute::kCx,nativeProps.cx);
  setLengthAttribute(SkSVGAttribute::kCy,nativeProps.cy);
  setLengthAttribute(SkSVGAttribute::kRx,nativeProps.rx);
  setLengthAttribute(SkSVGAttribute::kRy,nativeProps.ry);

}

void RSkComponentRNSVGEllipse::onSetAttribute(SkSVGAttribute attr, const SkSVGValue& v) {
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
    case SkSVGAttribute::kRx:
      if (const auto* rx = v.as<SkSVGLengthValue>()) {
        rx_ =*rx;
      }
    break;
    case SkSVGAttribute::kRy:
      if (const auto* ry = v.as<SkSVGLengthValue>()) {
        ry_ =*ry;
      }
    break;
    default:
      this->INHERITED::onSetAttribute(attr, v);
  }
}

void RSkComponentRNSVGEllipse::onDraw(SkCanvas* canvas, const SkSVGLengthContext& lctx,const SkPaint& paint, SkPathFillType) const {
  SkScalar cx = lctx.resolve(cx_, SkSVGLengthContext::LengthType::kHorizontal);
  SkScalar cy = lctx.resolve(cy_, SkSVGLengthContext::LengthType::kVertical);
  SkScalar rx = lctx.resolve(rx_, SkSVGLengthContext::LengthType::kHorizontal);
  SkScalar ry = lctx.resolve(ry_, SkSVGLengthContext::LengthType::kVertical);
    
  SkRect rect =(rx > 0 && ry > 0)
        ? SkRect::MakeXYWH(cx - rx, cy - ry, rx * 2, ry * 2)
        : SkRect::MakeEmpty();
    
  canvas->drawOval(rect, paint);
}

} // namespace react
} // namespace facebook

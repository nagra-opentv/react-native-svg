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

#ifdef ENABLE_NATIVE_PROPS_DEBUG
  RNS_LOG_INFO(" CX: "<<newRNSVGEllipseProps.cx <<
               " CY: "<<newRNSVGEllipseProps.cy <<
               " RX: "<<newRNSVGEllipseProps.rx <<
               " RY: "<<newRNSVGEllipseProps.ry);
#endif/*ENABLE_NATIVE_PROPS_DEBUG*/
  setLengthAttribute(SkSVGAttribute::kCx,newRNSVGEllipseProps.cx);
  setLengthAttribute(SkSVGAttribute::kCy,newRNSVGEllipseProps.cy);
  setLengthAttribute(SkSVGAttribute::kRx,newRNSVGEllipseProps.rx);
  setLengthAttribute(SkSVGAttribute::kRy,newRNSVGEllipseProps.ry);

  setCommonRenderableProps(newRNSVGEllipseProps);
  setCommonNodeProps(newRNSVGEllipseProps);

  return RnsShell::LayerInvalidateAll;
}

void RSkComponentRNSVGEllipse::onSetAttribute(SkSVGAttribute attr, const SkSVGValue& attrValue) {
  switch (attr) {
    case SkSVGAttribute::kCx:
      if (const auto* cx = attrValue.as<SkSVGLengthValue>()) {
        cx_ =*cx;
      }
      break;
    case SkSVGAttribute::kCy:
      if (const auto* cy = attrValue.as<SkSVGLengthValue>()) {
        cy_ =*cy;
      }
      break;
    case SkSVGAttribute::kRx:
      if (const auto* rx = attrValue.as<SkSVGLengthValue>()) {
        rx_ =*rx;
      }
      break;
    case SkSVGAttribute::kRy:
      if (const auto* ry = attrValue.as<SkSVGLengthValue>()) {
        ry_ =*ry;
      }
      break;
    default:
      this->INHERITED::onSetAttribute(attr, attrValue);
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

/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "RSkComponentRNSVGLine.h"

namespace facebook {
namespace react {

RSkComponentRNSVGLine::RSkComponentRNSVGLine(const ShadowView &shadowView)
    : INHERITED(shadowView,LAYER_TYPE_DEFAULT,SkSVGTag::kLine){}

RnsShell::LayerInvalidateMask  RSkComponentRNSVGLine::updateComponentProps(SharedProps newViewProps,bool forceUpdate) {

  auto component = getComponentData();

  auto const &newRNSVGLineProps = *std::static_pointer_cast<RNSVGLineProps const>(newViewProps);
 
  RNS_LOG_DEBUG( " Width :: "<<component.layoutMetrics.frame.size.width<<" Height :: "<<component.layoutMetrics.frame.size.height<< " X:: "<<component.layoutMetrics.frame.origin.x<< " Y:: "<<component.layoutMetrics.frame.origin.y);

  setNativeProps(newRNSVGEllipseProps);
  setCommonRenderableProps(newRNSVGEllipseProps);
  setCommonNodeProps(newRNSVGEllipseProps);

  return RnsShell::LayerInvalidateNone;
}

RnsShell::LayerInvalidateMask  RSkComponentRNSVGLine::setNativeProps(const RNSVGLineProps &nativeProps) {

  RNS_LOG_INFO(" X1: "<<nativeProps.x1);
  RNS_LOG_INFO(" Y1: "<<nativeProps.y1);
  RNS_LOG_INFO(" X2: "<<nativeProps.x2);
  RNS_LOG_INFO(" Y2: "<<nativeProps.y2);

  setLengthAttribute(SkSVGAttribute::kX1,nativeProps.x1.c_str());
  setLengthAttribute(SkSVGAttribute::kX2,nativeProps.x2.c_str());
  setLengthAttribute(SkSVGAttribute::kY1,nativeProps.y1.c_str());
  setLengthAttribute(SkSVGAttribute::kY2,nativeProps.y2.c_str());

  return RnsShell::LayerInvalidateNone;
}

void RSkComponentRNSVGLine::onSetAttribute(SkSVGAttribute attr, const SkSVGValue& v) {

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

void RSkComponentRNSVGLine::onDraw(SkCanvas* canvas, const SkSVGLengthContext& lctx,
                         const SkPaint& paint, SkPathFillType) const {

  SkScalar cx = lctx.resolve(cx_, SkSVGLengthContext::LengthType::kHorizontal);
  SkScalar cy = lctx.resolve(cy_, SkSVGLengthContext::LengthType::kVertical);
  SkScalar  r = lctx.resolve(r_ , SkSVGLengthContext::LengthType::kOther);

  if (r > 0) {
    canvas->drawLine(cx, cy, r, paint);
  }
 
}

} // namespace react
} // namespace facebook

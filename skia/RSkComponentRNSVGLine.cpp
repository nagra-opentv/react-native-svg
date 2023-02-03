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
    : INHERITED(shadowView,LAYER_TYPE_VIRTUAL,SkSVGTag::kLine){}

RnsShell::LayerInvalidateMask  RSkComponentRNSVGLine::updateComponentProps(SharedProps newViewProps,bool forceUpdate) {

  auto const &newRNSVGLineProps = *std::static_pointer_cast<RNSVGLineProps const>(newViewProps);
 
  setNativeProps(newRNSVGLineProps);
  setCommonRenderableProps(newRNSVGLineProps);
  setCommonNodeProps(newRNSVGLineProps);

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
    case SkSVGAttribute::kX1:
      if (const auto* x1 = v.as<SkSVGLengthValue>()) {
        x1_ =*x1;
      }
      break;
    case SkSVGAttribute::kY1:
      if (const auto* y1 = v.as<SkSVGLengthValue>()) {
        y1_ =*y1;
      }
      break;
    case SkSVGAttribute::kX2:
      if (const auto* x2 = v.as<SkSVGLengthValue>()) {
        x2_ =*x2;
      }
      break;
    case SkSVGAttribute::kY2:
      if (const auto* y2 = v.as<SkSVGLengthValue>()) {
        y2_ =*y2;
      }
      break;
    default:
      this->INHERITED::onSetAttribute(attr, v);
    }
}

void RSkComponentRNSVGLine::onDraw(SkCanvas* canvas, const SkSVGLengthContext& lctx,
                         const SkPaint& paint, SkPathFillType) const {

    SkPoint p0, p1;
    p0=SkPoint::Make(lctx.resolve(x1_, SkSVGLengthContext::LengthType::kHorizontal),
                     lctx.resolve(y1_, SkSVGLengthContext::LengthType::kVertical));

    p1=SkPoint::Make(lctx.resolve(x2_, SkSVGLengthContext::LengthType::kHorizontal),
                     lctx.resolve(y2_, SkSVGLengthContext::LengthType::kVertical));

    canvas->drawLine(p0, p1, paint);
 
}

} // namespace react
} // namespace facebook

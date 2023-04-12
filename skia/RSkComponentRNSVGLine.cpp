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

#ifdef ENABLE_RSKSVG_PROPS_DEBUG
  RNS_LOG_INFO("\n" <<
               "===Native Props for SVG Element Circle==="<< "\n" <<
               " X1: "<<newRNSVGLineProps.x1 << "\n" <<
               " Y1: "<<newRNSVGLineProps.y1 << "\n" <<
               " X2: "<<newRNSVGLineProps.x2 << "\n" <<
               " Y2: "<<newRNSVGLineProps.y2 << "\n" <<
               "==========================================");
#endif/*ENABLE_RSKSVG_PROPS_DEBUG*/
  setLengthAttribute(SkSVGAttribute::kX1,newRNSVGLineProps.x1);
  setLengthAttribute(SkSVGAttribute::kX2,newRNSVGLineProps.x2);
  setLengthAttribute(SkSVGAttribute::kY1,newRNSVGLineProps.y1);
  setLengthAttribute(SkSVGAttribute::kY2,newRNSVGLineProps.y2);

  setCommonRenderableProps(newRNSVGLineProps);
  setCommonNodeProps(newRNSVGLineProps);

  invalidateParentSvgContainer();

  return RnsShell::LayerInvalidateAll;
}

void RSkComponentRNSVGLine::onSetAttribute(SkSVGAttribute attr, const SkSVGValue& attrValue) {

  switch (attr) {
    case SkSVGAttribute::kX1:
      if (const auto* x1 = attrValue.as<SkSVGLengthValue>()) {
        x1_ =*x1;
      }
      break;
    case SkSVGAttribute::kY1:
      if (const auto* y1 = attrValue.as<SkSVGLengthValue>()) {
        y1_ =*y1;
      }
      break;
    case SkSVGAttribute::kX2:
      if (const auto* x2 = attrValue.as<SkSVGLengthValue>()) {
        x2_ =*x2;
      }
      break;
    case SkSVGAttribute::kY2:
      if (const auto* y2 = attrValue.as<SkSVGLengthValue>()) {
        y2_ =*y2;
      }
      break;
    default:
      this->INHERITED::onSetAttribute(attr, attrValue);
  }
}

void RSkComponentRNSVGLine::onDraw(SkCanvas* canvas, const SkSVGLengthContext& lengthContext,
                         const SkPaint& paint, SkPathFillType) const {

  SkPoint p0, p1;
  p0=SkPoint::Make(lengthContext.resolve(x1_, SkSVGLengthContext::LengthType::kHorizontal),
                   lengthContext.resolve(y1_, SkSVGLengthContext::LengthType::kVertical));

  p1=SkPoint::Make(lengthContext.resolve(x2_, SkSVGLengthContext::LengthType::kHorizontal),
                   lengthContext.resolve(y2_, SkSVGLengthContext::LengthType::kVertical));

  canvas->drawLine(p0, p1, paint);
}

SkRect RSkComponentRNSVGLine::getObjectBoundingBox(const SkSVGLengthContext& lengthContext) const {
  SkScalar x1,x2,y1,y2;
  x1=lengthContext.resolve(x1_, SkSVGLengthContext::LengthType::kHorizontal);
  x2=lengthContext.resolve(x2_, SkSVGLengthContext::LengthType::kHorizontal);
  y1=lengthContext.resolve(y2_, SkSVGLengthContext::LengthType::kVertical);
  y2=lengthContext.resolve(y2_, SkSVGLengthContext::LengthType::kVertical);

  return SkRect::MakeXYWH(x1,y1,(x2-x1),(y2-y1));
}

} // namespace react
} // namespace facebook

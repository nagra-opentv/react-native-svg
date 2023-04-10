/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "RSkComponentRNSVGRect.h"

namespace facebook {
namespace react {

RSkComponentRNSVGRect::RSkComponentRNSVGRect(const ShadowView &shadowView)
    : INHERITED(shadowView,LAYER_TYPE_VIRTUAL,SkSVGTag::kRect) {}

RnsShell::LayerInvalidateMask  RSkComponentRNSVGRect::updateComponentProps(SharedProps newViewProps,bool forceUpdate) {

  auto const &newRNSVGRectProps = *std::static_pointer_cast<RNSVGRectProps const>(newViewProps);
  
#ifdef ENABLE_RSKSVG_PROPS_DEBUG
  RNS_LOG_INFO("\n" <<
               "===Native Props for SVG Element Rect==="<< "\n" <<
               " X     : "<<newRNSVGRectProps.x <<  "\n" <<
               " Y     : "<<newRNSVGRectProps.y <<  "\n" <<
               " Rx    : "<<newRNSVGRectProps.rx <<  "\n" <<
               " Ry    : "<<newRNSVGRectProps.ry <<  "\n" <<
               " Width : "<<newRNSVGRectProps.width <<  "\n" <<
               " Height: "<<newRNSVGRectProps.height<< "\n" <<
               "=======================================" );
#endif /*ENABLE_RSKSVG_PROPS_DEBUG*/
  setLengthAttribute(SkSVGAttribute::kX,newRNSVGRectProps.x);
  setLengthAttribute(SkSVGAttribute::kY,newRNSVGRectProps.y);
  setLengthAttribute(SkSVGAttribute::kRx,newRNSVGRectProps.rx);
  setLengthAttribute(SkSVGAttribute::kRy,newRNSVGRectProps.ry);
  setLengthAttribute(SkSVGAttribute::kWidth,newRNSVGRectProps.width);
  setLengthAttribute(SkSVGAttribute::kHeight,newRNSVGRectProps.height);

  setCommonRenderableProps(newRNSVGRectProps);
  setCommonNodeProps(newRNSVGRectProps);

  invalidateParentSvgContainer();

  return RnsShell::LayerInvalidateAll;
}

void RSkComponentRNSVGRect::onSetAttribute(SkSVGAttribute attr, const SkSVGValue& attrValue) {
  switch (attr) {
    case SkSVGAttribute::kX:
      if (const auto* x = attrValue.as<SkSVGLengthValue>()) {
        x_ =*x;
      }
      break;
    case SkSVGAttribute::kY:
      if (const auto* y = attrValue.as<SkSVGLengthValue>()) {
        y_ =*y;
      }
      break;
    case SkSVGAttribute::kWidth:
      if (const auto* w = attrValue.as<SkSVGLengthValue>()) {
        width_=*w;
      }
      break;
    case SkSVGAttribute::kHeight:
      if (const auto* h = attrValue.as<SkSVGLengthValue>()) {
        height_=*h;
      }
      break;
    case SkSVGAttribute::kRx:
      if (const auto* rx = attrValue.as<SkSVGLengthValue>()) {
        rx_=*rx;
      }
      break;
    case SkSVGAttribute::kRy:
      if (const auto* ry = attrValue.as<SkSVGLengthValue>()) {
        ry_=*ry;
      }
      break;
    default:
      this->INHERITED::onSetAttribute(attr, attrValue);
  }
}

void RSkComponentRNSVGRect::onDraw(SkCanvas* canvas, const SkSVGLengthContext& lengthContext,
             const SkPaint& paint, SkPathFillType) const {

  SkRect rect = lengthContext.resolveRect(x_,y_,width_,height_);
  SkScalar rx = lengthContext.resolve(rx_, SkSVGLengthContext::LengthType::kHorizontal);
  SkScalar ry = lengthContext.resolve(ry_, SkSVGLengthContext::LengthType::kVertical);

  SkRRect rrect=SkRRect::MakeRectXY(rect, rx ,ry);
  canvas->drawRRect(rrect, paint);  
}

SkRect RSkComponentRNSVGRect::getObjectBoundingBox(const SkSVGLengthContext& lengthContext ) const {
    return lengthContext.resolveRect(x_,y_,width_,height_);
}

} // namespace react
} // namespace facebook

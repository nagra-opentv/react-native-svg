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
  
  setNativeProps(newRNSVGRectProps);
  setCommonRenderableProps(newRNSVGRectProps);
  setCommonNodeProps(newRNSVGRectProps);

  return RnsShell::LayerInvalidateNone;
}

RnsShell::LayerInvalidateMask  RSkComponentRNSVGRect::setNativeProps(const RNSVGRectProps &nativeProps) {

  RNS_LOG_INFO(" X: "<<nativeProps.x);
  RNS_LOG_INFO(" Y: "<<nativeProps.y);
  RNS_LOG_INFO(" Rx: "<<nativeProps.rx);
  RNS_LOG_INFO(" Ry: "<<nativeProps.ry);
  RNS_LOG_INFO(" Width: "<<nativeProps.width);
  RNS_LOG_INFO(" Height: "<<nativeProps.height);

  setLengthAttribute(SkSVGAttribute::kX,nativeProps.x.c_str());
  setLengthAttribute(SkSVGAttribute::kY,nativeProps.y.c_str());
  setLengthAttribute(SkSVGAttribute::kRx,nativeProps.rx.c_str());
  setLengthAttribute(SkSVGAttribute::kRy,nativeProps.ry.c_str());
  setLengthAttribute(SkSVGAttribute::kWidth,nativeProps.width.c_str());
  setLengthAttribute(SkSVGAttribute::kHeight,nativeProps.height.c_str());

  return RnsShell::LayerInvalidateNone;
}

void RSkComponentRNSVGRect::onSetAttribute(SkSVGAttribute attr, const SkSVGValue& v) {
  switch (attr) {
  case SkSVGAttribute::kX:
    if (const auto* x = v.as<SkSVGLengthValue>()) {
      x_ =*x;
    }
    break;
  case SkSVGAttribute::kY:
    if (const auto* y = v.as<SkSVGLengthValue>()) {
      y_ =*y;
    }
    break;
  case SkSVGAttribute::kWidth:
    if (const auto* w = v.as<SkSVGLengthValue>()) {
      width_=*w;
    }
    break;
  case SkSVGAttribute::kHeight:
    if (const auto* h = v.as<SkSVGLengthValue>()) {
      height_=*h;
    }
    break;
  case SkSVGAttribute::kRx:
    if (const auto* rx = v.as<SkSVGLengthValue>()) {
      rx_=*rx;
    }
    break;
  case SkSVGAttribute::kRy:
    if (const auto* ry = v.as<SkSVGLengthValue>()) {
      ry_=*ry;
    }
    break;
  default:
    this->INHERITED::onSetAttribute(attr, v);
  }
}

void RSkComponentRNSVGRect::onDraw(SkCanvas* canvas, const SkSVGLengthContext& lctx,
             const SkPaint& paint, SkPathFillType) const {

  const SkRect rect = lctx.resolveRect(x_,y_,width_,height_);
  const SkScalar rx = lctx.resolve(rx_, SkSVGLengthContext::LengthType::kHorizontal);
  const SkScalar ry = lctx.resolve(ry_, SkSVGLengthContext::LengthType::kVertical);
  
  SkRRect rrect=SkRRect::MakeRectXY(rect, rx ,ry);
  canvas->drawRRect(rrect, paint);  
}


} // namespace react
} // namespace facebook

/*
 * Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "include/core/SkCanvas.h"
#include "include/core/SkPaint.h"

#include "react/renderer/components/rnsvg/RNSVGProps.h"

#include "RSkComponentRNSVGRect.h"
#include "RSkSVGPropsParserUtil.h"

namespace facebook {
namespace react {

RSkComponentRNSVGRect::RSkComponentRNSVGRect(const ShadowView &shadowView)
    : RSkComponent(shadowView,LAYER_TYPE_DEFAULT),
    INHERITED(SkSVGTag::kRect) {
  selfNode=sk_sp<RSkSVGNode>(this);
}

RnsShell::LayerInvalidateMask  RSkComponentRNSVGRect::updateComponentProps(SharedProps newViewProps,bool forceUpdate) {
  RnsShell::LayerInvalidateMask invalidateMask = RnsShell::LayerInvalidateNone;

  auto component = getComponentData();

  auto const &newRNSVGRectProps = *std::static_pointer_cast<RNSVGRectProps const>(newViewProps);
  
  RNS_LOG_WARN( " Width :: "<<component.layoutMetrics.frame.size.width<<" Height :: "<<component.layoutMetrics.frame.size.height<< " X:: "<<component.layoutMetrics.frame.origin.x<< " Y:: "<<component.layoutMetrics.frame.origin.y);
  RNS_LOG_INFO(" X: "<<newRNSVGRectProps.x);
  RNS_LOG_INFO(" Y: "<<newRNSVGRectProps.y);
  RNS_LOG_INFO(" Rx: "<<newRNSVGRectProps.rx);
  RNS_LOG_INFO(" Ry: "<<newRNSVGRectProps.ry);
  RNS_LOG_INFO(" Width: "<<newRNSVGRectProps.width);
  RNS_LOG_INFO(" Height: "<<newRNSVGRectProps.height);

  setLengthAttribute(SkSVGAttribute::kX,newRNSVGRectProps.x.c_str());
  setLengthAttribute(SkSVGAttribute::kY,newRNSVGRectProps.y.c_str());
  setLengthAttribute(SkSVGAttribute::kRx,newRNSVGRectProps.rx.c_str());
  setLengthAttribute(SkSVGAttribute::kRy,newRNSVGRectProps.ry.c_str());
  setLengthAttribute(SkSVGAttribute::kWidth,newRNSVGRectProps.width.c_str());
  setLengthAttribute(SkSVGAttribute::kHeight,newRNSVGRectProps.height.c_str());

  updateCommonNodeProps(newRNSVGRectProps,selfNode);

  return invalidateMask;
}

void RSkComponentRNSVGRect::mountChildComponent(
    std::shared_ptr<RSkComponent> newChildComponent,
    const int index) {
  RNS_LOG_INFO("cannot append child nodes to an SVG shape.\n");
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

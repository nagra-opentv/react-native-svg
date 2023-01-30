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
    : RSkComponent(shadowView,LAYER_TYPE_DEFAULT),
    INHERITED(SkSVGTag::kEllipse) {}

void RSkComponentRNSVGEllipse::mountChildComponent(std::shared_ptr<RSkComponent> newChildComponent,const int index) {
  RNS_LOG_INFO("cannot append child nodes to an SVG Element Ellipse.\n");
}

void RSkComponentRNSVGEllipse::unmountChildComponent(std::shared_ptr<RSkComponent> oldChildComponent,const int index) {
  RNS_LOG_INFO(" SVG Element Ellipse can't have child ");
}

RnsShell::LayerInvalidateMask  RSkComponentRNSVGEllipse::updateComponentProps(SharedProps newViewProps,bool forceUpdate) {

  auto component = getComponentData();

  auto const &newRNSVGEllipseProps = *std::static_pointer_cast<RNSVGEllipseProps const>(newViewProps);

  RNS_LOG_DEBUG( " Width :: "<<component.layoutMetrics.frame.size.width<<" Height :: "<<component.layoutMetrics.frame.size.height<< " X:: "<<component.layoutMetrics.frame.origin.x<< " Y:: "<<component.layoutMetrics.frame.origin.y);
  setNativeProps(newRNSVGEllipseProps);
  setCommonRenderableProps(newRNSVGEllipseProps);
  setCommonNodeProps(newRNSVGEllipseProps);

  return RnsShell::LayerInvalidateNone;
}

RnsShell::LayerInvalidateMask  RSkComponentRNSVGEllipse::setNativeProps(const RNSVGEllipseProps &nativeProps) {

  RNS_LOG_INFO(" CX: "<<nativeProps.cx);
  RNS_LOG_INFO(" CY: "<<nativeProps.cy);
  RNS_LOG_INFO(" RX: "<<nativeProps.rx);
  RNS_LOG_INFO(" RY: "<<nativeProps.ry);

  setLengthAttribute(SkSVGAttribute::kCx,nativeProps.cx.c_str());
  setLengthAttribute(SkSVGAttribute::kCy,nativeProps.cy.c_str());
  setLengthAttribute(SkSVGAttribute::kRx,nativeProps.rx.c_str());
  setLengthAttribute(SkSVGAttribute::kRy,nativeProps.ry.c_str());

  return RnsShell::LayerInvalidateNone;
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
  const auto cx = lctx.resolve(cx_, SkSVGLengthContext::LengthType::kHorizontal);
  const auto cy = lctx.resolve(cy_, SkSVGLengthContext::LengthType::kVertical);
  const auto rx = lctx.resolve(rx_, SkSVGLengthContext::LengthType::kHorizontal);
  const auto ry = lctx.resolve(ry_, SkSVGLengthContext::LengthType::kVertical);
    
  SkRect rect =(rx > 0 && ry > 0)
        ? SkRect::MakeXYWH(cx - rx, cy - ry, rx * 2, ry * 2)
        : SkRect::MakeEmpty();
    
  canvas->drawOval(rect, paint);
}

} // namespace react
} // namespace facebook

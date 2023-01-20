/*
 * Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */


#include "include/core/SkCanvas.h"
#include "include/core/SkPaint.h"

#include "react/renderer/components/rnsvg/RNSVGProps.h"

#include "RSkComponentRNSVGEllipse.h"
#include "RSkSVGPropsParserUtil.h"

namespace facebook {
namespace react {

RSkComponentRNSVGEllipse::RSkComponentRNSVGEllipse(const ShadowView &shadowView)
    : RSkComponent(shadowView,LAYER_TYPE_DEFAULT),
    INHERITED(SkSVGTag::kEllipse) {
  selfNode=sk_sp<SkSVGNode>(this);
}

void RSkComponentRNSVGEllipse::mountChildComponent(
    std::shared_ptr<RSkComponent> newChildComponent,
    const int index) {
  RNS_LOG_INFO("cannot append child nodes to an SVG shape.\n");
}

RnsShell::LayerInvalidateMask  RSkComponentRNSVGEllipse::updateComponentProps(const ShadowView &newShadowView,bool forceUpdate) {

  auto component = getComponentData();

  auto const &newRNSVGEllipseProps = *std::static_pointer_cast<RNSVGEllipseProps const>(newShadowView.props);

  RNS_LOG_WARN( " Width :: "<<component.layoutMetrics.frame.size.width<<" Height :: "<<component.layoutMetrics.frame.size.height<< " X:: "<<component.layoutMetrics.frame.origin.x<< " Y:: "<<component.layoutMetrics.frame.origin.y);
  RNS_LOG_INFO(" CX: "<<newRNSVGEllipseProps.cx);
  RNS_LOG_INFO(" CY: "<<newRNSVGEllipseProps.cy);
  RNS_LOG_INFO(" RX: "<<newRNSVGEllipseProps.rx);
  RNS_LOG_INFO(" RY: "<<newRNSVGEllipseProps.ry);

  setLengthAttribute(selfNode,SkSVGAttribute::kCx,newRNSVGEllipseProps.cx.c_str());
  setLengthAttribute(selfNode,SkSVGAttribute::kCy,newRNSVGEllipseProps.cy.c_str());
  setLengthAttribute(selfNode,SkSVGAttribute::kRx,newRNSVGEllipseProps.rx.c_str());
  setLengthAttribute(selfNode,SkSVGAttribute::kRy,newRNSVGEllipseProps.ry.c_str());

  updateCommonNodeProps(newRNSVGEllipseProps,*this,selfNode);

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

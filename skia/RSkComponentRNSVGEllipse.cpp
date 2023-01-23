/*
 * Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <string>

#include "include/core/SkPaint.h"

#include "cxxreact/ModuleRegistry.h"

#include "react/renderer/components/rnsvg/RNSVGProps.h"

#include "RSkComponentRNSVGEllipse.h"



#include "experimental/svg/model/SkSVGRenderContext.h"
#include "experimental/svg/model/SkSVGValue.h"
#include "include/core/SkCanvas.h"

#include "RSkSVGPropsParserUtil.h"

namespace facebook {
namespace react {

RSkComponentRNSVGEllipse::RSkComponentRNSVGEllipse(const ShadowView &shadowView)
    : RSkComponent(shadowView,LAYER_TYPE_DEFAULT),
    INHERITED(SkSVGTag::kEllipse) {
      selfNode=sk_sp<RSkSVGNode>(this);
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

     selfNode->SetLengthAttribute(selfNode,SkSVGAttribute::kCx,newRNSVGEllipseProps.cx.c_str());
     selfNode->SetLengthAttribute(selfNode,SkSVGAttribute::kCy,newRNSVGEllipseProps.cy.c_str());
     selfNode->SetLengthAttribute(selfNode,SkSVGAttribute::kRx,newRNSVGEllipseProps.rx.c_str());
     selfNode->SetLengthAttribute(selfNode,SkSVGAttribute::kRy,newRNSVGEllipseProps.ry.c_str());
 updateCommonNodeProps(newRNSVGEllipseProps,selfNode);
  return RnsShell::LayerInvalidateNone;
}


void RSkComponentRNSVGEllipse::onSetAttribute(SkSVGAttribute attr, const SkSVGValue& v) {
    switch (attr) {
    case SkSVGAttribute::kCx:
        if (const auto* cx = v.as<SkSVGLengthValue>()) {
            fCx =*cx;
        }
        break;
    case SkSVGAttribute::kCy:
        if (const auto* cy = v.as<SkSVGLengthValue>()) {
             fCy =*cy;
        }
        break;
    case SkSVGAttribute::kRx:
        if (const auto* rx = v.as<SkSVGLengthValue>()) {
            fRx =*rx;
        }
        break;
    case SkSVGAttribute::kRy:
        if (const auto* ry = v.as<SkSVGLengthValue>()) {
            fRy =*ry;
        }
        break;
    default:
        this->INHERITED::onSetAttribute(attr, v);
    }
}

SkRect RSkComponentRNSVGEllipse::resolve(const SkSVGLengthContext& lctx) const {
    const auto cx = lctx.resolve(fCx, SkSVGLengthContext::LengthType::kHorizontal);
    const auto cy = lctx.resolve(fCy, SkSVGLengthContext::LengthType::kVertical);
    const auto rx = lctx.resolve(fRx, SkSVGLengthContext::LengthType::kHorizontal);
    const auto ry = lctx.resolve(fRy, SkSVGLengthContext::LengthType::kVertical);

    return (rx > 0 && ry > 0)
        ? SkRect::MakeXYWH(cx - rx, cy - ry, rx * 2, ry * 2)
        : SkRect::MakeEmpty();
}

void RSkComponentRNSVGEllipse::onDraw(SkCanvas* canvas, const SkSVGLengthContext& lctx,
                          const SkPaint& paint, SkPathFillType) const {
    canvas->drawOval(this->resolve(lctx), paint);
}

} // namespace react
} // namespace facebook

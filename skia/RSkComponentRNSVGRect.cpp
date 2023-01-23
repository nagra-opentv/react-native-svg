/*
 * Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "include/core/SkPaint.h"

#include "cxxreact/ModuleRegistry.h"

#include "react/renderer/components/rnsvg/RNSVGProps.h"
#include "rns_shell/compositor/layers/PictureLayer.h"

#include "RSkComponentRNSVGRect.h"

#include "experimental/svg/model/SkSVGRenderContext.h"
#include "experimental/svg/model/SkSVGValue.h"
#include "include/core/SkCanvas.h"


#include "RSkSVGPropsParserUtil.h"
namespace facebook {
namespace react {

RSkComponentRNSVGRect::RSkComponentRNSVGRect(const ShadowView &shadowView)
    : RSkComponent(shadowView,LAYER_TYPE_DEFAULT),
    INHERITED(SkSVGTag::kRect) {
      selfNode=sk_sp<RSkSVGNode>(this);
}

RnsShell::LayerInvalidateMask  RSkComponentRNSVGRect::updateComponentProps(const ShadowView &newShadowView,bool forceUpdate) {
  RnsShell::LayerInvalidateMask invalidateMask = RnsShell::LayerInvalidateNone;

  auto component = getComponentData();

  auto const &newRNSVGRectProps = *std::static_pointer_cast<RNSVGRectProps const>(newShadowView.props);
  
    RNS_LOG_WARN( " Width :: "<<component.layoutMetrics.frame.size.width<<" Height :: "<<component.layoutMetrics.frame.size.height<< " X:: "<<component.layoutMetrics.frame.origin.x<< " Y:: "<<component.layoutMetrics.frame.origin.y);
  RNS_LOG_INFO(" X: "<<newRNSVGRectProps.x);
  RNS_LOG_INFO(" Y: "<<newRNSVGRectProps.y);
  RNS_LOG_INFO(" Rx: "<<newRNSVGRectProps.rx);
  RNS_LOG_INFO(" Ry: "<<newRNSVGRectProps.ry);
  RNS_LOG_INFO(" Width: "<<newRNSVGRectProps.width);
  RNS_LOG_INFO(" Height: "<<newRNSVGRectProps.height);

     selfNode->SetLengthAttribute(selfNode,SkSVGAttribute::kX,newRNSVGRectProps.x.c_str());
     selfNode->SetLengthAttribute(selfNode,SkSVGAttribute::kY,newRNSVGRectProps.y.c_str());
     selfNode->SetLengthAttribute(selfNode,SkSVGAttribute::kRx,newRNSVGRectProps.rx.c_str());
     selfNode->SetLengthAttribute(selfNode,SkSVGAttribute::kRy,newRNSVGRectProps.ry.c_str());
     selfNode->SetLengthAttribute(selfNode,SkSVGAttribute::kWidth,newRNSVGRectProps.width.c_str());
     selfNode->SetLengthAttribute(selfNode,SkSVGAttribute::kHeight,newRNSVGRectProps.height.c_str());
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
            fX =*x;
        }
        break;
    case SkSVGAttribute::kY:
        if (const auto* y = v.as<SkSVGLengthValue>()) {
           fY =*y;
        }
        break;
    case SkSVGAttribute::kWidth:
        if (const auto* w = v.as<SkSVGLengthValue>()) {
            fWidth=*w;
        }
        break;
    case SkSVGAttribute::kHeight:
        if (const auto* h = v.as<SkSVGLengthValue>()) {
            fHeight=*h;
        }
        break;
    case SkSVGAttribute::kRx:
        if (const auto* rx = v.as<SkSVGLengthValue>()) {
            fRx=*rx;
        }
        break;
    case SkSVGAttribute::kRy:
        if (const auto* ry = v.as<SkSVGLengthValue>()) {
            fRy=*ry;
        }
        break;
    default:
        this->INHERITED::onSetAttribute(attr, v);
    }
}

SkRRect RSkComponentRNSVGRect::resolve(const SkSVGLengthContext& lctx) const {
    const SkRect rect = lctx.resolveRect(fX, fY, fWidth, fHeight);
    const SkScalar rx = lctx.resolve(fRx, SkSVGLengthContext::LengthType::kHorizontal);
    const SkScalar ry = lctx.resolve(fRy, SkSVGLengthContext::LengthType::kVertical);

    return SkRRect::MakeRectXY(rect, rx ,ry);
}

void RSkComponentRNSVGRect::onDraw(SkCanvas* canvas, const SkSVGLengthContext& lctx,
                       const SkPaint& paint, SkPathFillType) const {

                               canvas->save();

canvas->drawRRect(this->resolve(lctx), paint);
    
}


} // namespace react
} // namespace facebook

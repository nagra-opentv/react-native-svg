/*
 * Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <vector>
#include "include/core/SkPaint.h"
#include "experimental/svg/model/SkSVGCircle.h"

#include "cxxreact/ModuleRegistry.h"

#include "react/renderer/components/rnsvg/RNSVGProps.h"

#include "RSkComponentRNSVGView.h"
#include "experimental/svg/model/SkSVGSVG.h"
#include "experimental/svg/model/SkSVGNode.h"
#include "experimental/svg/model/SkSVGRenderContext.h"
#include "RSkSVGPropsParserUtil.h"


namespace facebook {
namespace react {

RSkComponentRNSVGView::RSkComponentRNSVGView(const ShadowView &shadowView)
    : RSkComponent(shadowView),
      INHERITED(SkSVGTag::kSvg) {
  selfNode=sk_sp<SkSVGNode>(this);
  RNS_LOG_INFO("selfNode tag : "<<(int)selfNode->tag());
}

RnsShell::LayerInvalidateMask  RSkComponentRNSVGView::updateComponentProps(const ShadowView &newShadowView,bool forceUpdate) {
  auto component = getComponentData();
  auto const &newRNSVGViewProps = *std::static_pointer_cast<RNSVGSvgViewProps const>(newShadowView.props);
  RNS_LOG_WARN( " Width :: "<<component.layoutMetrics.frame.size.width<<" Height :: "<<component.layoutMetrics.frame.size.height<< " X:: "<<component.layoutMetrics.frame.origin.x<< " Y:: "<<component.layoutMetrics.frame.origin.y);
  RNS_LOG_INFO("RNSVGSvgViewProps : minX :"<<newRNSVGViewProps.minX);
  RNS_LOG_INFO("RNSVGSvgViewProps : minY :"<<newRNSVGViewProps.minY);
  RNS_LOG_INFO("RNSVGSvgViewProps : vbWidth :"<<newRNSVGViewProps.vbWidth);
  RNS_LOG_INFO("RNSVGSvgViewProps : vbHeight :"<<newRNSVGViewProps.vbHeight);
  RNS_LOG_INFO("RNSVGSvgViewProps : tintColor :"<<newRNSVGViewProps.tintColor);
  RNS_LOG_INFO("RNSVGSvgViewProps : color :"<<newRNSVGViewProps.color);
  RNS_UNUSED(newRNSVGViewProps);

  std::string viewBox;
  viewBox.append(std::to_string(newRNSVGViewProps.minX).c_str());
  viewBox.append(" ");
  viewBox.append(std::to_string(newRNSVGViewProps.minY).c_str());
  viewBox.append(" ");
  viewBox.append(std::to_string(newRNSVGViewProps.vbWidth).c_str());
  viewBox.append(" ");
  viewBox.append(std::to_string(newRNSVGViewProps.vbHeight).c_str());
  viewBox.append(" ");
  setViewBoxAttribute(selfNode,SkSVGAttribute::kViewBox,viewBox.c_str());

  setColorAttribute(selfNode,SkSVGAttribute::kColor,newRNSVGViewProps.color.c_str());
  setLengthAttribute(selfNode,SkSVGAttribute::kX,std::to_string(component.layoutMetrics.frame.origin.x).c_str());
  setLengthAttribute(selfNode,SkSVGAttribute::kY,std::to_string(component.layoutMetrics.frame.origin.y).c_str());
  setLengthAttribute(selfNode,SkSVGAttribute::kWidth,std::to_string(component.layoutMetrics.frame.size.width).c_str());
  setLengthAttribute(selfNode,SkSVGAttribute::kHeight,std::to_string(component.layoutMetrics.frame.size.height).c_str());
  return RnsShell::LayerInvalidateNone;
}

void RSkComponentRNSVGView::OnPaint(SkCanvas *canvas) {
    SkSVGLengthContext       lctx(fContainerSize);
    SkSVGPresentationContext pctx;
    //Merge childs containers def
    for (int i = 0; i < fChildren.count(); ++i) {
        RNS_LOG_INFO("--- STARTED RENDER--");
    }
    selfNode->render(SkSVGRenderContext(canvas, IDMapper, lctx, pctx));
}

void RSkComponentRNSVGView::mountChildComponent(std::shared_ptr<RSkComponent> newChildComponent,const int index) {

  RNS_LOG_INFO("RSkComponentRNSVGView holding child :" << newChildComponent->getComponentData().componentName);
   appendSVGChildElements(newChildComponent);
}

const SkSize& RSkComponentRNSVGView::containerSize() const {
    return fContainerSize;
}

bool RSkComponentRNSVGView::onPrepareToRender(SkSVGRenderContext* ctx) const {
    auto viewPortRect  = ctx->lengthContext().resolveRect(x_,y_,width_,height_); 
    auto contentMatrix = SkMatrix::Translate(viewPortRect.x(), viewPortRect.y());
    auto viewPort      = SkSize::Make(viewPortRect.width(), viewPortRect.height());

    if (!viewBox_.isEmpty()) {

      // A viewBox overrides the intrinsic viewport.
      viewPort = SkSize::Make(viewBox_.width(), viewBox_.height());

      contentMatrix.preConcat(
        SkMatrix::MakeRectToRect(viewBox_, viewPortRect, SkMatrix::kFill_ScaleToFit));
    }

    if (!contentMatrix.isIdentity()) {
        ctx->saveOnce();
        ctx->canvas()->concat(contentMatrix);
    }

    if (viewPort != ctx->lengthContext().viewPort()) {
        ctx->writableLengthContext()->setViewPort(viewPort);
    }
    return this->INHERITED::onPrepareToRender(ctx);
}


void RSkComponentRNSVGView::onSetAttribute(SkSVGAttribute attr, const SkSVGValue& v) {
    switch (attr) {
    case SkSVGAttribute::kX:
        if (const auto* x = v.as<SkSVGLengthValue>()) {
            x_ = *x;
        }
        break;
    case SkSVGAttribute::kY:
        if (const auto* y = v.as<SkSVGLengthValue>()) {
            y_ = *y;
        }
        break;
    case SkSVGAttribute::kWidth:
        if (const auto* w = v.as<SkSVGLengthValue>()) {
            width_ = *w;
        }
        break;
    case SkSVGAttribute::kHeight:
        if (const auto* h = v.as<SkSVGLengthValue>()) {
            height_ = *h;
        }
        break;

    case SkSVGAttribute::kViewBox:
        if (const auto* vb = v.as<SkSVGViewBoxValue>()) {
            viewBox_=*vb;
        }
        break;
    default:
        this->INHERITED::onSetAttribute(attr, v);
    }
}

void RSkComponentRNSVGView::setContainerSize(const SkSize& containerSize) {
    // TODO: inval
    fContainerSize = containerSize;
}

} // namespace react
} // namespace facebook

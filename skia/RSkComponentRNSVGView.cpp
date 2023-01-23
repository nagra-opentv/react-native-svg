/*
 * Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */


#include "react/renderer/components/rnsvg/RNSVGProps.h"

#include "RSkComponentRNSVGView.h"

#include "experimental/svg/model/SkSVGRenderContext.h"

#include "RSkSVGPropsParserUtil.h"


namespace facebook {
namespace react {

RSkComponentRNSVGView::RSkComponentRNSVGView(const ShadowView &shadowView)
    : RSkComponent(shadowView,LAYER_TYPE_DEFAULT),
     INHERITED(SkSVGTag::kSvg) {
  selfNode=sk_sp<RSkSVGNode>(this);
}

void RSkComponentRNSVGView::OnPaint(SkCanvas *canvas) {
    SkSVGLengthContext       lctx(svgContainerSize);
    SkSVGPresentationContext pctx;
    
    printContainiersNodeInfo();
    RNS_LOG_INFO("---Start render from Root SVG Node---");
    // Start render from Root SVG Node
    selfNode->render(SkSVGRenderContext(canvas, IDMapper, lctx, pctx));
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

  std::string viewBox;
  viewBox.append(std::to_string(newRNSVGViewProps.minX).c_str());
  viewBox.append(" ");
  viewBox.append(std::to_string(newRNSVGViewProps.minY).c_str());
  viewBox.append(" ");
  viewBox.append(std::to_string(newRNSVGViewProps.vbWidth).c_str());
  viewBox.append(" ");
  viewBox.append(std::to_string(newRNSVGViewProps.vbHeight).c_str());
  viewBox.append(" ");
  setViewBoxAttribute(SkSVGAttribute::kViewBox,viewBox.c_str());

  setColorAttribute(SkSVGAttribute::kColor,newRNSVGViewProps.color.c_str());
  setLengthAttribute(SkSVGAttribute::kX,std::to_string(component.layoutMetrics.frame.origin.x).c_str());
  setLengthAttribute(SkSVGAttribute::kY,std::to_string(component.layoutMetrics.frame.origin.y).c_str());
  setLengthAttribute(SkSVGAttribute::kWidth,std::to_string(component.layoutMetrics.frame.size.width).c_str());
  setLengthAttribute(SkSVGAttribute::kHeight,std::to_string(component.layoutMetrics.frame.size.height).c_str());
  return RnsShell::LayerInvalidateNone;
}

void RSkComponentRNSVGView::mountChildComponent(
    std::shared_ptr<RSkComponent> newChildComponent,
    const int index) {
  RNS_LOG_INFO("RSkComponentRNSVGView holdinAg child :" << newChildComponent->getComponentData().componentName);
  appendChild(newChildComponent);
  RNS_LOG_INFO("Defs in RSkComponentRNSVGView Container:: "<<IDMapper.count());
  RNS_LOG_INFO("\n Childs in  RSkComponentRNSVGView Container :: "<<childrenContainer.count());
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

SkSize RSkComponentRNSVGView::getContainerSize(const SkSVGLengthContext& lctx) const {
    // Percentage values do not provide an intrinsic size.
    if (width_.unit() == SkSVGLength::Unit::kPercentage ||
        height_.unit() == SkSVGLength::Unit::kPercentage) {
        return SkSize::Make(0, 0);
    }

    return SkSize::Make(lctx.resolve(width_, SkSVGLengthContext::LengthType::kHorizontal),
                        lctx.resolve(height_, SkSVGLengthContext::LengthType::kVertical));
}

} // namespace react
} // namespace facebook

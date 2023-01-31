/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */


#include "experimental/svg/model/SkSVGRenderContext.h"

#include "RSkComponentRNSVGGroup.h"
#include "RSkComponentRNSVGSvgView.h"

namespace facebook {
namespace react {

RSkComponentRNSVGSvgView::RSkComponentRNSVGSvgView(const ShadowView &shadowView)
    : RSkComponent(shadowView),
     INHERITED(SkSVGTag::kSvg) {}

void RSkComponentRNSVGSvgView::OnPaint(SkCanvas *canvas) {
    SkSVGLengthContext       lctx(svgContainerSize);
    SkSVGPresentationContext pctx;
    
    printChildList();
    // Set Clip to SVG ontainer size, to restrict child draw within SVG container
    // TODO: USe Bitmap as an alternate approach for the platform with less memory constraint
    SkAutoCanvasRestore save(canvas, true);
    canvas->clipRect(SkRect::MakeXYWH(lctx.resolve(x_, SkSVGLengthContext::LengthType::kHorizontal),
                                      lctx.resolve(y_, SkSVGLengthContext::LengthType::kVertical),
                                      lctx.resolve(width_, SkSVGLengthContext::LengthType::kHorizontal),
                                      lctx.resolve(height_, SkSVGLengthContext::LengthType::kVertical))
                    );
    RNS_LOG_INFO("---Start render from Root SVG Node---");
    // Start render from Root SVG Node
    INHERITED::render(SkSVGRenderContext(canvas, nodeIDMapper_, lctx, pctx));
}

RnsShell::LayerInvalidateMask  RSkComponentRNSVGSvgView::updateComponentProps(SharedProps newViewProps,bool forceUpdate) {

  auto component = getComponentData();
  auto const &newRNSVGViewProps = *std::static_pointer_cast<RNSVGSvgViewProps const>(newViewProps);

  RNS_LOG_INFO( " Width :: "<<component.layoutMetrics.frame.size.width<<" Height :: "<<component.layoutMetrics.frame.size.height<< " X:: "<<component.layoutMetrics.frame.origin.x<< " Y:: "<<component.layoutMetrics.frame.origin.y);
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

void RSkComponentRNSVGSvgView::mountChildComponent(
    std::shared_ptr<RSkComponent> newChildComponent,
    const int index) {
  RNS_LOG_INFO("RSkComponentRNSVGSvgView holdinAg child :" << newChildComponent->getComponentData().componentName);

  addChildAtIndex(newChildComponent,index);
  
  // Fix: Skia's default paint color is black , where it is transparent on reference platform.
  //      To match with the reference platform, altering skia's default paint to transparent on the
  //      outtermost container, which will the final inherit Node for childs. 
  
  if(!strcmp(newChildComponent->getComponentData().componentName , "RNSVGGroup")) {
    (static_cast<RSkComponentRNSVGGroup *>(newChildComponent.get()))->alterSkiaDefaultPaint();
  }
}

void RSkComponentRNSVGSvgView::unmountChildComponent(
    std::shared_ptr<RSkComponent> oldChildComponent,
    const int index) {
  RNS_LOG_INFO("RSkComponentRNSVGSvgView recieved unmount for child :" << oldChildComponent->getComponentData().componentName);
  removeChildAtIndex(oldChildComponent,index);
}

bool RSkComponentRNSVGSvgView::onPrepareToRender(SkSVGRenderContext* ctx) const {
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


void RSkComponentRNSVGSvgView::onSetAttribute(SkSVGAttribute attr, const SkSVGValue& v) {
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

SkSize RSkComponentRNSVGSvgView::getContainerSize(const SkSVGLengthContext& lctx) const {
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

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
    : INHERITED(shadowView,LAYER_TYPE_PICTURE,SkSVGTag::kSvg) {}

void RSkComponentRNSVGSvgView::OnPaint(SkCanvas *canvas) {
    SkSVGLengthContext       lctx(svgContainerSize);
    SkSVGPresentationContext pctx;
    
    printChildList();

    //1. Set Clip to SVG ontainer size, to restrict child draw within SVG container
    // TODO: USe Bitmap as an alternate approach for the platform with less memory constraint
    SkAutoCanvasRestore save(canvas, true);
    canvas->clipRect(SkRect::MakeXYWH(lctx.resolve(x_, SkSVGLengthContext::LengthType::kHorizontal),
                                      lctx.resolve(y_, SkSVGLengthContext::LengthType::kVertical),
                                      lctx.resolve(width_, SkSVGLengthContext::LengthType::kHorizontal),
                                      lctx.resolve(height_, SkSVGLengthContext::LengthType::kVertical))
                    );

    //2. Apply Container Style Props.
    auto component = getComponentData();
    auto const &viewProps = *std::static_pointer_cast<ViewProps const>(component.props);
  /* apply view style props */
  auto borderMetrics=viewProps.resolveBorderMetrics(component.layoutMetrics);
  Rect frame = component.layoutMetrics.frame;

  /*Draw Order : 1. Shadow 2. BackGround 3 Border*/
  auto layerRef=layer();
  if(layerRef->isShadowVisible) {
    drawShadow(canvas,frame,borderMetrics,
                    viewProps.backgroundColor,
                    layerRef->shadowColor,layerRef->shadowOffset,layerRef->shadowOpacity,
                    layerRef->opacity,
                    layerRef->shadowImageFilter,layerRef->shadowMaskFilter
                   );
  }
  drawBackground(canvas,frame,borderMetrics,viewProps.backgroundColor);
  drawBorder(canvas,frame,borderMetrics,viewProps.backgroundColor);
  RNS_LOG_INFO("---Start render from Root SVG Node---");

  // Fix: Altering Skia's defult paint behaviour to match with reference platform.
  alterSkiaDefaultPaint();

  //3. Start render from Root SVG Node
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

  RNS_LOG_TODO("TO BE CONFIRMED: When the SVG dimensions change, it is unclear whether a remove and insert mount instruction will be received \
  or an update mount instruction will be received. If an update mount instruction is received,update props will not be called for layout metric changes.");

  return RnsShell::LayerInvalidateNone;
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

inline void RSkComponentRNSVGSvgView::alterSkiaDefaultPaint() {
 //Note: Skia's default paint is black. WhereIn on SVG REference platform it's transparent
 //      To Match with Reference output, for the next immendiate child of SVGView,
 //       resetting color to transparent, if color not speciifed

  for (auto item:childRSkNodeList_) {
    RNS_LOG_INFO(" Child Tag : "<<(int)item->tag());
    if(item->tag() == SkSVGTag::kG) {
      auto component =static_cast<RSkComponentRNSVGGroup *>(item.get())->getComponentData();
      auto const &newRNSVGGroupPropsProps = *std::static_pointer_cast<RNSVGGroupProps const>(component.props);
      auto rskSVGNode =static_cast<RSkSVGNode *>(item.get());
      // Reset Stroke & Fill Color if not specifed to transparent
      if(std::find (newRNSVGGroupPropsProps.propList.begin(), newRNSVGGroupPropsProps.propList.end(), "fill") == newRNSVGGroupPropsProps.propList.end()) {
        rskSVGNode->setPaintAttribute(SkSVGAttribute::kFill,"none");
      }
      if(std::find (newRNSVGGroupPropsProps.propList.begin(), newRNSVGGroupPropsProps.propList.end(), "stroke") == newRNSVGGroupPropsProps.propList.end()) {
        rskSVGNode->setPaintAttribute(SkSVGAttribute::kStroke,"none");
      }
    }
  }
}

} // namespace react
} // namespace facebook

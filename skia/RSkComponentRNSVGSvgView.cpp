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
  SkSVGLengthContext       lengthContext(SkSize::Make(svgContainerSize_.width(), svgContainerSize_.height()));
  SkSVGPresentationContext presentationContext;

#ifdef ENABLE_RSKSVG_RENDER_DEBUG
  printChildList();
#endif /*ENABLE_RSKSVG_RENDER_DEBUG*/

  //1. Svg children are always drawn inside the bounds of parent SVGView conatiner, hence we will clip & draw the children
  // TODO: Consider utilizing Bitmap as an alternative strategy for platforms that have limited memory constraints
  SkAutoCanvasRestore save(canvas, true);
  canvas->clipRect(SkRect::MakeXYWH(lengthContext.resolve(x_, SkSVGLengthContext::LengthType::kHorizontal),
                                    lengthContext.resolve(y_, SkSVGLengthContext::LengthType::kVertical),
                                    svgContainerSize_.width(),
                                    svgContainerSize_.height())
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

  //3. Start render from Root SVG Node
  RNS_LOG_DEBUG("---Start render from Root SVG Node---");
  SkSVGIDMapper    dummyIDMapper; // Deprecated, will be using RSkSVGIDMapper
  INHERITED::render(SkSVGRenderContext(canvas, dummyIDMapper, lengthContext, presentationContext));
  RNS_LOG_DEBUG("---Render completed---");
}

RnsShell::LayerInvalidateMask  RSkComponentRNSVGSvgView::updateComponentProps(SharedProps newViewProps,bool forceUpdate) {

  auto component = getComponentData();
  auto const &newRNSVGViewProps = *std::static_pointer_cast<RNSVGSvgViewProps const>(newViewProps);

#ifdef ENABLE_RSKSVG_PROPS_DEBUG
  RNS_LOG_INFO( " Width :: "<<component.layoutMetrics.frame.size.width<<" Height :: "<<component.layoutMetrics.frame.size.height<< " X:: "<<component.layoutMetrics.frame.origin.x<< " Y:: "<<component.layoutMetrics.frame.origin.y);
  RNS_LOG_INFO("\n" <<
               "===Native Props for SVG Element View==="<< "\n" <<
               "minX      : "<<newRNSVGViewProps.minX << "\n" <<
               "minY      : "<<newRNSVGViewProps.minY << "\n" <<
               "vbWidth   : "<<newRNSVGViewProps.vbWidth << "\n" <<
               "vbHeight  : "<<newRNSVGViewProps.vbHeight << "\n" <<
               "tintColor : "<<newRNSVGViewProps.tintColor << "\n" <<
               "color     : "<<newRNSVGViewProps.color << "\n" <<
               "=======================================");
#endif /*ENABLE_RSKSVG_PROPS_DEBUG*/

  std::string viewBox=std::to_string(newRNSVGViewProps.minX) + " "+ \
                      std::to_string(newRNSVGViewProps.minY)+ " " + \
                      std::to_string(newRNSVGViewProps.vbWidth)+ " " + \
                      std::to_string(newRNSVGViewProps.vbHeight);
  setViewBoxAttribute(SkSVGAttribute::kViewBox,viewBox);

  setColorAttribute(SkSVGAttribute::kColor,newRNSVGViewProps.color);
  setLengthAttribute(SkSVGAttribute::kX,std::to_string(component.layoutMetrics.frame.origin.x));
  setLengthAttribute(SkSVGAttribute::kY,std::to_string(component.layoutMetrics.frame.origin.y));
  setLengthAttribute(SkSVGAttribute::kWidth,std::to_string(component.layoutMetrics.frame.size.width));
  setLengthAttribute(SkSVGAttribute::kHeight,std::to_string(component.layoutMetrics.frame.size.height));

  svgContainerSize_.set(component.layoutMetrics.frame.size.width,
                        component.layoutMetrics.frame.size.height);

  //TODO: ("TO BE CONFIRMED: When the SVG dimensions change, it is unclear whether a remove and insert mount instruction will be received \
  // or an update mount instruction will be received. If an update mount instruction is received,update props will not be called for layout metric changes.");

  return RnsShell::LayerInvalidateAll;
}

bool RSkComponentRNSVGSvgView::onPrepareToRender(SkSVGRenderContext* renderContext) const {
  auto viewPortRect  = renderContext->lengthContext().resolveRect(SkSVGLength(0),SkSVGLength(0),width_,height_);
  auto viewPort      = SkSize::Make(viewPortRect.width(), viewPortRect.height());
  SkMatrix contentMatrix;

  if (!viewBox_.isEmpty()) {
    // A viewBox overrides the intrinsic viewport.
    viewPort = SkSize::Make(viewBox_.width(), viewBox_.height());
    contentMatrix.preConcat(
      SkMatrix::MakeRectToRect(viewBox_, viewPortRect, SkMatrix::kFill_ScaleToFit));
  }
  contentMatrix.postTranslate(renderContext->lengthContext().resolve(x_, SkSVGLengthContext::LengthType::kHorizontal),
                              renderContext->lengthContext().resolve(y_, SkSVGLengthContext::LengthType::kVertical));

  if (!contentMatrix.isIdentity()) {
    renderContext->saveOnce();
    renderContext->canvas()->concat(contentMatrix);
  }

  if (viewPort != renderContext->lengthContext().viewPort()) {
    renderContext->writableLengthContext()->setViewPort(viewPort);
  }

  return this->INHERITED::onPrepareToRender(renderContext);
}

void RSkComponentRNSVGSvgView::onSetAttribute(SkSVGAttribute attr, const SkSVGValue& attrValue) {
  switch (attr) {
    case SkSVGAttribute::kX:
      if (const auto* x = attrValue.as<SkSVGLengthValue>()) {
        x_ = *x;
      }
      break;
    case SkSVGAttribute::kY:
      if (const auto* y = attrValue.as<SkSVGLengthValue>()) {
        y_ = *y;
      }
    break;
    case SkSVGAttribute::kWidth:
      if (const auto* w = attrValue.as<SkSVGLengthValue>()) {
        width_ = *w;
      }
      break;
    case SkSVGAttribute::kHeight:
      if (const auto* h = attrValue.as<SkSVGLengthValue>()) {
        height_ = *h;
      }
      break;
    case SkSVGAttribute::kViewBox:
      if (const auto* vb = attrValue.as<SkSVGViewBoxValue>()) {
        viewBox_=*vb;
      }
      break;
    default:
      this->INHERITED::onSetAttribute(attr, attrValue);
  }
}

} // namespace react
} // namespace facebook

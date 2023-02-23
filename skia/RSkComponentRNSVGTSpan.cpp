/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "RSkComponentRNSVGTSpan.h"


namespace facebook {
namespace react {
namespace RSKSVGTextUtil {

SkScalar getTextAnchorXOffset(SkScalar width, const SkSVGStringType& text_anchor) {

// Default Line = "Start".
  if (strcmp(text_anchor.c_str(), "start") != 0) {
    if (strcmp(text_anchor.c_str(), "middle") == 0) {
      return -(0.5f*width);
    } else if (strcmp(text_anchor.c_str(), "end") == 0) {
      return -width;
    }
  }
  return 0;
}

}//RSKSVGTextUtil

RSkComponentRNSVGTSpan::RSkComponentRNSVGTSpan(const ShadowView &shadowView)
    : INHERITED(shadowView,LAYER_TYPE_VIRTUAL,SkSVGTag::kText) {}

RnsShell::LayerInvalidateMask  RSkComponentRNSVGTSpan::updateComponentProps(SharedProps newViewProps,bool forceUpdate) {

  auto const &newRNSVGTSpanPropsProps = *std::static_pointer_cast<RNSVGTSpanProps const>(newViewProps);
  content_ = newRNSVGTSpanPropsProps.content;
  updateCommonTextProps(newViewProps);
  return RnsShell::LayerInvalidateAll;
}

void RSkComponentRNSVGTSpan::onRender(const SkSVGRenderContext& ctx) const {
  if(content_.size()) {

    ParagraphStyle paragraph_style;

    ParagraphBuilderImpl fillBuilder(paragraph_style, fontCollection_);
    ParagraphBuilderImpl strokeBuilder(paragraph_style, fontCollection_);
    TextStyle textStyle=getContentTextStyle();
    SkPoint frame=getContentDrawCoOrdinates();
    std::unique_ptr<Paragraph> paragraph;

    auto buildAndDrawParagraph =[&](SkPaint* paint,ParagraphBuilderImpl *builder){
      if(paint && builder) {
        paint->setAntiAlias(true);
        textStyle.setForegroundColor(*paint);
        builder->pushStyle(textStyle);
        builder->addText(content_.c_str(), content_.length());
        paragraph = builder->Build();
        paragraph->layout(getContainerSize().width()); // Get Container Size from SVGView
        std::vector<LineMetrics> metrics;
        paragraph->getLineMetrics(metrics);
        SkScalar xOffset{0};
        SkString textAnchor;
        if(getTextAnchor(textAnchor)) {
          auto impl = static_cast<ParagraphImpl*>(paragraph.get());
          xOffset=RSKSVGTextUtil::getTextAnchorXOffset(impl->getBoundaries().width(),textAnchor);
        }
        // SkParagraph draw from TopLeft as like Other Skia components Rect...,which gives Text appear as Hanging Text.As below.
        /*____________________________
          HANGING TEXT LOOKS LIKE THIS
          ____________________________
        */
        // Shifting up Draw Point/Baseline to have behaviour as text written on line/Baseline.
        paragraph->paint(ctx.canvas(), frame.x()+xOffset, frame.y()-metrics[0].fBaseline);
      }
     };

    if (SkPaint* fillPaint = const_cast<SkPaint*>(ctx.fillPaint())) {
      buildAndDrawParagraph(fillPaint,&fillBuilder);
    }
    if (SkPaint* strokePaint = const_cast<SkPaint*>(ctx.strokePaint())) {
      buildAndDrawParagraph(strokePaint,&strokeBuilder);
    }

    if(paragraph) {
      auto impl = static_cast<ParagraphImpl*>(paragraph.get());
      SkRect conentBound=impl->getBoundaries();
      updateContainerContentBounds(SkRect::MakeXYWH(conentBound.x()+frame.x(),
                                                    conentBound.y()+frame.y(),
                                                    conentBound.width(),
                                                    conentBound.height()));
    #ifdef RNS_SVG_TSPAN_PAINT_TEXT_BOUNDS
      std::vector<LineMetrics> metrics;
      paragraph->getLineMetrics(metrics);
      SkRect frameRect= SkRect::MakeXYWH(contentBounds_.front().x(),
                                         contentBounds_.front().y()-metrics[0].fBaseline,
                                         contentBounds_.front().width(),
                                         contentBounds_.front().height()
                                        );
      //Visualize Text Anchor
      SkPaint anchorPaint;
      anchorPaint.setStrokeWidth(3);
      anchorPaint.setColor(SK_ColorRED);
      ctx.canvas()->drawPoint(frameRect.x(), frameRect.y(),anchorPaint);

      // Visualize Text BaseLine, Ascent & Descent
      SkPaint baseLinePaint,ascentPaint,descentPaint;
      baseLinePaint.setColor(SK_ColorGREEN);
      baseLinePaint.setStrokeWidth(2);
      ascentPaint.setColor(SK_ColorBLUE);
      ascentPaint.setStrokeWidth(2);
      descentPaint.setColor(SK_ColorYELLOW);
      descentPaint.setStrokeWidth(2);

      for (auto& metric : metrics) {

        auto x0 = frameRect.x();
        auto x1 = x0+metric.fWidth;
        auto ascentY = metric.fAscent+frameRect.y();
        auto descentY = metric.fDescent+frameRect.y();
        auto baselineY = metric.fBaseline+frameRect.y();

        ctx.canvas()->drawLine(x0, ascentY, x1, ascentY, ascentPaint);
        ctx.canvas()->drawLine(x0, baselineY, x1, baselineY, baseLinePaint);
        ctx.canvas()->drawLine(x0, descentY, x1, descentY, descentPaint);
        RNS_LOG_INFO( " AscentY : [ "<<metric.fAscent <<
                      " ] BaselineY : [ "<<metric.fBaseline<<
                      " ] descentY : [ "<<metric.fDescent<<
                      " ]");
      }
    #endif/*RNS_SVG_TSPAN_PAINT_TEXT_BOUNDS*/
    }
  }
  INHERITED::onRender(ctx);
}

} // namespace react
} // namespace facebook

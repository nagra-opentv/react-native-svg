/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "RSkComponentRNSVGTSpan.h"

namespace facebook {
namespace react {
namespace {

SkScalar getTextAnchorXOffset(SkScalar width, const SkSVGStringType& textAnchor) {

  if(textAnchor == SkString("middle")) {
    return -(0.5f*width);
  } else if(textAnchor == SkString("end")) {
    return -width;
  }
  return 0; // default anchor pt "start/Left"
}

}//namespace

RSkComponentRNSVGTSpan::RSkComponentRNSVGTSpan(const ShadowView &shadowView)
    : INHERITED(shadowView,LAYER_TYPE_VIRTUAL,SkSVGTag::kText) {}

RnsShell::LayerInvalidateMask  RSkComponentRNSVGTSpan::updateComponentProps(SharedProps newViewProps,bool forceUpdate) {

  auto const &newRNSVGTSpanPropsProps = *std::static_pointer_cast<RNSVGTSpanProps const>(newViewProps);
  content_ = newRNSVGTSpanPropsProps.content;
  updateCommonTextProps(newViewProps);

  invalidateParentSvgContainer();

  return RnsShell::LayerInvalidateAll;
}

void RSkComponentRNSVGTSpan::onRender(const SkSVGRenderContext& renderContext) const {
  if(content_.size()) {

    TextStyle textStyle=getContentTextStyle();
    SkPoint frame=getContentDrawCoOrdinates();
    std::unique_ptr<Paragraph> paragraph;

    auto buildAndDrawParagraph =[&](SkPaint* paint,const RNSVGColorFillStruct & colorStruct){
      if(paint) {
        setupPaintForRender(paint,colorStruct,renderContext);
        textStyle.setForegroundColor(*paint);
        textStyle.setDecorationColor(paint->getColor());
        paragraph=buildParagraph(textStyle);
        if(paragraph) {
          SkScalar xOffset{0};
          SkString textAnchor;
          if(getTextAnchor(textAnchor)) {
            auto impl = static_cast<ParagraphImpl*>(paragraph.get());
            xOffset=getTextAnchorXOffset(impl->getBoundaries().width(),textAnchor);
          }
          // SkParagraph draw from TopLeft as like Other Skia components Rect...,which gives Text appear as Hanging Text.As below.
          /*____________________________
            HANGING TEXT LOOKS LIKE THIS
            ____________________________
          */
          // Shifting up Draw Point/Baseline to have behavior as text written on line/Baseline.
          std::vector<LineMetrics> metrics;
          paragraph->getLineMetrics(metrics);
          paragraph->paint(renderContext.canvas(), frame.x()+xOffset, frame.y()-metrics[0].fBaseline);
        }
      }
    };

    if (SkPaint* fillPaint = const_cast<SkPaint*>(renderContext.fillPaint())) {
      buildAndDrawParagraph(fillPaint,fillColor);
    }
    if (SkPaint* strokePaint = const_cast<SkPaint*>(renderContext.strokePaint())) {
      buildAndDrawParagraph(strokePaint,strokeColor);
    }

    if(paragraph) {
      auto impl = static_cast<ParagraphImpl*>(paragraph.get());
      SkRect contentBound=impl->getBoundaries();
      updateContainerContentBounds(SkRect::MakeXYWH(contentBound.x()+frame.x(),
                                                    contentBound.y()+frame.y(),
                                                    contentBound.width(),
                                                    contentBound.height()));
    #ifdef RNS_SVG_TSPAN_PAINT_TEXT_BOUNDS
      std::vector<LineMetrics> metrics;
      paragraph->getLineMetrics(metrics);
      SkRect frameRect= SkRect::MakeXYWH(containerContentBounds_.front().x(),
                                         containerContentBounds_.front().y()-metrics[0].fBaseline,
                                         containerContentBounds_.front().width(),
                                         containerContentBounds_.front().height()
                                        );
      //Visualize Text Anchor
      SkPaint anchorPaint;
      anchorPaint.setStrokeWidth(3);
      anchorPaint.setColor(SK_ColorRED);
      renderContext.canvas()->drawPoint(frameRect.x(), frameRect.y(),anchorPaint);

      // Visualize Text BaseLine, Ascent & Descent
      SkPaint baseLinePaint,ascentPaint,descentPaint;
      baseLinePaint.setColor(SK_ColorGREEN);
      baseLinePaint.setStrokeWidth(2);
      ascentPaint.setColor(SK_ColorBLUE);
      ascentPaint.setStrokeWidth(2);
      descentPaint.setColor(SK_ColorYELLOW);
      descentPaint.setStrokeWidth(2);

      for (auto& metric : metrics) {

        auto startPtX = frameRect.x();
        auto endtPtX = startPtX+metric.fWidth;
        auto ascentY = metric.fAscent+frameRect.y();
        auto descentY = metric.fDescent+frameRect.y();
        auto baselineY = metric.fBaseline+frameRect.y();

        ctx.canvas()->drawLine(startPtX, ascentY, endtPtX, ascentY, ascentPaint);
        ctx.canvas()->drawLine(startPtX, baselineY, endtPtX, baselineY, baseLinePaint);
        ctx.canvas()->drawLine(startPtX, descentY, endtPtX, descentY, descentPaint);
        RNS_LOG_INFO( " AscentY : [ "<<metric.fAscent <<
                      " ] BaselineY : [ "<<metric.fBaseline<<
                      " ] descentY : [ "<<metric.fDescent<<
                      " ]");
      }
    #endif/*RNS_SVG_TSPAN_PAINT_TEXT_BOUNDS*/
    }
  }
  INHERITED::onRender(renderContext);
}

std::unique_ptr<Paragraph> RSkComponentRNSVGTSpan::buildParagraph(TextStyle  textStyle) const{

  ParagraphStyle paraStyle;
  paraStyle.setMaxLines(1);//Svg text content to be presented in single line.
  ParagraphBuilderImpl builder(paraStyle, fontCollection_);
  std::unique_ptr<Paragraph> paragraph;

  builder.pushStyle(textStyle);
  builder.addText(content_.c_str(), content_.length());
  paragraph = builder.Build();
  if(paragraph) {
    paragraph->layout(getContainerSize().width());
  }

  return paragraph;
}

SkRect RSkComponentRNSVGTSpan::getObjectBoundingBox(const SkSVGLengthContext& ) const{

  if(content_.size()) {
    std::unique_ptr<Paragraph> paragraph = buildParagraph(getContentTextStyle());
    auto impl = static_cast<ParagraphImpl*>(paragraph.get());
    return impl->getBoundaries();
  }
  return SkRect::MakeEmpty();

}

} // namespace react
} // namespace facebook

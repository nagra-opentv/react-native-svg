/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "RSkComponentRNSVGTSpan.h"


namespace facebook {
namespace react {

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
    TextStyle textStyle=getTextStyle();
    SkRect frame=getContentFrame();
    std::unique_ptr<Paragraph> paragraph;

    if (SkPaint* fillPaint = const_cast<SkPaint*>(ctx.fillPaint())) {
      fillPaint->setAntiAlias(true);
      textStyle.setForegroundColor(*ctx.fillPaint());
      fillBuilder.pushStyle(textStyle);
      fillBuilder.addText(content_.c_str(), content_.length());
      paragraph = fillBuilder.Build();
      paragraph->layout(getContainerSize().width()); // Get Container Size from SVGView
      paragraph->paint(ctx.canvas(), frame.x(), frame.y());
    }
    if (SkPaint* strokePaint = const_cast<SkPaint*>(ctx.strokePaint())) {
      strokePaint->setAntiAlias(true);
      textStyle.setForegroundColor(*ctx.strokePaint());
      strokeBuilder.pushStyle(textStyle);
      strokeBuilder.addText(content_.c_str(), content_.length());
      paragraph = strokeBuilder.Build();
      paragraph->layout(getContainerSize().width()); // Get Container Size from SVGView
      paragraph->paint(ctx.canvas(), frame.x(), frame.y());
    }
    if(paragraph) {
      auto impl = static_cast<ParagraphImpl*>(paragraph.get());
      contentBounds_=SkRect::MakeXYWH(impl->getBoundaries().x()+frame.x(),
                                      impl->getBoundaries().y()+frame.y(),
                                      impl->getBoundaries().width(),
                                      impl->getBoundaries().height());

    #ifdef PAINT_TEXT_BOUNDS
      SkPaint boundsPaint;
      boundsPaint.setColor(SK_ColorGREEN);
      boundsPaint.setStrokeWidth(5);
      boundsPaint.setStyle(SkPaint::kStroke_Style);
      ctx.canvas()->drawRect(impl->getBoundaries(),boundsPaint);
    #endif/*PAINT_TEXT_BOUNDS*/
    }
  }
  updateContainerContentBounds(contentBounds_);
  INHERITED::onRender(ctx);
}

} // namespace react
} // namespace facebook

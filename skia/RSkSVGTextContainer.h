/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */
#pragma once

#include <vector>

#include "modules/skparagraph/include/Paragraph.h"
#include "modules/skparagraph/include/ParagraphBuilder.h"
#include "modules/skparagraph/src/ParagraphBuilderImpl.h"
#include "modules/skparagraph/src/ParagraphImpl.h"

#include "RSkSVGContainer.h"
#include "RSkSVGTextPropsHelper.h"

namespace facebook {
namespace react {

class RSkSVGTextContainer : public RSkSVGContainer {
 public:

  ~RSkSVGTextContainer() override{};
  void mountChildComponent(std::shared_ptr<RSkComponent> newChildComponent, const int index)override;
  void updateCommonTextProps(SharedProps newViewProps);

 protected:

  explicit RSkSVGTextContainer(const ShadowView &shadowView,
                               RnsShell::LayerType layerType,
                               SkSVGTag tag);

  void onSetAttribute(SkSVGAttribute attr, const SkSVGValue& attrValue) override;
  void onSetRSkSVGAttribute(RSkSVGAttribute attr, const SkSVGValue& attrValue);
  void setTextParent(RSkSVGNode * rootNode);
  TextStyle getContentTextStyle() const;
  SkPoint getContentDrawCoOrdinates()const;
  void updateContainerContentBounds(SkRect frame)const;

  sk_sp<skia::textlayout::FontCollection> fontCollection_;
  RSkSVGNode * textParentNode_{nullptr};
  mutable std::vector<SkRect> containerContentBounds_;

  RNS_SVG_TEXT_POSITION_ATTR(PositionX,SkSVGLength)
  RNS_SVG_TEXT_POSITION_ATTR(PositionY,SkSVGLength)
  RNS_SVG_TEXT_POSITION_DELTA_ATTR(DeltaX,SkSVGLength)
  RNS_SVG_TEXT_POSITION_DELTA_ATTR(DeltaY,SkSVGLength)
  RNS_SVG_TEXT_ATTR(FontSize,SkSVGLength)
  RNS_SVG_TEXT_ATTR(FontWeight,SkString)
  RNS_SVG_TEXT_ATTR(FontStyle,SkString)
  RNS_SVG_TEXT_ATTR(FontFamily,SkString)
  RNS_SVG_TEXT_ATTR(FontStretch,SkString)
  RNS_SVG_TEXT_ATTR(LetterSpacing,SkSVGLength)
  RNS_SVG_TEXT_ATTR(WordSpacing,SkSVGLength)
  RNS_SVG_TEXT_ATTR(TextAnchor,SkString)
  RNS_SVG_TEXT_ATTR(TextDecoration,SkString)

 private:

  typedef RSkSVGContainer INHERITED;

};

} // namespace react
} // namespace facebook




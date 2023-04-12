/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once


#include "RSkSVGTextContainer.h"

namespace facebook {
namespace react {

class RSkComponentRNSVGTSpan final : public RSkSVGTextContainer {
 public:

  RSkComponentRNSVGTSpan(const ShadowView &shadowView);
  ~RSkComponentRNSVGTSpan() {}

  SkRect getObjectBoundingBox(const SkSVGLengthContext&) const override;

 // Override for Base class : RSkComponent
  RnsShell::LayerInvalidateMask updateComponentProps(SharedProps newViewProps,bool forceUpdate) override;

 protected:

  std::string content_;
  void onRender(const SkSVGRenderContext&) const override;

 private:
  std::unique_ptr<Paragraph> buildParagraph(TextStyle textStyle) const;
  typedef RSkSVGTextContainer INHERITED;
};

} // namespace react
} // namespace facebook

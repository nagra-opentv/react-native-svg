/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once


#include "RSkSVGContainer.h"
#include "RSkSVGNode.h"

namespace facebook {
namespace react {

class RSkComponentRNSVGSvgView final : public RSkSVGContainer  {
 public:

  RSkComponentRNSVGSvgView(const ShadowView &shadowView);
  ~RSkComponentRNSVGSvgView() {}
  //Override for Base Class :RSkComponent
  RnsShell::LayerInvalidateMask updateComponentProps(SharedProps newViewProps,bool forceUpdate) override;
  SkSize getContainerSize() const override { return svgContainerSize_;}

 protected:

  //Overrides for Base Class :RSkComponent
  void OnPaint(SkCanvas *canvas) override;

  //Overrides for Base Class :RSkSVGContainer
  bool onPrepareToRender(SkSVGRenderContext*) const override;
  void onSetAttribute(SkSVGAttribute, const SkSVGValue&) override;

 private:

  SkSize       svgContainerSize_;

  SkSVGLength x_    = SkSVGLength(0);
  SkSVGLength y_    = SkSVGLength(0);
  SkSVGLength width_  = SkSVGLength(100, SkSVGLength::Unit::kPercentage);
  SkSVGLength height_ = SkSVGLength(100, SkSVGLength::Unit::kPercentage);
  SkRect viewBox_;

  void alterSkiaDefaultPaint();

  typedef RSkSVGContainer INHERITED;
};

} // namespace react
} // namespace facebook

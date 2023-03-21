/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include "include/effects/SkGradientShader.h"

#include "RSkSVGHiddenContainer.h"

namespace facebook {
namespace react {

class RSkComponentRNSVGLinearGradient final : public RSkSVGHiddenContainer {
 public:

  RSkComponentRNSVGLinearGradient(const ShadowView &shadowView);
  ~RSkComponentRNSVGLinearGradient() {}

  // Override for Base class : RSkComponent
  RnsShell::LayerInvalidateMask updateComponentProps(SharedProps newViewProps,bool forceUpdate) override;

  sk_sp<SkShader> getShader(const SkSVGRenderContext& ctx);

 protected:

  // Override for Base class : RSkSvgNode
  void onSetAttribute(SkSVGAttribute, const SkSVGValue&) override;

 private:

  SkSVGLength x1_ = SkSVGLength(0);
  SkSVGLength y1_ = SkSVGLength(0);
  SkSVGLength x2_ = SkSVGLength(0);
  SkSVGLength y2_ = SkSVGLength(0);
  SkMatrix gradientTransforMatrix_;
  std::vector<SkScalar> stopOffset_;
  std::vector<SkColor> stopColor_;

  typedef RSkSVGHiddenContainer INHERITED;

};

} // namespace react
} // namespace facebook

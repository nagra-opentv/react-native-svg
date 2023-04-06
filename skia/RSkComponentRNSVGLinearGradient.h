/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include "include/effects/SkGradientShader.h"

#include "RSkSVGComponentNode.h"

namespace facebook {
namespace react {

class RSkComponentRNSVGLinearGradient final : public RSkSVGComponentNode {
 public:

  RSkComponentRNSVGLinearGradient(const ShadowView &shadowView);
  ~RSkComponentRNSVGLinearGradient() {}

  // Override for Base class : RSkComponent
  RnsShell::LayerInvalidateMask updateComponentProps(SharedProps newViewProps,bool forceUpdate) override;

  sk_sp<SkShader> getShader(const SkSVGLengthContext& ctx,SkRect boundingBox);

 protected:

  // Override for Base class : RSkSvgNode
  void onSetAttribute(SkSVGAttribute, const SkSVGValue&) override;
  void onRender(const SkSVGRenderContext&) const override;

 private:

  SkSVGLength x1_ = SkSVGLength(0);
  SkSVGLength y1_ = SkSVGLength(0);
  SkSVGLength x2_ = SkSVGLength(0);
  SkSVGLength y2_ = SkSVGLength(0);
  SkMatrix gradientTransforMatrix_;
  std::vector<SkScalar> stopOffsets_;
  std::vector<SkColor> stopColors_;
  int gradientUnit_{0};

  typedef RSkSVGComponentNode INHERITED;

};

} // namespace react
} // namespace facebook

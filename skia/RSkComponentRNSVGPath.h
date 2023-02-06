/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include "RSkSVGShape.h"

namespace facebook {
namespace react {

class RSkComponentRNSVGPath final : public RSkSVGShape{
 public:

  RSkComponentRNSVGPath(const ShadowView &shadowView);
  ~RSkComponentRNSVGPath() override {};

  // Override for Base class : RSkComponent
  RnsShell::LayerInvalidateMask updateComponentProps(SharedProps newViewProps,bool forceUpdate) override;

 protected:

  // Overrides for Base class : RSkSVGShape
  void onSetAttribute(SkSVGAttribute, const SkSVGValue&) override;
  void onDraw(SkCanvas*, const SkSVGLengthContext&, const SkPaint&,SkPathFillType) const override;

 private:

  mutable SkPath path_; // mutated in onDraw(), to apply inherited fill types.

  typedef RSkSVGShape INHERITED;
};

} // namespace react
} // namespace facebook

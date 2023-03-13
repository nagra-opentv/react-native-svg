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

class RSkComponentRNSVGRect final : public RSkSVGShape{
 public:

  RSkComponentRNSVGRect(const ShadowView &shadowView);
  ~RSkComponentRNSVGRect() {}

  // Override for Base class : RSkComponent
  RnsShell::LayerInvalidateMask updateComponentProps(SharedProps newViewProps,bool forceUpdate) override;

 protected:

  // Overrides for Base class : RSkSVGShape
  void onDraw(SkCanvas*, const SkSVGLengthContext&, const SkPaint&,SkPathFillType) const override;
  void onSetAttribute(SkSVGAttribute, const SkSVGValue&) override;

 private:

  SkSVGLength x_    = SkSVGLength(0);
  SkSVGLength y_    = SkSVGLength(0);
  SkSVGLength width_  = SkSVGLength(0);
  SkSVGLength height_ = SkSVGLength(0);
  SkSVGLength rx_   = SkSVGLength(0);
  SkSVGLength ry_   = SkSVGLength(0);

  typedef RSkSVGShape INHERITED;
};

} // namespace react
} // namespace facebook

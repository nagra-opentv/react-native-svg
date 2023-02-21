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

class RSkComponentRNSVGCircle final : public RSkSVGShape{
 public:

  RSkComponentRNSVGCircle(const ShadowView &shadowView);
  ~RSkComponentRNSVGCircle() override {};

  // Override for Base Class: RSkComponent
  RnsShell::LayerInvalidateMask updateComponentProps(SharedProps newViewProps,bool forceUpdate) override;

 protected:

  void onDraw(SkCanvas*, const SkSVGLengthContext&, const SkPaint&,SkPathFillType) const override;
  void onSetAttribute(SkSVGAttribute, const SkSVGValue&) override;

 private:

  SkSVGLength cx_ = SkSVGLength(0);
  SkSVGLength cy_ = SkSVGLength(0);
  SkSVGLength r_  = SkSVGLength(0);

  typedef RSkSVGShape INHERITED;

};

} // namespace react
} // namespace facebook

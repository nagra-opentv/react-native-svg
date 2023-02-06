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

class RSkComponentRNSVGEllipse final : public RSkSVGShape{
 public:

  RSkComponentRNSVGEllipse(const ShadowView &shadowView);
  ~RSkComponentRNSVGEllipse() override {};

  // Overrides for Base class : RSkComponent
  RnsShell::LayerInvalidateMask updateComponentProps(SharedProps newViewProps,bool forceUpdate) override;

 protected:

  // Overrides for Base class : RSkSVGShape
  void onDraw(SkCanvas*, const SkSVGLengthContext&, const SkPaint&,SkPathFillType) const override;
  void onSetAttribute(SkSVGAttribute, const SkSVGValue&) override;

 private:

  SkSVGLength cx_ = SkSVGLength(0);
  SkSVGLength cy_ = SkSVGLength(0);
  SkSVGLength rx_ = SkSVGLength(0);
  SkSVGLength ry_ = SkSVGLength(0);

  void  setNativeProps(const RNSVGEllipseProps &nativeProps);

  typedef RSkSVGShape INHERITED;
};

} // namespace react
} // namespace facebook

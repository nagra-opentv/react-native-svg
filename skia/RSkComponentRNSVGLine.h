/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include "RSkSVGShapeComponent.h"

namespace facebook {
namespace react {

using namespace std;

class RSkComponentRNSVGLine final : public RSkSVGShapeComponent{
 public:

  RSkComponentRNSVGLine(const ShadowView &shadowView);
  ~RSkComponentRNSVGLine() = default;

  // Override for Base class : RSkComponent
  RnsShell::LayerInvalidateMask updateComponentProps(SharedProps newViewProps,bool forceUpdate) override;

 protected:

  // Overrides for Base class : RSkSVGShape
  void onDraw(SkCanvas*, const SkSVGLengthContext&, const SkPaint&,SkPathFillType) const override;
  void onSetAttribute(SkSVGAttribute, const SkSVGValue&) override;

 private:

    SkSVGLength x1_ = SkSVGLength(0);
    SkSVGLength y1_ = SkSVGLength(0);
    SkSVGLength x2_ = SkSVGLength(0);
    SkSVGLength y2_ = SkSVGLength(0);

    RnsShell::LayerInvalidateMask  setNativeProps(const RNSVGLineProps &nativeProps);

    typedef RSkSVGShapeComponent INHERITED;

};

} // namespace react
} // namespace facebook

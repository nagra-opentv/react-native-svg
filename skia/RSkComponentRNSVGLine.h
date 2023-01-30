/*
 * Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include "ReactSkia/components/RSkComponent.h"

#include "RSkSVGShape.h"

namespace facebook {
namespace react {

using namespace std;

class RSkComponentRNSVGLine final : public RSkComponent,public RSkSVGShape{
 public:

  RSkComponentRNSVGLine(const ShadowView &shadowView);
  ~RSkComponentRNSVGLine() = default;

// Overrides for Base class : RSkComponent
  RnsShell::LayerInvalidateMask updateComponentProps(SharedProps newViewProps,bool forceUpdate) override;
  void mountChildComponent(std::shared_ptr<RSkComponent> newChildComponent,const int index)override;
  void unmountChildComponent(std::shared_ptr<RSkComponent> oldChildComponent,const int index)override;

 protected:

// Overrides for Base class : RSkComponent
  void OnPaint(SkCanvas *canvas) override{};

// Overrides for Base class : RSkSVGShape
  void onDraw(SkCanvas*, const SkSVGLengthContext&, const SkPaint&,SkPathFillType) const override;
  void onSetAttribute(SkSVGAttribute, const SkSVGValue&) override;

 private:

    SkSVGLength x1 = SkSVGLength(0);
    SkSVGLength y1 = SkSVGLength(0);
    SkSVGLength x2 = SkSVGLength(0);
    SkSVGLength y2 = SkSVGLength(0);

    typedef RSkSVGShape INHERITED;

};

} // namespace react
} // namespace facebook

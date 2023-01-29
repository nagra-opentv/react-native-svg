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

class RSkComponentRNSVGPath final : public RSkComponent,public RSkSVGShape{
  public:
    RSkComponentRNSVGPath(const ShadowView &shadowView);
    ~RSkComponentRNSVGPath() = default;

    RnsShell::LayerInvalidateMask updateComponentProps(SharedProps newViewProps,bool forceUpdate) override;
    void mountChildComponent(std::shared_ptr<RSkComponent> newChildComponent, const int index)override;
   // sk_sp<RSkSVGNode> getComponentNode(){ return this;}

  protected:
    void OnPaint(SkCanvas *canvas) override {};

    void onSetAttribute(SkSVGAttribute, const SkSVGValue&) override;
    void onDraw(SkCanvas*, const SkSVGLengthContext&, const SkPaint&,SkPathFillType) const override;

  private:
    mutable SkPath path_; // mutated in onDraw(), to apply inherited fill types.

    typedef RSkSVGShape INHERITED;
};

} // namespace react
} // namespace facebook

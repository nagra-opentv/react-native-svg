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

class RSkComponentRNSVGRect final : public RSkComponent,public RSkSVGShape{
  public:
    RSkComponentRNSVGRect(const ShadowView &shadowView);
    ~RSkComponentRNSVGRect() = default;

    RnsShell::LayerInvalidateMask updateComponentProps(const ShadowView &newShadowView,bool forceUpdate) override;
    void mountChildComponent(std::shared_ptr<RSkComponent> newChildComponent, const int index)override;

    sk_sp<RSkSVGNode> getComponentNode(){ return selfNode;}

  protected:
    void OnPaint(SkCanvas *canvas) override {};

    void onDraw(SkCanvas*, const SkSVGLengthContext&, const SkPaint&,SkPathFillType) const override;
    void onSetAttribute(SkSVGAttribute, const SkSVGValue&) override;

  private:
    sk_sp<RSkSVGNode> selfNode;
    SkSVGLength x_      = SkSVGLength(0);
    SkSVGLength y_      = SkSVGLength(0);
    SkSVGLength width_  = SkSVGLength(0);
    SkSVGLength height_ = SkSVGLength(0);
    SkSVGLength rx_     = SkSVGLength(0);
    SkSVGLength ry_     = SkSVGLength(0);

   typedef RSkSVGShape INHERITED;
};

} // namespace react
} // namespace facebook

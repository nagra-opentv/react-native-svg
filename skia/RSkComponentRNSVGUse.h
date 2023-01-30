/*
 * Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "ReactSkia/components/RSkComponent.h"

#include "RSkSVGNode.h"

namespace facebook {
namespace react {

class RSkComponentRNSVGUse: public RSkComponent,public RSkSVGNode {
  public:

    RSkComponentRNSVGUse(const ShadowView &shadowView);
    ~RSkComponentRNSVGUse() = default;

// Overrides for Base class : RSkComponent
  RnsShell::LayerInvalidateMask updateComponentProps(SharedProps newViewProps,bool forceUpdate) override;
  void mountChildComponent(std::shared_ptr<RSkComponent> newChildComponent,const int index)override;
  void unmountChildComponent(std::shared_ptr<RSkComponent> oldChildComponent,const int index)override;

  protected:
// Overrides for Base class : RSkComponent
    void OnPaint(SkCanvas *canvas) override{};

// Overrides for Base class : RSkSVGNode
    void onSetAttribute(SkSVGAttribute, const SkSVGValue&) override;
    bool onPrepareToRender(SkSVGRenderContext*) const override;
    void onRender(const SkSVGRenderContext&) const override;

private:

    SkSVGStringType    href_;
    SkSVGLength        x_ = SkSVGLength(0);
    SkSVGLength        y_ = SkSVGLength(0);

    typedef RSkSVGNode INHERITED;
};

} // namespace react
} // namespace facebook
/*
 * Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "ReactSkia/components/RSkComponent.h"
#include "experimental/svg/model/SkSVGNode.h"

#include "RSkSVGNode.h"

namespace facebook {
namespace react {

class RSkComponentRNSVGUse: public RSkComponent,public SkSVGNode,public RSkSVGNode {
  public:
    RSkComponentRNSVGUse(const ShadowView &shadowView);
    ~RSkComponentRNSVGUse() = default;

    RnsShell::LayerInvalidateMask updateComponentProps(const ShadowView &newShadowView,bool forceUpdate) override;
    void mountChildComponent(std::shared_ptr<RSkComponent> newChildComponent, const int index)override;

    void appendChild(sk_sp<SkSVGNode>) override;

    sk_sp<SkSVGNode> getComponentNode(){ return selfNode;}

  protected:
    void OnPaint(SkCanvas *canvas) override{};
    void onSetAttribute(SkSVGAttribute, const SkSVGValue&) override;
    bool onPrepareToRender(SkSVGRenderContext*) const override;
    void onRender(const SkSVGRenderContext&) const override;
    SkPath onAsPath(const SkSVGRenderContext&) const override;

private:

    sk_sp<SkSVGNode> selfNode;

    SkSVGStringType    href_;
    SkSVGLength        x_ = SkSVGLength(0);
    SkSVGLength        y_ = SkSVGLength(0);

    typedef SkSVGNode INHERITED;
};

} // namespace react
} // namespace facebook
/*
 * Copyright (C) 1994-present OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */
#pragma once

#include "ReactSkia/components/RSkComponent.h"
#include "RSkSVGHiddenContainer.h"

namespace facebook {
namespace react {

class RSkComponentRNSVGDefs: public RSkComponent,public RSkSVGHiddenContainer {
  public:
    RSkComponentRNSVGDefs(const ShadowView &shadowView);
    ~RSkComponentRNSVGDefs() = default;
  
    RnsShell::LayerInvalidateMask updateComponentProps(const ShadowView &newShadowView,bool forceUpdate) override;
    void mountChildComponent(std::shared_ptr<RSkComponent> newChildComponent,const int index)override;
    sk_sp<RSkSVGNode> getComponentNode(){ return selfNode;}

  protected:
    void OnPaint(SkCanvas *canvas) override {};

  private:
    sk_sp<RSkSVGNode> selfNode;

    typedef RSkSVGHiddenContainer INHERITED;
};

} // namespace react
} // namespace facebook
/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */
#pragma once

#include <vector>

#include "ReactSkia/components/RSkComponent.h"
#include "RSkSVGNode.h"

namespace facebook {
namespace react {

class RSkSVGContainerComponent : public RSkComponent,public RSkSVGNode {
  public:

    ~RSkSVGContainerComponent() override;

  //Overrides for Base Class :RSkComponent
  void mountChildComponent(std::shared_ptr<RSkComponent> newChildComponent, const int index)override;
  void unmountChildComponent(std::shared_ptr<RSkComponent> oldChildComponent,const int index)override;

  protected:

    explicit RSkSVGContainerComponent(const ShadowView &shadowView,
                                  RnsShell::LayerType layerType,
                                  SkSVGTag);

    //Override for Base Class :RSkComponent
    void OnPaint(SkCanvas *canvas) override;
  
    //Override for Base Class :RSkSVGNode
    void onRender(const SkSVGRenderContext&) const override;
    bool hasChildren() const final;

    void printChildList();

    SkSVGIDMapper    nodeIDMapper_;
    std::vector<sk_sp<SkSVGNode>> childRSkNodeList_;

  private:
  
};

} // namespace react
} // namespace facebook




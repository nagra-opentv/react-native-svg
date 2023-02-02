/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include "include/core/SkCanvas.h"
#include "include/core/SkPaint.h"

#include "ReactSkia/components/RSkComponent.h"
#include "RSkSVGNode.h"

using namespace std;

namespace facebook {
namespace react {

class RSkSVGShapeComponent : public RSkComponent,public RSkSVGNode {
  public:

    ~RSkSVGShapeComponent() = default;

  // Overrides for Base Class: RSkComponent
  void mountChildComponent(std::shared_ptr<RSkComponent> newChildComponent, const int index)override;
  void unmountChildComponent(std::shared_ptr<RSkComponent> oldChildComponent,const int index)override;

  protected:

    explicit RSkSVGShapeComponent(const ShadowView &shadowView,
                                  RnsShell::LayerType layerType,
                                  SkSVGTag);

    // Override for Base Class: RSkComponent
    void OnPaint(SkCanvas *canvas) override;

    void onRender(const SkSVGRenderContext&) const final;
    virtual void onDraw(SkCanvas*, const SkSVGLengthContext&, const SkPaint&,SkPathFillType) const = 0;

  private:

};

} // namespace react
} // namespace facebook
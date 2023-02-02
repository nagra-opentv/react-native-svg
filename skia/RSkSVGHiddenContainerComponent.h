/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */
#pragma once

#include "RSkSVGContainerComponent.h"

namespace facebook {
namespace react {

class RSkSVGHiddenContainerComponent : public RSkSVGContainerComponent {
  protected:

    explicit RSkSVGHiddenContainerComponent(const ShadowView &shadowView,
                                  RnsShell::LayerType layerType,
                                  SkSVGTag t) :
                       RSkSVGContainerComponent(shadowView,layerType,t) {}

    void onRender(const SkSVGRenderContext&) const final {}

  private:

};

} // namespace react
} // namespace facebook
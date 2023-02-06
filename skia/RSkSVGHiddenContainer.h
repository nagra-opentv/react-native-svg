/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */
#pragma once

#include "RSkSVGContainer.h"

namespace facebook {
namespace react {

class RSkSVGHiddenContainer : public RSkSVGContainer {
 protected:

  explicit RSkSVGHiddenContainer(const ShadowView &shadowView,
                                 RnsShell::LayerType layerType,
                                 SkSVGTag t) :
                       RSkSVGContainer(shadowView,layerType,t) {}

  void onRender(const SkSVGRenderContext&) const final {}

 private:

};

} // namespace react
} // namespace facebook
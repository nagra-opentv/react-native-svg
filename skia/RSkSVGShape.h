/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include "RSkSVGComponentNode.h"

namespace facebook {
namespace react {

class RSkSVGShape : public RSkSVGComponentNode {
 public:

  ~RSkSVGShape() {}

 protected:

  explicit RSkSVGShape(const ShadowView &shadowView,
                       RnsShell::LayerType layerType,
                       SkSVGTag);

  void onRender(const SkSVGRenderContext&) const final;
  virtual void onDraw(SkCanvas*, const SkSVGLengthContext&, const SkPaint&,SkPathFillType) const = 0;

 private:

  typedef RSkSVGComponentNode INHERITED;
};

} // namespace react
} // namespace facebook
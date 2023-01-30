/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include "include/core/SkCanvas.h"
#include "include/core/SkPaint.h"

#include "RSkSVGNode.h"

using namespace std;

namespace facebook {
namespace react {

class RSkSVGShape : public RSkSVGNode {
  public:

    ~RSkSVGShape() = default;

  protected:

    explicit RSkSVGShape(SkSVGTag);

    void onRender(const SkSVGRenderContext&) const final;
    virtual void onDraw(SkCanvas*, const SkSVGLengthContext&, const SkPaint&,SkPathFillType) const = 0;

  private:

    typedef RSkSVGNode INHERITED;
};

} // namespace react
} // namespace facebook
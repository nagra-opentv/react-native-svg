/*
 * Copyright (C) 1994-present OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include "include/core/SkPath.h"

#include "ReactSkia/components/RSkComponent.h"
#include "RSkSVGNode.h"

using namespace std;

namespace facebook {
namespace react {

class RSkSVGShape : public RSkSVGNode {
  public:
    ~RSkSVGShape() = default;

    void appendChild(std::shared_ptr<RSkComponent> childComponent) override;

  protected:
    RSkSVGShape(SkSVGTag);

    void onRender(const SkSVGRenderContext&) const final;
    virtual void onDraw(SkCanvas*, const SkSVGLengthContext&, const SkPaint&,SkPathFillType) const = 0;
  private:
    typedef RSkSVGNode INHERITED;
};

} // namespace react
} // namespace facebook
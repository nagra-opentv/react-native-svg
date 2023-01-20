/*
 * Copyright (C) 1994-present OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include "include/core/SkPath.h"

#include "ReactSkia/components/RSkComponent.h"
#include "experimental/svg/model/SkSVGTransformableNode.h"
#include "RSkSVGNode.h"

using namespace std;

namespace facebook {
namespace react {

class RSkSVGShape : public SkSVGTransformableNode,public RSkSVGNode{
  public:
    ~RSkSVGShape() = default;

    void appendChild(sk_sp<SkSVGNode>) override;

  protected:
    RSkSVGShape(SkSVGTag);
    SkPath onAsPath(const SkSVGRenderContext&)  const override { SkPath path;return path; };
    void onRender(const SkSVGRenderContext&) const final;
    virtual void onDraw(SkCanvas*, const SkSVGLengthContext&, const SkPaint&,SkPathFillType) const = 0;
  private:
    typedef SkSVGTransformableNode INHERITED;
};

} // namespace react
} // namespace facebook
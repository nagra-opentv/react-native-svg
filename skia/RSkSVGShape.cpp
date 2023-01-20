/*
 * Copyright (C) 1994-present OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "experimental/svg/model/SkSVGRenderContext.h"
#include "RSkSVGShape.h"
#include "include/core/SkCanvas.h"

using namespace std;

namespace facebook {
namespace react {

RSkSVGShape::RSkSVGShape(SkSVGTag t) : INHERITED(t) {}

void RSkSVGShape::onRender(const SkSVGRenderContext& ctx) const {
    const auto fillType = ctx.presentationContext().fInherited.fFillRule->asFillType();

    if (const SkPaint* fillPaint = ctx.fillPaint()) {
        this->onDraw(ctx.canvas(), ctx.lengthContext(), *fillPaint, fillType);
    }

    if (const SkPaint* strokePaint = ctx.strokePaint()) {
        this->onDraw(ctx.canvas(), ctx.lengthContext(), *strokePaint, fillType);
    }

    SkMatrix matrix=ctx.canvas()->getTotalMatrix();
	printf("\n getScaleX [%f]\n",matrix.getScaleX());
	printf("\n getScaleY [%f]\n",matrix.getScaleY());
	printf("\n getTranslateX [%f]\n",matrix.getTranslateX());
	printf("\n getTranslateY [%f]\n",matrix.getTranslateY());
	printf("\n getSkewX [%f]\n",matrix.getSkewX());
	printf("\n getSkewY [%f]\n",matrix.getSkewY());

}

void RSkSVGShape::appendChild(sk_sp<SkSVGNode>) {
    printf("cannot append child nodes to an SVG shape.\n");
}

} // namespace react
} // namespace facebook
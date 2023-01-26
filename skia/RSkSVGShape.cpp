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
	RNS_LOG_INFO(" getScaleX "<<matrix.getScaleX());
	RNS_LOG_INFO(" getScaleY "<<matrix.getScaleY());
	RNS_LOG_INFO(" getTranslateX "<<matrix.getTranslateX());
	RNS_LOG_INFO(" getTranslateY "<<matrix.getTranslateY());
	RNS_LOG_INFO(" getSkewX "<<matrix.getSkewX());
	RNS_LOG_INFO(" getSkewY "<<matrix.getSkewY());

}

} // namespace react
} // namespace facebook
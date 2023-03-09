/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "RSkSVGShape.h"

namespace facebook {
namespace react {

RSkSVGShape::RSkSVGShape(const ShadowView &shadowView,
                                           RnsShell::LayerType layerType,
                                           SkSVGTag tag)
    : INHERITED(shadowView,layerType,tag){}

void RSkSVGShape::onRender(const SkSVGRenderContext& ctx) const {

  const auto fillType = ctx.presentationContext().fInherited.fFillRule->asFillType();

  if (SkPaint* fillPaint = const_cast<SkPaint*>(ctx.fillPaint())) {
    fillPaint->setAntiAlias(true);
    this->onDraw(ctx.canvas(), ctx.lengthContext(), *fillPaint, fillType);
  }
  if (SkPaint* strokePaint = const_cast<SkPaint*>(ctx.strokePaint())) {
    strokePaint->setAntiAlias(true);
    this->onDraw(ctx.canvas(), ctx.lengthContext(), *strokePaint, fillType);
  }

  SkMatrix matrix=ctx.canvas()->getTotalMatrix();
  RNS_LOG_DEBUG("\n"<<
                " getScaleX      : "<<matrix.getScaleX() << "\n" <<
                " getScaleY      : "<<matrix.getScaleY()<<  "\n" <<
                " getTranslateX  : "<<matrix.getTranslateX()<<  "\n" <<
                " getTranslateY  : "<<matrix.getTranslateY()<<  "\n" <<
                " getSkewX       : "<<matrix.getSkewX()<<  "\n" <<
                " getSkewY       : "<<matrix.getSkewY());
}

} // namespace react
} // namespace facebook
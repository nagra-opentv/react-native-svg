/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "include/core/SkCanvas.h"

#include "RSkSVGShape.h"

using namespace std;

namespace facebook {
namespace react {

RSkSVGShape::RSkSVGShape(const ShadowView &shadowView,
                                           RnsShell::LayerType layerType,
                                           SkSVGTag t)
    : INHERITED(shadowView,layerType,t){}

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
  RNS_LOG_DEBUG(" getScaleX "<<matrix.getScaleX());
  RNS_LOG_DEBUG(" getScaleY "<<matrix.getScaleY());
  RNS_LOG_DEBUG(" getTranslateX "<<matrix.getTranslateX());
  RNS_LOG_DEBUG(" getTranslateY "<<matrix.getTranslateY());
  RNS_LOG_DEBUG(" getSkewX "<<matrix.getSkewX());
  RNS_LOG_DEBUG(" getSkewY "<<matrix.getSkewY());
}

} // namespace react
} // namespace facebook
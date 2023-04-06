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

  auto renderShape =[&](SkPaint* paint,const RNSVGColorFillStruct & colorStruct){
    setupPaintForRender(paint,colorStruct,ctx);
    this->onDraw(ctx.canvas(), ctx.lengthContext(), *paint, fillType);
  };

  if (SkPaint* fillPaint = const_cast<SkPaint*>(ctx.fillPaint())) {
    renderShape(fillPaint,fillColor);
  }
  if (SkPaint* strokePaint = const_cast<SkPaint*>(ctx.strokePaint())) {
    renderShape(strokePaint,strokeColor);
  }

#ifdef ENABLE_RSKSVG_PROPS_DEBUG
  SkMatrix matrix=ctx.canvas()->getTotalMatrix();
  RNS_LOG_INFO(" Transform Matrix Applied on Canvas \n" <<
               "----------------------------"<< "\n" <<
               " getScaleX      : "<<matrix.getScaleX() << "\n" <<
               " getScaleY      : "<<matrix.getScaleY()<<  "\n" <<
               " getTranslateX  : "<<matrix.getTranslateX()<<  "\n" <<
               " getTranslateY  : "<<matrix.getTranslateY()<<  "\n" <<
               " getSkewX       : "<<matrix.getSkewX()<<  "\n" <<
               " getSkewY       : "<<matrix.getSkewY()<<  "\n" <<
               "----------------------------");
#endif/*ENABLE_RSKSVG_PROPS_DEBUG*/

}

} // namespace react
} // namespace facebook
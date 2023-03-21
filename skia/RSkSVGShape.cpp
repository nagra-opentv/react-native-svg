/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "RSkComponentRNSVGLinearGradient.h"
#include "RSkComponentRNSVGSvgView.h"
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
    if(!fillBrushRef.empty()) {
      applyShader(fillPaint,fillBrushRef,ctx);
    }
    this->onDraw(ctx.canvas(), ctx.lengthContext(), *fillPaint, fillType);
  }
  if (SkPaint* strokePaint = const_cast<SkPaint*>(ctx.strokePaint())) {
    strokePaint->setAntiAlias(true);
    if(!strokeBrushRef.empty()) {
      applyShader(strokePaint,strokeBrushRef,ctx);
    }
    this->onDraw(ctx.canvas(), ctx.lengthContext(), *strokePaint, fillType);
  }

#ifdef ENABLE_NATIVE_PROPS_DEBUG
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
#endif/*ENABLE_NATIVE_PROPS_DEBUG*/

}

void RSkSVGShape::applyShader(SkPaint* paint,std::string brushRef,const SkSVGRenderContext& ctx) const{
  if(rootNode_) {
    auto rootSvgContainerNode=static_cast<RSkComponentRNSVGSvgView *>(rootNode_);
    if(rootSvgContainerNode) {
       RSkSVGNode**  nodeRef = rootSvgContainerNode->rskNodeIDMapper.find(SkString(brushRef));
      if (nodeRef && (*nodeRef) && ((*nodeRef)->tag() == SkSVGTag::kLinearGradient)) {
        auto linearGradientNode=dynamic_cast<RSkComponentRNSVGLinearGradient *>(*nodeRef);
        if(linearGradientNode) {
          paint->setShader(linearGradientNode->getShader(ctx));
        }
      } else {
        RNS_LOG_ERROR(" Provided Invalid Svg Element as a brushRef : "<<brushRef);
      }
    }
  }
}

} // namespace react
} // namespace facebook
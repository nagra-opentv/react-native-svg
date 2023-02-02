/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "include/core/SkCanvas.h"

#include "RSkSVGShapeComponent.h"

using namespace std;

namespace facebook {
namespace react {

RSkSVGShapeComponent::RSkSVGShapeComponent(const ShadowView &shadowView,
                                           RnsShell::LayerType layerType,
                                           SkSVGTag t)
    : RSkComponent(shadowView,layerType),
      RSkSVGNode(t) {}

void RSkSVGShapeComponent::onRender(const SkSVGRenderContext& ctx) const {

  const auto fillType = ctx.presentationContext().fInherited.fFillRule->asFillType();

  if (SkPaint* fillPaint = const_cast<SkPaint*>(ctx.fillPaint())) {
    SkColor color=fillPaint->getColor();
    RNS_LOG_DEBUG("FillColor : "<<color);
    RNS_LOG_DEBUG("A : "<<SkColorGetA(color));
    RNS_LOG_DEBUG("R : "<<SkColorGetR(color));
    RNS_LOG_DEBUG("G : "<<SkColorGetG(color));
    RNS_LOG_DEBUG("B : "<<SkColorGetB(color));
    fillPaint->setAntiAlias(true);
    this->onDraw(ctx.canvas(), ctx.lengthContext(), *fillPaint, fillType);
  }
  if (SkPaint* strokePaint = const_cast<SkPaint*>(ctx.strokePaint())) {
    SkColor color=strokePaint->getColor();
    RNS_LOG_DEBUG("StrokeColor : "<<color);
    RNS_LOG_DEBUG("A : "<<SkColorGetA(color));
    RNS_LOG_DEBUG("R : "<<SkColorGetR(color));
    RNS_LOG_DEBUG("G : "<<SkColorGetG(color));
    RNS_LOG_DEBUG("B : "<<SkColorGetB(color));
    strokePaint->setAntiAlias(true);
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


void RSkSVGShapeComponent::mountChildComponent(std::shared_ptr<RSkComponent> newChildComponent,const int index) {
  RNS_LOG_INFO("SVG Element of type Shapes can't have child Node :: "<<newChildComponent->getComponentData().componentName);
}

void RSkSVGShapeComponent::unmountChildComponent(std::shared_ptr<RSkComponent> oldChildComponent,const int index) {
  RNS_LOG_INFO(" SVG Element Of type Shapes can't have child :: "<<oldChildComponent->getComponentData().componentName);
}

void RSkSVGShapeComponent::OnPaint(SkCanvas *canvas) {
  RNS_LOG_INFO(" Paint for Shapes Elements handled via RNSSVG element ");
}

} // namespace react
} // namespace facebook
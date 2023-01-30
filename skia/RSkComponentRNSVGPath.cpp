/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "RSkComponentRNSVGPath.h"

namespace facebook {
namespace react {

RSkComponentRNSVGPath::RSkComponentRNSVGPath(const ShadowView &shadowView)
    : RSkComponent(shadowView,LAYER_TYPE_DEFAULT),
      INHERITED(SkSVGTag::kPath)  {}

void RSkComponentRNSVGPath::mountChildComponent(std::shared_ptr<RSkComponent> newChildComponent,const int index) {
  RNS_LOG_INFO("cannot append child nodes to an SVG Element Path.\n");
}

void RSkComponentRNSVGPath::unmountChildComponent(std::shared_ptr<RSkComponent> oldChildComponent,const int index) {
  RNS_LOG_INFO(" SVG Element Path can't have child ");
}

RnsShell::LayerInvalidateMask RSkComponentRNSVGPath::updateComponentProps(SharedProps newViewProps,bool forceUpdate) {

  RnsShell::LayerInvalidateMask invalidateMask = RnsShell::LayerInvalidateNone;

  auto const &newRNSVGPathProps = *std::static_pointer_cast<RNSVGPathProps const>(newViewProps);

  setPathDataAttribute(SkSVGAttribute::kD,newRNSVGPathProps.d.c_str());// Native Prop
  setCommonRenderableProps(newRNSVGPathProps);
  setCommonNodeProps(newRNSVGPathProps);

  return invalidateMask;
}

void RSkComponentRNSVGPath::onSetAttribute(SkSVGAttribute attr, const SkSVGValue& v) {
  switch (attr) {
  case SkSVGAttribute::kD:
    if (const auto* path = v.as<SkSVGPathValue>()) {
      path_=*path;
    }
    break;
  default:
    this->INHERITED::onSetAttribute(attr, v);
  }
}

void RSkComponentRNSVGPath::onDraw(SkCanvas* canvas, const SkSVGLengthContext&, const SkPaint& paint,
                                   SkPathFillType fillType) const {
  path_.setFillType(fillType);
  canvas->drawPath(path_, paint);
}


} // namespace react
} // namespace facebook

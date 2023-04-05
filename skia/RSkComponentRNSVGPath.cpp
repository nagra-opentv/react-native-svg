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
    : INHERITED(shadowView,LAYER_TYPE_VIRTUAL,SkSVGTag::kPath)  {}

RnsShell::LayerInvalidateMask RSkComponentRNSVGPath::updateComponentProps(SharedProps newViewProps,bool forceUpdate) {

  auto const &newRNSVGPathProps = *std::static_pointer_cast<RNSVGPathProps const>(newViewProps);
  #ifdef ENABLE_RSKSVG_PROPS_DEBUG
  RNS_LOG_INFO("\n" <<
               "===Native Props for SVG Element Path==="<< "\n" <<
               "Path String : "<<newRNSVGPathProps.d.c_str() << "\n" <<
               "=======================================");
  #endif/*ENABLE_RSKSVG_PROPS_DEBUG*/
  setPathDataAttribute(SkSVGAttribute::kD,newRNSVGPathProps.d.c_str());// Native Prop

  setCommonRenderableProps(newRNSVGPathProps);
  setCommonNodeProps(newRNSVGPathProps);

  invalidateParentSvgContainer();

  return RnsShell::LayerInvalidateAll;
}

void RSkComponentRNSVGPath::onSetAttribute(SkSVGAttribute attr, const SkSVGValue& attrValue) {
  switch (attr) {
    case SkSVGAttribute::kD:
      if (const auto* path = attrValue.as<SkSVGPathValue>()) {
        path_=*path;
      }
      break;
    default:
      this->INHERITED::onSetAttribute(attr, attrValue);
  }
}

void RSkComponentRNSVGPath::onDraw(SkCanvas* canvas, const SkSVGLengthContext&, const SkPaint& paint,
                                   SkPathFillType fillType) const {
  path_.setFillType(fillType);
  canvas->drawPath(path_, paint);
}

} // namespace react
} // namespace facebook

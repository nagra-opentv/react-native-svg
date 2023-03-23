/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "RSkComponentRNSVGCircle.h"

namespace facebook {
namespace react {

RSkComponentRNSVGCircle::RSkComponentRNSVGCircle(const ShadowView &shadowView)
    : INHERITED(shadowView,LAYER_TYPE_VIRTUAL,SkSVGTag::kCircle) {}

RnsShell::LayerInvalidateMask  RSkComponentRNSVGCircle::updateComponentProps(SharedProps newViewProps,bool forceUpdate) {

  auto const &newRNSVGCircleProps = *std::static_pointer_cast<RNSVGCircleProps const>(newViewProps);

#ifdef ENABLE_NATIVE_PROPS_DEBUG
  RNS_LOG_INFO("\n" <<
               "===Native Props for SVG Element Circle==="<< "\n" <<
               " CX: "<<newRNSVGCircleProps.cx << "\n" <<
               " CY: "<<newRNSVGCircleProps.cy << "\n" <<
               " r : "<<newRNSVGCircleProps.r << "\n" <<
               "=========================================");
#endif /*ENABLE_NATIVE_PROPS_DEBUG*/
  setLengthAttribute(SkSVGAttribute::kCx,newRNSVGCircleProps.cx);
  setLengthAttribute(SkSVGAttribute::kCy,newRNSVGCircleProps.cy);
  setLengthAttribute(SkSVGAttribute::kR,newRNSVGCircleProps.r);

  setCommonRenderableProps(newRNSVGCircleProps);
  setCommonNodeProps(newRNSVGCircleProps);

  invalidateLayer();
  return RnsShell::LayerInvalidateAll;
}

void RSkComponentRNSVGCircle::onSetAttribute(SkSVGAttribute attr, const SkSVGValue& attrValue) {

  switch (attr) {
    case SkSVGAttribute::kCx:
      if (const auto* cx = attrValue.as<SkSVGLengthValue>()) {
        cx_ =*cx;
      }
      break;
    case SkSVGAttribute::kCy:
      if (const auto* cy = attrValue.as<SkSVGLengthValue>()) {
        cy_ =*cy;
      }
      break;
    case SkSVGAttribute::kR:
      if (const auto* r = attrValue.as<SkSVGLengthValue>()) {
        r_ =*r;
      }
      break;
    default:
      this->INHERITED::onSetAttribute(attr, attrValue);
  }
}

void RSkComponentRNSVGCircle::onDraw(SkCanvas* canvas, const SkSVGLengthContext& lctx,
                         const SkPaint& paint, SkPathFillType) const {

  SkScalar cx = lctx.resolve(cx_, SkSVGLengthContext::LengthType::kHorizontal);
  SkScalar cy = lctx.resolve(cy_, SkSVGLengthContext::LengthType::kVertical);
  SkScalar  r = lctx.resolve(r_ , SkSVGLengthContext::LengthType::kOther);

  if (r > 0) {
    canvas->drawCircle(cx, cy, r, paint);
  }
 
}

} // namespace react
} // namespace facebook

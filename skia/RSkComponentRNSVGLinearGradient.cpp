/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "RSkComponentRNSVGLinearGradient.h"

namespace facebook {
namespace react {

RSkComponentRNSVGLinearGradient::RSkComponentRNSVGLinearGradient(const ShadowView &shadowView)
    : INHERITED(shadowView,LAYER_TYPE_VIRTUAL,SkSVGTag::kLinearGradient){}

RnsShell::LayerInvalidateMask  RSkComponentRNSVGLinearGradient::updateComponentProps(SharedProps newViewProps,bool forceUpdate) {

  auto const &newRNSVGLinearGradientProps = *std::static_pointer_cast<RNSVGLinearGradientProps const>(newViewProps);

#ifdef ENABLE_RSKSVG_PROPS_DEBUG
  RNS_LOG_INFO("\n" <<
               "===Native Props for SVG Element Circle==="<< "\n" <<
               " X1: "<<newRNSVGLinearGradientProps.x1 << "\n" <<
               " Y1: "<<newRNSVGLinearGradientProps.y1 << "\n" <<
               " X2: "<<newRNSVGLinearGradientProps.x2 << "\n" <<
               " Y2: "<<newRNSVGLinearGradientProps.y2 << "\n" <<
               "==========================================");
  if(newRNSVGLinearGradientProps.gradientTransform.size() == 6) {
    RNS_LOG_INFO("gradientTransform : \n"<<
                  " Matrix 0 : "<<newRNSVGLinearGradientProps.gradientTransform[0] << "\n" <<
                  " Matrix 1 : "<<newRNSVGLinearGradientProps.gradientTransform[1] << "\n" <<
                  " Matrix 2 : "<<newRNSVGLinearGradientProps.gradientTransform[2] << "\n" <<
                  " Matrix 3 : "<<newRNSVGLinearGradientProps.gradientTransform[3] << "\n" <<
                  " Matrix 4 : "<<newRNSVGLinearGradientProps.gradientTransform[4] << "\n" <<
                  " Matrix 5 : "<<newRNSVGLinearGradientProps.gradientTransform[5]);
  }
#endif/*ENABLE_RSKSVG_PROPS_DEBUG*/
  setLengthAttribute(SkSVGAttribute::kX1,newRNSVGLinearGradientProps.x1);
  setLengthAttribute(SkSVGAttribute::kX2,newRNSVGLinearGradientProps.x2);
  setLengthAttribute(SkSVGAttribute::kY1,newRNSVGLinearGradientProps.y1);
  setLengthAttribute(SkSVGAttribute::kY2,newRNSVGLinearGradientProps.y2);

  if(newRNSVGLinearGradientProps.gradientTransform.size() == 6) {
    // Converting received Matrix from React Native framework which is in column major Order to row Major Order for SKia
    gradientTransforMatrix_[SkMatrix::kMScaleX] = newRNSVGLinearGradientProps.gradientTransform[0];  //horizontal scale factor
    gradientTransforMatrix_[SkMatrix::kMSkewY]  = newRNSVGLinearGradientProps.gradientTransform[1];  // vertical skew factor
    gradientTransforMatrix_[SkMatrix::kMSkewX]  = newRNSVGLinearGradientProps.gradientTransform[2];  //horizontal skew factor
    gradientTransforMatrix_[SkMatrix::kMScaleY] = newRNSVGLinearGradientProps.gradientTransform[3];  //vertical scale factor
    gradientTransforMatrix_[SkMatrix::kMTransX] = newRNSVGLinearGradientProps.gradientTransform[4];  //horizontal translation
    gradientTransforMatrix_[SkMatrix::kMTransY] = newRNSVGLinearGradientProps.gradientTransform[5];  // vertical translation
  }

  for (int i = 0; i < newRNSVGLinearGradientProps.gradient.size();) {

  #ifdef ENABLE_RSKSVG_PROPS_DEBUG
    RNS_LOG_INFO("gradient :: " <<i << " Item :: "<< newRNSVGLinearGradientProps.gradient[i]);
    RNS_LOG_INFO("gradient :: " <<i+1 << " Item :: "<< (SharedColor)newRNSVGLinearGradientProps.gradient[i+1]);
  #endif/*ENABLE_RSKSVG_PROPS_DEBUG*/

    //The stop elements are ordered by offset followed by the color.
    //StopColor received is a combined value with stop opacity. 
    stopOffset_.push_back(newRNSVGLinearGradientProps.gradient[i]);
    stopColor_.push_back(RSkColorFromSharedColor((SharedColor)newRNSVGLinearGradientProps.gradient[i+1], SK_ColorTRANSPARENT));
    i=i+2;
  }

  setCommonNodeProps(newRNSVGLinearGradientProps);

#ifdef ENABLE_RSKSVG_PROPS_DEBUG
  for (auto item: stopOffset_) {
    RNS_LOG_INFO("stopOffset :: " <<item);
  }
  for (auto item: stopColor_) {
    RNS_LOG_INFO("stopColor_ ::\n"<<
                 "R :: " << SkColorGetR(item)<<"\n"
                 "G :: " << SkColorGetG(item)<<"\n"
                 "B :: " << SkColorGetB(item)<<"\n"
                 "A :: " <<SkColorGetA(item) <<"\n"
    );
  }
  #endif /*ENABLE_RSKSVG_PROPS_DEBUG*/

  invalidateLayer();

  return RnsShell::LayerInvalidateAll;
}

void RSkComponentRNSVGLinearGradient::onSetAttribute(SkSVGAttribute attr, const SkSVGValue& attrValue) {

  switch (attr) {
    case SkSVGAttribute::kX1:
      if (const auto* x1 = attrValue.as<SkSVGLengthValue>()) {
        x1_ =*x1;
      }
      break;
    case SkSVGAttribute::kY1:
      if (const auto* y1 = attrValue.as<SkSVGLengthValue>()) {
        y1_ =*y1;
      }
      break;
    case SkSVGAttribute::kX2:
      if (const auto* x2 = attrValue.as<SkSVGLengthValue>()) {
        x2_ =*x2;
      }
      break;
    case SkSVGAttribute::kY2:
      if (const auto* y2 = attrValue.as<SkSVGLengthValue>()) {
        y2_ =*y2;
      }
      break;
    default:
      this->INHERITED::onSetAttribute(attr, attrValue);
  }
}

sk_sp<SkShader> RSkComponentRNSVGLinearGradient::getShader(const SkSVGRenderContext& ctx)  {

    if(stopColor_.empty() || stopOffset_.empty() || (stopOffset_.size() != stopColor_.size())) {
      return nullptr;
    }
    const auto& lctx = ctx.lengthContext();
    const auto x1 = lctx.resolve(x1_, SkSVGLengthContext::LengthType::kHorizontal);
    const auto y1 = lctx.resolve(y1_, SkSVGLengthContext::LengthType::kVertical);
    const auto x2 = lctx.resolve(x2_, SkSVGLengthContext::LengthType::kHorizontal);
    const auto y2 = lctx.resolve(y2_, SkSVGLengthContext::LengthType::kVertical);

    const SkPoint pts[2] = { {x1, y1}, {x2, y2}};

    return SkGradientShader::MakeLinear(pts, &stopColor_[0], &stopOffset_[0], stopColor_.size(), SkTileMode::kClamp, 0, &gradientTransforMatrix_);
}

void RSkComponentRNSVGLinearGradient::onRender(const SkSVGRenderContext& ctx) const {
// The Linear Gradient is a color type for SVG cannot be displayed as an independent element. So no Action required here.
}

} // namespace react
} // namespace facebook

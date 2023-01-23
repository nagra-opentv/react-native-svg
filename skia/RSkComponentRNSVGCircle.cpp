/*
 * Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <string>

#include "include/core/SkPaint.h"


#include "cxxreact/ModuleRegistry.h"

#include "react/renderer/components/rnsvg/RNSVGProps.h"

#include "RSkComponentRNSVGCircle.h"
#include "experimental/svg/model/SkSVGAttribute.h"

#include "experimental/svg/model/SkSVGRenderContext.h"
#include "experimental/svg/model/SkSVGValue.h"
#include "include/core/SkCanvas.h"

#include "RSkSVGPropsParserUtil.h"

namespace facebook {
namespace react {

RSkComponentRNSVGCircle::RSkComponentRNSVGCircle(const ShadowView &shadowView)
    : RSkComponent(shadowView,LAYER_TYPE_DEFAULT),
      INHERITED(SkSVGTag::kCircle) {
  selfNode=sk_sp<RSkSVGNode>(this);
}

void RSkComponentRNSVGCircle::mountChildComponent(
    std::shared_ptr<RSkComponent> newChildComponent,
    const int index) {
  RNS_LOG_INFO("cannot append child nodes to an SVG shape.\n");
}

RnsShell::LayerInvalidateMask  RSkComponentRNSVGCircle::updateComponentProps(const ShadowView &newShadowView,bool forceUpdate) {

  auto component = getComponentData();

  auto const &newRNSVGCircleProps = *std::static_pointer_cast<RNSVGCircleProps const>(newShadowView.props);
 
  RNS_LOG_WARN( " Width :: "<<component.layoutMetrics.frame.size.width<<" Height :: "<<component.layoutMetrics.frame.size.height<< " X:: "<<component.layoutMetrics.frame.origin.x<< " Y:: "<<component.layoutMetrics.frame.origin.y);
  RNS_LOG_INFO(" CX: "<<newRNSVGCircleProps.cx);
  RNS_LOG_INFO(" CY: "<<newRNSVGCircleProps.cy);
  RNS_LOG_INFO(" r: "<<newRNSVGCircleProps.r);


     SetLengthAttribute(selfNode,SkSVGAttribute::kCx,newRNSVGCircleProps.cx.c_str());

     SetLengthAttribute(selfNode,SkSVGAttribute::kCy,newRNSVGCircleProps.cy.c_str());

     SetLengthAttribute(selfNode,SkSVGAttribute::kR,newRNSVGCircleProps.r.c_str());

 updateCommonNodeProps(newRNSVGCircleProps,selfNode);


return RnsShell::LayerInvalidateNone;
}


void RSkComponentRNSVGCircle::onSetAttribute(SkSVGAttribute attr, const SkSVGValue& v) {

  switch (attr) {
    case SkSVGAttribute::kCx:
        if (const auto* cx = v.as<SkSVGLengthValue>()) {
            this->cx =*cx;
        }
        break;
    case SkSVGAttribute::kCy:
        if (const auto* cy = v.as<SkSVGLengthValue>()) {
            this->cy =*cy;
        }
        break;
    case SkSVGAttribute::kR:
        if (const auto* r = v.as<SkSVGLengthValue>()) {
            this->r =*r;
        }
        break;
    default:
        this->INHERITED::onSetAttribute(attr, v);
    }
}

void RSkComponentRNSVGCircle::onDraw(SkCanvas* canvas, const SkSVGLengthContext& lctx,
                         const SkPaint& paint, SkPathFillType) const {

  SkScalar cx = lctx.resolve(this->cx, SkSVGLengthContext::LengthType::kHorizontal);
  SkScalar cy = lctx.resolve(this->cy, SkSVGLengthContext::LengthType::kVertical);
  SkScalar  r = lctx.resolve(this->r , SkSVGLengthContext::LengthType::kOther);

  if (r > 0) {
    canvas->drawCircle(cx, cy, r, paint);
  }
 
}

} // namespace react
} // namespace facebook

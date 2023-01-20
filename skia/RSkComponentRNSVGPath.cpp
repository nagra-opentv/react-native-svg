/*
 * Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */


#include "include/core/SkCanvas.h"
#include "include/core/SkPaint.h"

#include "react/renderer/components/rnsvg/RNSVGProps.h"

#include "RSkComponentRNSVGPath.h"
#include "RSkSVGPropsParserUtil.h"

namespace facebook {
namespace react {

RSkComponentRNSVGPath::RSkComponentRNSVGPath(const ShadowView &shadowView)
    : RSkComponent(shadowView,LAYER_TYPE_DEFAULT),
      INHERITED(SkSVGTag::kPath)  {
  selfNode=sk_sp<SkSVGNode>(this);
}

void RSkComponentRNSVGPath::mountChildComponent(
    std::shared_ptr<RSkComponent> newChildComponent,
    const int index) {
  RNS_LOG_INFO("cannot append child nodes to an SVG shape.\n");
}

RnsShell::LayerInvalidateMask RSkComponentRNSVGPath::updateComponentProps(
    const ShadowView &newShadowView,
    bool forceUpdate) {
  RnsShell::LayerInvalidateMask invalidateMask = RnsShell::LayerInvalidateNone;

  auto const &newRNSVGPathProps = *std::static_pointer_cast<RNSVGPathProps const>(newShadowView.props);

  setPathDataAttribute(selfNode,SkSVGAttribute::kD,newRNSVGPathProps.d.c_str());

  updateCommonNodeProps(newRNSVGPathProps,*this,selfNode);

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

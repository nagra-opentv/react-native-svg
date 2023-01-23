/*
 * Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */


#include "include/core/SkPaint.h"

#include "cxxreact/ModuleRegistry.h"

#include "react/renderer/components/rnsvg/RNSVGProps.h"
#include "rns_shell/compositor/layers/PictureLayer.h"

#include "include/utils/SkParsePath.h"

#include "RSkComponentRNSVGPath.h"

#include "experimental/svg/model/SkSVGRenderContext.h"
#include "experimental/svg/model/SkSVGValue.h"
#include "include/core/SkCanvas.h"

#include "RSkSVGPropsParserUtil.h"

namespace facebook {
namespace react {

RSkComponentRNSVGPath::RSkComponentRNSVGPath(const ShadowView &shadowView)
    : RSkComponent(shadowView,LAYER_TYPE_DEFAULT),
      INHERITED(SkSVGTag::kPath)
       {
       selfNode=sk_sp<RSkSVGNode>(this);
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

  auto component = getComponentData();

  auto const &newRNSVGPathProps =
      *std::static_pointer_cast<RNSVGPathProps const>(newShadowView.props);

     selfNode->SetPathDataAttribute(selfNode,SkSVGAttribute::kD,newRNSVGPathProps.d.c_str());

 updateCommonNodeProps(newRNSVGPathProps,selfNode);

  return invalidateMask;
}
void RSkComponentRNSVGPath::onSetAttribute(SkSVGAttribute attr, const SkSVGValue& v) {
    switch (attr) {
    case SkSVGAttribute::kD:
        if (const auto* path = v.as<SkSVGPathValue>()) {
            fPath=*path;
        }
        break;
    default:
        this->INHERITED::onSetAttribute(attr, v);
    }
}

void RSkComponentRNSVGPath::onDraw(SkCanvas* canvas, const SkSVGLengthContext&, const SkPaint& paint,
                       SkPathFillType fillType) const {
    fPath.setFillType(fillType);
    canvas->drawPath(fPath, paint);
}


} // namespace react
} // namespace facebook

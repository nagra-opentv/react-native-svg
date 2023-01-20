/*
 * Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <vector>
#include "include/core/SkPaint.h"


#include "cxxreact/ModuleRegistry.h"

#include "react/renderer/components/rnsvg/RNSVGProps.h"
#include "rns_shell/compositor/layers/PictureLayer.h"

#include "experimental/svg/model/SkSVGContainer.h"
#include "RSkComponentRNSVGG.h"
#include "RSkSVGPropsParserUtil.h"


namespace facebook {
namespace react {

RSkComponentRNSVGGroup::RSkComponentRNSVGGroup(const ShadowView &shadowView)
    : RSkComponent(shadowView),
      INHERITED(SkSVGTag::kG) {
  selfNode=sk_sp<SkSVGNode>(this);
}

RnsShell::LayerInvalidateMask  RSkComponentRNSVGGroup::updateComponentProps(const ShadowView &newShadowView,bool forceUpdate) {
  RnsShell::LayerInvalidateMask invalidateMask = RnsShell::LayerInvalidateNone;

  auto component = getComponentData();

  auto const &newRNSVGGroupPropsProps = *std::static_pointer_cast<RNSVGGroupProps const>(newShadowView.props);

  RNS_LOG_WARN( " Width :: "<<component.layoutMetrics.frame.size.width<<" Height :: "<<component.layoutMetrics.frame.size.height<< " X:: "<<component.layoutMetrics.frame.origin.x<< " Y:: "<<component.layoutMetrics.frame.origin.y);

  updateCommonNodeProps(newRNSVGGroupPropsProps,*this,selfNode);
  return invalidateMask;
}

void RSkComponentRNSVGGroup::mountChildComponent(std::shared_ptr<RSkComponent> newChildComponent,const int index) {
  RNS_LOG_INFO("mountChildComponent :: RSkComponentRNSVGGroup holding child :" << newChildComponent->getComponentData().componentName);
  appendSVGChildElements(newChildComponent);
}

} // namespace react
} // namespace facebook

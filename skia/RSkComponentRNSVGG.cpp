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


#include "RSkComponentRNSVGG.h"
#include "RSkSVGPropsParserUtil.h"

std::vector<std::shared_ptr<RSkComponent>> groupChildContainer;

namespace facebook {
namespace react {

RSkComponentRNSVGGroup::RSkComponentRNSVGGroup(const ShadowView &shadowView)
    : RSkComponent(shadowView,LAYER_TYPE_DEFAULT) ,
     INHERITED(SkSVGTag::kG){}

RnsShell::LayerInvalidateMask  RSkComponentRNSVGGroup::updateComponentProps(SharedProps newViewProps,bool forceUpdate) {
  RnsShell::LayerInvalidateMask invalidateMask = RnsShell::LayerInvalidateNone;

  auto component = getComponentData();

  auto const &newRNSVGGroupPropsProps = *std::static_pointer_cast<RNSVGGroupProps const>(newViewProps);

  RNS_LOG_WARN( " Width :: "<<component.layoutMetrics.frame.size.width<<" Height :: "<<component.layoutMetrics.frame.size.height<< " X:: "<<component.layoutMetrics.frame.origin.x<< " Y:: "<<component.layoutMetrics.frame.origin.y);
  updateCommonNodeProps(newRNSVGGroupPropsProps,this);

  return invalidateMask;
}

void RSkComponentRNSVGGroup::mountChildComponent(
    std::shared_ptr<RSkComponent> newChildComponent,
    const int index) {
  RNS_LOG_INFO("RSkComponentRNSVGGroup holding child :" << newChildComponent->getComponentData().componentName);

  addChildAtIndex(newChildComponent,index);
}

void RSkComponentRNSVGGroup::unmountChildComponent(
    std::shared_ptr<RSkComponent> oldChildComponent,
    const int index) {
  RNS_LOG_INFO("RSkComponentRNSVGGroup recieved unmount for child :" << oldChildComponent->getComponentData().componentName);
  removeChildAtIndex(oldChildComponent,index);
}

} // namespace react
} // namespace facebook

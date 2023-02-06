/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "RSkComponentRNSVGGroup.h"

namespace facebook {
namespace react {

RSkComponentRNSVGGroup::RSkComponentRNSVGGroup(const ShadowView &shadowView)
    : INHERITED(shadowView,LAYER_TYPE_VIRTUAL,SkSVGTag::kG) {}

RnsShell::LayerInvalidateMask  RSkComponentRNSVGGroup::updateComponentProps(SharedProps newViewProps,bool forceUpdate) {

  auto const &newRNSVGGroupPropsProps = *std::static_pointer_cast<RNSVGGroupProps const>(newViewProps);

  setCommonRenderableProps(newRNSVGGroupPropsProps);
  setCommonNodeProps(newRNSVGGroupPropsProps);
  setCommonGroupProps(newRNSVGGroupPropsProps);

  return RnsShell::LayerInvalidateAll;
}

} // namespace react
} // namespace facebook

/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "RSkComponentRNSVGText.h"

namespace facebook {
namespace react {

RSkComponentRNSVGText::RSkComponentRNSVGText(const ShadowView &shadowView)
    : INHERITED(shadowView,LAYER_TYPE_VIRTUAL,SkSVGTag::kText) {
 }

RnsShell::LayerInvalidateMask  RSkComponentRNSVGText::updateComponentProps(SharedProps newViewProps,bool forceUpdate) {

  updateCommonTextProps(newViewProps);
  return RnsShell::LayerInvalidateAll;
}

} // namespace react
} // namespace facebook

/*
 * Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "react/renderer/components/rnsvg/RNSVGComponentDescriptors.h"

#include "RSkComponentProviderRNSVGView.h"
#include "RSkComponentRNSVGView.h"

namespace facebook {
namespace react {

RSkComponentProviderRNSVGView::RSkComponentProviderRNSVGView() {}

ComponentDescriptorProvider RSkComponentProviderRNSVGView::GetDescriptorProvider() {
  return concreteComponentDescriptorProvider<RNSVGViewComponentDescriptor>();
}

std::shared_ptr<RSkComponent> RSkComponentProviderRNSVGView::CreateComponent(
    const ShadowView &shadowView) {
  return std::static_pointer_cast<RSkComponent>(
      std::make_shared<RSkComponentRNSVGView>(shadowView));
}

} // namespace react
} // namespace facebook

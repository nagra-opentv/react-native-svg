/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "react/renderer/components/rnsvg/RNSVGComponentDescriptors.h"

#include "RSkComponentProviderRNSVGGroup.h"
#include "RSkComponentRNSVGGroup.h"

namespace facebook {
namespace react {

RSkComponentProviderRNSVGGroup::RSkComponentProviderRNSVGGroup() {}

ComponentDescriptorProvider RSkComponentProviderRNSVGGroup::GetDescriptorProvider() {
  return concreteComponentDescriptorProvider<RNSVGGroupComponentDescriptor>();
}

std::shared_ptr<RSkComponent> RSkComponentProviderRNSVGGroup::CreateComponent(
    const ShadowView &shadowView) {
  return std::static_pointer_cast<RSkComponent>(
      std::make_shared<RSkComponentRNSVGGroup>(shadowView));
}

} // namespace react
} // namespace facebook

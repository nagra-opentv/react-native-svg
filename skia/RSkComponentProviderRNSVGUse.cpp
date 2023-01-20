/*
 * Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "RSkComponentProviderRNSVGUse.h"
#include "RSkComponentRNSVGUse.h"

#include "react/renderer/components/rnsvg/RNSVGComponentDescriptors.h"

namespace facebook {
namespace react {

RSkComponentProviderRNSVGUse::RSkComponentProviderRNSVGUse() {}

ComponentDescriptorProvider RSkComponentProviderRNSVGUse::GetDescriptorProvider() {
  return concreteComponentDescriptorProvider<RNSVGUseComponentDescriptor>();
}

std::shared_ptr<RSkComponent> RSkComponentProviderRNSVGUse::CreateComponent(
    const ShadowView &shadowView) {
  return std::static_pointer_cast<RSkComponent>(
      std::make_shared<RSkComponentRNSVGUse>(shadowView));
}


} // namespace react
} // namespace facebook

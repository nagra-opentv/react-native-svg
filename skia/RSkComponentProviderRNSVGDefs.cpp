/*
 * Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "react/renderer/components/rnsvg/RNSVGComponentDescriptors.h"

#include "RSkComponentProviderRNSVGDefs.h"
#include "RSkComponentRNSVGDefs.h"

namespace facebook {
namespace react {

RSkComponentProviderRNSVGDefs::RSkComponentProviderRNSVGDefs() {}

ComponentDescriptorProvider RSkComponentProviderRNSVGDefs::GetDescriptorProvider() {
  return concreteComponentDescriptorProvider<RNSVGDefsComponentDescriptor>();
}

std::shared_ptr<RSkComponent> RSkComponentProviderRNSVGDefs::CreateComponent(
    const ShadowView &shadowView) {
  return std::static_pointer_cast<RSkComponent>(
      std::make_shared<RSkComponentRNSVGDefs>(shadowView));
}

} // namespace react
} // namespace facebook

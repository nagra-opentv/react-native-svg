/*
 * Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "react/renderer/components/rnsvg/RNSVGComponentDescriptors.h"

#include "RSkComponentProviderRNSVGCircle.h"
#include "RSkComponentRNSVGCircle.h"

namespace facebook {
namespace react {

RSkComponentProviderRNSVGCircle::RSkComponentProviderRNSVGCircle() {}

ComponentDescriptorProvider RSkComponentProviderRNSVGCircle::GetDescriptorProvider() {
  return concreteComponentDescriptorProvider<RNSVGCircleComponentDescriptor>();
}

std::shared_ptr<RSkComponent> RSkComponentProviderRNSVGCircle::CreateComponent(
    const ShadowView &shadowView) {
  return std::static_pointer_cast<RSkComponent>(
      std::make_shared<RSkComponentRNSVGCircle>(shadowView));
}

} // namespace react
} // namespace facebook

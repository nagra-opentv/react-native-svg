/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "react/renderer/components/rnsvg/RNSVGComponentDescriptors.h"

#include "RSkComponentProviderRNSVGLine.h"
#include "RSkComponentRNSVGLine.h"

namespace facebook {
namespace react {

RSkComponentProviderRNSVGLine::RSkComponentProviderRNSVGLine() {}

ComponentDescriptorProvider RSkComponentProviderRNSVGLine::GetDescriptorProvider() {
  return concreteComponentDescriptorProvider<RNSVGLineComponentDescriptor>();
}

std::shared_ptr<RSkComponent> RSkComponentProviderRNSVGLine::CreateComponent(
    const ShadowView &shadowView) {
  return std::static_pointer_cast<RSkComponent>(
      std::make_shared<RSkComponentRNSVGLine>(shadowView));
}

} // namespace react
} // namespace facebook

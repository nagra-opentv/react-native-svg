/*
 * Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "RSkComponentProviderRNSVGPath.h"
#include "RSkComponentRNSVGPath.h"

#include "react/renderer/components/rnsvg/RNSVGComponentDescriptors.h"

namespace facebook {
namespace react {

RSkComponentProviderRNSVGPath::RSkComponentProviderRNSVGPath() {}

ComponentDescriptorProvider RSkComponentProviderRNSVGPath::GetDescriptorProvider() {
  return concreteComponentDescriptorProvider<RNSVGPathComponentDescriptor>();
}

std::shared_ptr<RSkComponent> RSkComponentProviderRNSVGPath::CreateComponent(
    const ShadowView &shadowView) {
  return std::static_pointer_cast<RSkComponent>(
      std::make_shared<RSkComponentRNSVGPath>(shadowView));
}

} // namespace react
} // namespace facebook

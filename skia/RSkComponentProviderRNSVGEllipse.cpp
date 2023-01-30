/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "react/renderer/components/rnsvg/RNSVGComponentDescriptors.h"

#include "RSkComponentProviderRNSVGEllipse.h"
#include "RSkComponentRNSVGEllipse.h"

namespace facebook {
namespace react {

RSkComponentProviderRNSVGEllipse::RSkComponentProviderRNSVGEllipse() {}

ComponentDescriptorProvider RSkComponentProviderRNSVGEllipse::GetDescriptorProvider() {
  return concreteComponentDescriptorProvider<RNSVGEllipseComponentDescriptor>();
}

std::shared_ptr<RSkComponent> RSkComponentProviderRNSVGEllipse::CreateComponent(
    const ShadowView &shadowView) {
  return std::static_pointer_cast<RSkComponent>(
      std::make_shared<RSkComponentRNSVGEllipse>(shadowView));
}

} // namespace react
} // namespace facebook

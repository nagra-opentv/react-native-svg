/*
 * Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "react/renderer/components/rnsvg/RNSVGComponentDescriptors.h"

#include "RSkComponentProviderRNSVGRect.h"
#include "RSkComponentRNSVGRect.h"

namespace facebook {
namespace react {

RSkComponentProviderRNSVGRect::RSkComponentProviderRNSVGRect() {}

ComponentDescriptorProvider RSkComponentProviderRNSVGRect::GetDescriptorProvider() {
  return concreteComponentDescriptorProvider<RNSVGRectComponentDescriptor>();
}

std::shared_ptr<RSkComponent> RSkComponentProviderRNSVGRect::CreateComponent(
    const ShadowView &shadowView) {
  return std::static_pointer_cast<RSkComponent>(
      std::make_shared<RSkComponentRNSVGRect>(shadowView));
}

} // namespace react
} // namespace facebook

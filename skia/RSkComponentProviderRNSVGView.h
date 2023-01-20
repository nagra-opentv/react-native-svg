/*
 * Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include "ReactSkia/components/RSkComponentProvider.h"
#include "ReactSkia/utils/RnsUtils.h"

namespace facebook {
namespace react {

class RSkComponentProviderRNSVGView : public RSkComponentProvider {
 public:
  RSkComponentProviderRNSVGView();

 public:
  ComponentDescriptorProvider GetDescriptorProvider() override;
  std::shared_ptr<RSkComponent> CreateComponent(
      const ShadowView &shadowView) override;
};

#ifdef __cplusplus
extern "C" {
#endif
RNS_EXPORT_COMPONENT_PROVIDER(RNSVGView)
#ifdef __cplusplus
}
#endif

} // namespace react
} // namespace facebook

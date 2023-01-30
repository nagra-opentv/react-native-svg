/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "ReactSkia/utils/RnsLog.h"

#include "RNSVGSvgViewModule.h"

using namespace folly;

namespace facebook {
namespace xplat {

std::string RNSVGSvgViewModule::getName() {
  return "RNSVGSvgViewManager";
}

auto RNSVGSvgViewModule::getConstants() -> std::map<std::string, folly::dynamic> {
  return {};
}

// Module Methods
auto RNSVGSvgViewModule::getMethods() -> std::vector<Method> {
  return {
    Method(
      "toDataURL",
      [this] (dynamic args) {
        RNS_LOG_NOT_IMPL;
        RNS_UNUSED(this);
        return;
      }),
  };
}

// Module Helpers

} // namespace xplat
} // namespace facebook

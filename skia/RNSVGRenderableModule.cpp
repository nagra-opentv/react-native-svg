/*
 * Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "ReactSkia/utils/RnsLog.h"

#include "RNSVGRenderableModule.h"

using namespace folly;

namespace facebook {
namespace xplat {

std::string RNSVGRenderableModule::getName() {
  return "RNSVGRenderableManager";
}

auto RNSVGRenderableModule::getConstants() -> std::map<std::string, folly::dynamic> {
  RNS_LOG_NOT_IMPL;
  return {};
}

// Module Methods
auto RNSVGRenderableModule::getMethods() -> std::vector<Method> {
  return {
    Method(
      "isPointInStroke",
      [this] () -> bool {
        RNS_LOG_NOT_IMPL;
        RNS_UNUSED(this);
        return true;
      }),
    Method(
      "isPointInFill",
      [this] () -> bool {
        RNS_LOG_NOT_IMPL;
        RNS_UNUSED(this);
        return true;
      }),
    Method(
      "getPointAtLength",
      [this] () -> bool {
        RNS_LOG_NOT_IMPL;
        RNS_UNUSED(this);
        return true;
      }),
    Method(
      "getTotalLength",
      [this] () -> bool {
        RNS_LOG_NOT_IMPL;
        RNS_UNUSED(this);
        return true;
      }),
    Method(
      "getBBox",
      [this] () -> bool {
        RNS_LOG_NOT_IMPL;
        RNS_UNUSED(this);
        return true;
      }),
    Method(
      "getCTM",
      [this] () -> bool {
        RNS_LOG_NOT_IMPL;
        RNS_UNUSED(this);
        return true;
      }),
    Method(
      "getScreenCTM",
      [this] () -> bool {
        RNS_LOG_NOT_IMPL;
        RNS_UNUSED(this);
        return true;
      }),
  };
}

// Module Helpers

} // namespace xplat
} // namespace facebook

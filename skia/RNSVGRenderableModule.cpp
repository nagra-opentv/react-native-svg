/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
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
  return "RNSVGRenderableModule";
}

auto RNSVGRenderableModule::getConstants() -> std::map<std::string, folly::dynamic> {
  return {};
}

// Module Methods
auto RNSVGRenderableModule::getMethods() -> std::vector<Method> {
  return {
    Method(
      "isPointInStroke",
      [] () -> bool {
        RNS_LOG_NOT_IMPL;
        return true;
      }),
    Method(
      "isPointInFill",
      [] () -> bool {
        RNS_LOG_NOT_IMPL;
        return true;
      }),
    Method(
      "getPointAtLength",
      [] () -> bool {
        RNS_LOG_NOT_IMPL;
        return true;
      }),
    Method(
      "getTotalLength",
      [] () -> bool {
        RNS_LOG_NOT_IMPL;
        return true;
      }),
    Method(
      "getBBox",
      [] () -> bool {
        RNS_LOG_NOT_IMPL;
        return true;
      }),
    Method(
      "getCTM",
      [] () -> bool {
        RNS_LOG_NOT_IMPL;
        return true;
      }),
    Method(
      "getScreenCTM",
      [] () -> bool {
        RNS_LOG_NOT_IMPL;
        return true;
      }),
  };
}


#ifdef __cplusplus
extern "C" {
#endif
RNS_EXPORT_MODULE_WITHOUT_SUFFIX(RNSVGRenderableModule)
#ifdef __cplusplus
}
#endif

} // namespace xplat
} // namespace facebook

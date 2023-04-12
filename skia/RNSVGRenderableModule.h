/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <cxxreact/CxxModule.h>

#include "ReactSkia/utils/RnsUtils.h"

namespace facebook {
namespace xplat {

class RNSVGRenderableModule : public module::CxxModule {
 public:
  RNSVGRenderableModule() {};

  // Module Implementation
  std::map<std::string, folly::dynamic> getConstants() override;
  std::vector<Method> getMethods() override;
  std::string getName() override;

 private:
};

} // namespace xplat
} // namespace facebook

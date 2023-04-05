/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include "RSkSVGTextContainer.h"

namespace facebook {
namespace react {

class RSkComponentRNSVGText final : public RSkSVGTextContainer{
 public:

  RSkComponentRNSVGText(const ShadowView &shadowView);
  ~RSkComponentRNSVGText() {}

 // Override for Base class : RSkComponent
  RnsShell::LayerInvalidateMask updateComponentProps(SharedProps newViewProps,bool forceUpdate) override;
 protected:

 private:
  typedef RSkSVGTextContainer INHERITED;
};

} // namespace react
} // namespace facebook

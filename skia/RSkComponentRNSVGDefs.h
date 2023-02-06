/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */
#pragma once

#include "RSkSVGHiddenContainer.h"

namespace facebook {
namespace react {

class RSkComponentRNSVGDefs: public RSkSVGHiddenContainer {
 public:

  RSkComponentRNSVGDefs(const ShadowView &shadowView) :
          RSkSVGHiddenContainer(shadowView,LAYER_TYPE_VIRTUAL,SkSVGTag::kDefs) {}

  ~RSkComponentRNSVGDefs() override {};
  RnsShell::LayerInvalidateMask updateComponentProps(SharedProps newViewProps,bool forceUpdate) override {return RnsShell::LayerInvalidateNone;}

 protected:

 private:

};

} // namespace react
} // namespace facebook
/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */
#pragma once

#include "RSkSVGHiddenContainerComponent.h"

namespace facebook {
namespace react {

class RSkComponentRNSVGDefs: public RSkSVGHiddenContainerComponent {
  public:

    RSkComponentRNSVGDefs(const ShadowView &shadowView) :
                    RSkSVGHiddenContainerComponent(shadowView,LAYER_TYPE_VIRTUAL,SkSVGTag::kDefs) {}

    ~RSkComponentRNSVGDefs() = default;
  
    RnsShell::LayerInvalidateMask updateComponentProps(SharedProps newViewProps,bool forceUpdate) override {return RnsShell::LayerInvalidateNone;}

  protected:

  private:

};

} // namespace react
} // namespace facebook
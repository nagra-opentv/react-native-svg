/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once


#include "RSkSVGContainerComponent.h"

namespace facebook {
namespace react {

using namespace std;

class RSkComponentRNSVGGroup final : public RSkSVGContainerComponent{
 public:

  RSkComponentRNSVGGroup(const ShadowView &shadowView);
  ~RSkComponentRNSVGGroup() = default;

 // Override for Base class : RSkComponent
  RnsShell::LayerInvalidateMask updateComponentProps(SharedProps newViewProps,bool forceUpdate) override;

  void alterSkiaDefaultPaint();

 protected:

 private:

  typedef RSkSVGContainerComponent INHERITED;
};

} // namespace react
} // namespace facebook

/*
 * Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include "ReactSkia/components/RSkComponent.h"

#include "RSkSVGContainer.h"

namespace facebook {
namespace react {

using namespace std;

class RSkComponentRNSVGGroup final : public RSkComponent,public RSkSVGContainer{
 public:
  RSkComponentRNSVGGroup(const ShadowView &shadowView);
  ~RSkComponentRNSVGGroup() = default;

  RnsShell::LayerInvalidateMask updateComponentProps(const ShadowView &newShadowView,bool forceUpdate) override;
  void mountChildComponent(std::shared_ptr<RSkComponent> newChildComponent,const int index)override;
  sk_sp<RSkSVGNode> getComponentNode(){ return selfNode;}

 protected:
  void OnPaint(SkCanvas *canvas) override{ };

 private:
  sk_sp<RSkSVGNode> selfNode;
  typedef RSkSVGContainer INHERITED;
};

} // namespace react
} // namespace facebook

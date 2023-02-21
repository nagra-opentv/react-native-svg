/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "ReactSkia/components/RSkComponent.h"
#include "RSkSVGComponentNode.h"

namespace facebook {
namespace react {

class RSkComponentRNSVGUse: public RSkSVGComponentNode {
 public:

  RSkComponentRNSVGUse(const ShadowView &shadowView);
  ~RSkComponentRNSVGUse() override {};

  RnsShell::LayerInvalidateMask updateComponentProps(SharedProps newViewProps,bool forceUpdate) override;

 protected:

  void onSetAttribute(SkSVGAttribute, const SkSVGValue&) override;
  bool onPrepareToRender(SkSVGRenderContext*) const override;
  void onRender(const SkSVGRenderContext&) const override;

 private:

  SkSVGStringType    href_;
  SkSVGLength        x_ = SkSVGLength(0);
  SkSVGLength        y_ = SkSVGLength(0);

  typedef RSkSVGComponentNode INHERITED;
};

} // namespace react
} // namespace facebook
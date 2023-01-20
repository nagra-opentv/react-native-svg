/*
 * Copyright (C) 1994-present OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include "ReactSkia/components/RSkComponent.h"
#include "ReactSkia/utils/RnsUtils.h"
#include "RSkSVGNode.h"
#include "experimental/svg/model/SkSVGNode.h"
#include "experimental/svg/model/SkSVGIDMapper.h"
#include "experimental/svg/model/SkSVGContainer.h"

#include "experimental/svg/model/SkSVGNode.h"
#include "RSkSVGNode.h"
#include "RSkSVGContainer.h"

namespace facebook {
namespace react {

using namespace std;

class RSkComponentRNSVGView final : public RSkComponent,public RSkSVGContainer {
 public:
  RSkComponentRNSVGView(const ShadowView &shadowView);
  ~RSkComponentRNSVGView() = default;

  RnsShell::LayerInvalidateMask updateComponentProps(const ShadowView &newShadowView,bool forceUpdate) override;
  void mountChildComponent(std::shared_ptr<RSkComponent> newChildComponent,const int index)override;

  sk_sp<SkSVGNode> getComponentNode (){ return selfNode;}
 protected:
    void OnPaint(SkCanvas *canvas) override;

    bool onPrepareToRender(SkSVGRenderContext*) const override;
    void onSetAttribute(SkSVGAttribute, const SkSVGValue&) override;

    const SkSize& containerSize() const;
    void setContainerSize(const SkSize&);

 private:
    sk_sp<SkSVGNode> selfNode;
    SkSize           fContainerSize;

    SkSVGLength x_      = SkSVGLength(0);
    SkSVGLength y_      = SkSVGLength(0);
    SkSVGLength width_  = SkSVGLength(100, SkSVGLength::Unit::kPercentage);
    SkSVGLength height_ = SkSVGLength(100, SkSVGLength::Unit::kPercentage);
    SkRect viewBox_;

    typedef RSkSVGContainer INHERITED;
};

} // namespace react
} // namespace facebook

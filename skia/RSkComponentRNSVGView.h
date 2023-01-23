/*
 * Copyright (C) 1994-present OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include "ReactSkia/components/RSkComponent.h"

#include "RSkSVGContainer.h"
#include "RSkSVGNode.h"

namespace facebook {
namespace react {

using namespace std;

class RSkComponentRNSVGView final : public RSkComponent,public RSkSVGContainer  {
 public:
  RSkComponentRNSVGView(const ShadowView &shadowView);
  ~RSkComponentRNSVGView() = default;
  
  RnsShell::LayerInvalidateMask updateComponentProps(const ShadowView &newShadowView,bool forceUpdate) override;
  void mountChildComponent(std::shared_ptr<RSkComponent> newChildComponent, const int index)override;
  sk_sp<RSkSVGNode> getComponentNode(){ return selfNode;}
  SkSize getContainerSize(const SkSVGLengthContext&) const;
  
 protected:
    void OnPaint(SkCanvas *canvas) override;
    const SkSize containerSize() const {return svgContainerSize;}
    bool onPrepareToRender(SkSVGRenderContext*) const override;
    void onSetAttribute(SkSVGAttribute, const SkSVGValue&) override;

 private:

    sk_sp<RSkSVGNode> selfNode;

    SkSize           svgContainerSize;

    SkSVGLength fX      = SkSVGLength(0);
    SkSVGLength fY      = SkSVGLength(0);
    SkSVGLength fWidth  = SkSVGLength(100, SkSVGLength::Unit::kPercentage);
    SkSVGLength fHeight = SkSVGLength(100, SkSVGLength::Unit::kPercentage);
    SkTLazy<SkSVGViewBoxType> fViewBox;

    typedef RSkSVGContainer INHERITED;
};

} // namespace react
} // namespace facebook

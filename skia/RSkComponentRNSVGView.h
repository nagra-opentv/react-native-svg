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
  
  RnsShell::LayerInvalidateMask updateComponentProps(SharedProps newViewProps,bool forceUpdate) override;
  void mountChildComponent(std::shared_ptr<RSkComponent> newChildComponent, const int index)override;
  void unmountChildComponent(std::shared_ptr<RSkComponent> oldChildComponent,const int index)override;

//  sk_sp<RSkSVGNode> getComponentNode(){ return this;}
  SkSize getContainerSize(const SkSVGLengthContext&) const;
  
 protected:
    void OnPaint(SkCanvas *canvas) override;
    const SkSize containerSize() const {return svgContainerSize;}
    bool onPrepareToRender(SkSVGRenderContext*) const override;
    void onSetAttribute(SkSVGAttribute, const SkSVGValue&) override;

 private:
 
    SkSize           svgContainerSize;

    SkSVGLength x_      = SkSVGLength(0);
    SkSVGLength y_      = SkSVGLength(0);
    SkSVGLength width_  = SkSVGLength(100, SkSVGLength::Unit::kPercentage);
    SkSVGLength height_ = SkSVGLength(100, SkSVGLength::Unit::kPercentage);
    SkRect viewBox_;

    typedef RSkSVGContainer INHERITED;
};

} // namespace react
} // namespace facebook

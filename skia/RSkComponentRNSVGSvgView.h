/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once


#include "RSkSVGContainerComponent.h"
#include "RSkSVGNode.h"

namespace facebook {
namespace react {

using namespace std;

class RSkComponentRNSVGSvgView final : public RSkSVGContainerComponent  {
 public:

  RSkComponentRNSVGSvgView(const ShadowView &shadowView);
  ~RSkComponentRNSVGSvgView() = default;
  
  //Override for Base Class :RSkComponent
  RnsShell::LayerInvalidateMask updateComponentProps(SharedProps newViewProps,bool forceUpdate) override;

  SkSize getContainerSize(const SkSVGLengthContext&) const;
  
 protected:

    //Overrides for Base Class :RSkComponent
    void OnPaint(SkCanvas *canvas) override;

    //Overrides for Base Class :RSkSVGContainer
    bool onPrepareToRender(SkSVGRenderContext*) const override;
    void onSetAttribute(SkSVGAttribute, const SkSVGValue&) override;

    const SkSize containerSize() const {return svgContainerSize;}

 private:
 
    SkSize           svgContainerSize;

    SkSVGLength x_      = SkSVGLength(0);
    SkSVGLength y_      = SkSVGLength(0);
    SkSVGLength width_  = SkSVGLength(100, SkSVGLength::Unit::kPercentage);
    SkSVGLength height_ = SkSVGLength(100, SkSVGLength::Unit::kPercentage);
    SkRect viewBox_;

    void alterSkiaDefaultPaint();

    typedef RSkSVGContainerComponent INHERITED;
};

} // namespace react
} // namespace facebook

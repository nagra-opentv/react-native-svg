/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "RSkComponentRNSVGGroup.h"

namespace facebook {
namespace react {

RSkComponentRNSVGGroup::RSkComponentRNSVGGroup(const ShadowView &shadowView)
    : INHERITED(shadowView,LAYER_TYPE_DEFAULT,SkSVGTag::kG) {
      RNS_LOG_ERROR("\n ######## CREATED SVG NODE WITH TAG : " <<(int)tag());
    }

RnsShell::LayerInvalidateMask  RSkComponentRNSVGGroup::updateComponentProps(SharedProps newViewProps,bool forceUpdate) {
  RnsShell::LayerInvalidateMask invalidateMask = RnsShell::LayerInvalidateNone;

  auto component = getComponentData();

  auto const &newRNSVGGroupPropsProps = *std::static_pointer_cast<RNSVGGroupProps const>(newViewProps);

  RNS_LOG_DEBUG( " Width :: "<<component.layoutMetrics.frame.size.width<<" Height :: "<<component.layoutMetrics.frame.size.height<< " X:: "<<component.layoutMetrics.frame.origin.x<< " Y:: "<<component.layoutMetrics.frame.origin.y);
  setCommonRenderableProps(newRNSVGGroupPropsProps);
  setCommonNodeProps(newRNSVGGroupPropsProps);
  setCommonGroupProps(newRNSVGGroupPropsProps);
  return invalidateMask;
}

void RSkComponentRNSVGGroup::alterSkiaDefaultPaint() {
 //Note: Skia's default paint is black. WhereIn on SVG REference platform it's transparent
 //      To Match with Reference output, for the next immendiate child of SVGView,
//        resetting color to transparent, if color not speciifed

  auto component = getComponentData();
  auto const &newRNSVGGroupPropsProps = *std::static_pointer_cast<RNSVGGroupProps const>(component.props);

  // Reset Stroke & Fill Color if not specifed to transparent
  if(std::find (newRNSVGGroupPropsProps.propList.begin(), newRNSVGGroupPropsProps.propList.end(), "fill") == newRNSVGGroupPropsProps.propList.end()) {
    setPaintAttribute(SkSVGAttribute::kFill,"none");
  }
  if(std::find (newRNSVGGroupPropsProps.propList.begin(), newRNSVGGroupPropsProps.propList.end(), "stroke") == newRNSVGGroupPropsProps.propList.end()) {
    setPaintAttribute(SkSVGAttribute::kStroke,"none");
  }
}

} // namespace react
} // namespace facebook

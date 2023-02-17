/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "react/renderer/components/rnsvg/RNSVGComponentDescriptors.h"

#include "ReactSkia/components/RSkComponentProvider.h"
#include "ReactSkia/utils/RnsUtils.h"
#include "RSkComponentRNSVGCircle.h"
#include "RSkComponentRNSVGDefs.h"
#include "RSkComponentRNSVGEllipse.h"
#include "RSkComponentRNSVGGroup.h"
#include "RSkComponentRNSVGLine.h"
#include "RSkComponentRNSVGPath.h"
#include "RSkComponentRNSVGRect.h"
#include "RSkComponentRNSVGText.h"
#include "RSkComponentRNSVGTSpan.h"
#include "RSkComponentRNSVGUse.h"
#include "RSkComponentRNSVGSvgView.h"

#define SETUP_COMPOMNENT_PROVIDER_FOR(SVGElement) \
class RSkComponentProvider##SVGElement : public RSkComponentProvider { \
 public: \
  RSkComponentProvider##SVGElement(){} \
  ComponentDescriptorProvider GetDescriptorProvider() override { \
    return concreteComponentDescriptorProvider<SVGElement##ComponentDescriptor>(); \
  }\
  std::shared_ptr<RSkComponent> CreateComponent( \
    const ShadowView &shadowView) override { \
    return std::static_pointer_cast<RSkComponent>( \
      std::make_shared<RSkComponent##SVGElement>(shadowView)); \
  } \
};

namespace facebook {
namespace react {

SETUP_COMPOMNENT_PROVIDER_FOR(RNSVGSvgView)
SETUP_COMPOMNENT_PROVIDER_FOR(RNSVGGroup)
SETUP_COMPOMNENT_PROVIDER_FOR(RNSVGCircle)
SETUP_COMPOMNENT_PROVIDER_FOR(RNSVGRect)
SETUP_COMPOMNENT_PROVIDER_FOR(RNSVGEllipse)
SETUP_COMPOMNENT_PROVIDER_FOR(RNSVGPath)
SETUP_COMPOMNENT_PROVIDER_FOR(RNSVGLine)
SETUP_COMPOMNENT_PROVIDER_FOR(RNSVGText)
SETUP_COMPOMNENT_PROVIDER_FOR(RNSVGTSpan)
SETUP_COMPOMNENT_PROVIDER_FOR(RNSVGUse)
SETUP_COMPOMNENT_PROVIDER_FOR(RNSVGDefs)

#ifdef __cplusplus 
extern "C" { 
#endif 
RNS_EXPORT_COMPONENT_PROVIDER(RNSVGSvgView)
RNS_EXPORT_COMPONENT_PROVIDER(RNSVGGroup)
RNS_EXPORT_COMPONENT_PROVIDER(RNSVGCircle)
RNS_EXPORT_COMPONENT_PROVIDER(RNSVGRect)
RNS_EXPORT_COMPONENT_PROVIDER(RNSVGEllipse)
RNS_EXPORT_COMPONENT_PROVIDER(RNSVGPath)
RNS_EXPORT_COMPONENT_PROVIDER(RNSVGLine)
RNS_EXPORT_COMPONENT_PROVIDER(RNSVGText)
RNS_EXPORT_COMPONENT_PROVIDER(RNSVGTSpan)
RNS_EXPORT_COMPONENT_PROVIDER(RNSVGUse)
RNS_EXPORT_COMPONENT_PROVIDER(RNSVGDefs)

#ifdef __cplusplus 
} 
#endif

} // namespace react
} // namespace facebook
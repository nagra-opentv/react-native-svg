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
#include "RSkComponentRNSVGLinearGradient.h"
#include "RSkComponentRNSVGPath.h"
#include "RSkComponentRNSVGRect.h"
#include "RSkComponentRNSVGText.h"
#include "RSkComponentRNSVGTSpan.h"
#include "RSkComponentRNSVGUse.h"
#include "RSkComponentRNSVGSvgView.h"

namespace facebook {
namespace react {

RNS_SETUP_COMPOMNENT_PROVIDER(RNSVGSvgView)
RNS_SETUP_COMPOMNENT_PROVIDER(RNSVGGroup)
RNS_SETUP_COMPOMNENT_PROVIDER(RNSVGCircle)
RNS_SETUP_COMPOMNENT_PROVIDER(RNSVGRect)
RNS_SETUP_COMPOMNENT_PROVIDER(RNSVGEllipse)
RNS_SETUP_COMPOMNENT_PROVIDER(RNSVGPath)
RNS_SETUP_COMPOMNENT_PROVIDER(RNSVGLine)
RNS_SETUP_COMPOMNENT_PROVIDER(RNSVGText)
RNS_SETUP_COMPOMNENT_PROVIDER(RNSVGTSpan)
RNS_SETUP_COMPOMNENT_PROVIDER(RNSVGLinearGradient)
RNS_SETUP_COMPOMNENT_PROVIDER(RNSVGUse)
RNS_SETUP_COMPOMNENT_PROVIDER(RNSVGDefs)

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
RNS_EXPORT_COMPONENT_PROVIDER(RNSVGLinearGradient)
RNS_EXPORT_COMPONENT_PROVIDER(RNSVGUse)
RNS_EXPORT_COMPONENT_PROVIDER(RNSVGDefs)

#ifdef __cplusplus 
} 
#endif

} // namespace react
} // namespace facebook
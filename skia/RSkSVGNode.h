/*
 * Copyright (C) 1994-present OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */
#pragma once

#include <string>
#include "include/core/SkScalar.h"
#include "include/core/SkPath.h"

#include "include/core/SkColor.h"

#include "experimental/svg/model/SkSVGValue.h"
#include "include/utils/SkParsePath.h"
#include "experimental/svg/model/SkSVGTypes.h"
#include "experimental/svg/model/SkSVGTransformableNode.h"
#include "experimental/svg/model/SkSVGRenderContext.h"
#include "experimental/svg/model/SkSVGAttribute.h"
#include "experimental/svg/model/SkSVGAttributeParser.h"
#include "experimental/svg/model/SkSVGIDMapper.h"
#include "experimental/svg/model/SkSVGNode.h"

#include "ReactSkia/components/RSkComponent.h"
using namespace std;


namespace facebook {
namespace react {

class RSkSVGNode  {
public:

    static sk_sp<SkSVGNode> getRSkSVGNodeForComponetWithName(std::shared_ptr<RSkComponent> newChildComponent);
    static RSkSVGNode* getSVGRefNameForComponetWithName(std::shared_ptr<RSkComponent> component);

    bool setNumberAttribute(const sk_sp<SkSVGNode>& node, SkSVGAttribute attr,const char* stringValue);
    bool setStringAttribute( const sk_sp<SkSVGNode>& node,SkSVGAttribute attr,const char* stringValue);
    bool setPaintAttribute( const sk_sp<SkSVGNode>& node,SkSVGAttribute attr,const char* stringValue);
    bool setColorAttribute( const sk_sp<SkSVGNode>& node,SkSVGAttribute attr,const char* stringValue);
    bool setLengthAttribute( const sk_sp<SkSVGNode>& node,SkSVGAttribute attr,const char* stringValue);
    bool setPathDataAttribute( const sk_sp<SkSVGNode>& node,SkSVGAttribute attr,const char* stringValue);
    bool setFillRuleAttribute( const sk_sp<SkSVGNode>& node,SkSVGAttribute attr,const char* stringValue);
    bool setLineCapAttribute( const sk_sp<SkSVGNode>& node,SkSVGAttribute attr,const char* stringValue);
    bool setLineJoinAttribute( const sk_sp<SkSVGNode>& node,SkSVGAttribute attr,const char* stringValue);
    bool setViewBoxAttribute(const sk_sp<SkSVGNode>& node, SkSVGAttribute attr,const char* stringValue);   
    bool setIRIAttribute( const sk_sp<SkSVGNode>& node,SkSVGAttribute attr,const char* stringValue);
    bool setSpreadMethodAttribute(const sk_sp<SkSVGNode>& node, SkSVGAttribute attr,const char* stringValue);
    bool setStopColorAttribute(const sk_sp<SkSVGNode>& node, SkSVGAttribute attr,const char* stringValue);  
    bool setPointsAttribute(const sk_sp<SkSVGNode>& node, SkSVGAttribute attr,const char* stringValue);
    bool setVisibilityAttribute(const sk_sp<SkSVGNode>& node, SkSVGAttribute attr,const char* stringValue);
    bool setClipPathAttribute(const sk_sp<SkSVGNode>& node, SkSVGAttribute attr,const char* stringValue);
    bool setTransformAttribute(const sk_sp<SkSVGNode>& node,SkSVGAttribute attr,const std::vector<Float> matrix);
    bool setDashArrayAttribute(const sk_sp<SkSVGNode>& node, SkSVGAttribute attr,const std::vector<std::string> dashArray);    

    std::string nodeName;

private :

};

} // namespace react
} // namespace facebook
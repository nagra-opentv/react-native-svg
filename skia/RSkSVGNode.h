/*
 * Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */
#pragma once

#include <string>
#include <better/map.h>

#include "include/core/SkColor.h"

#include "experimental/svg/model/SkSVGValue.h"
#include "include/utils/SkParsePath.h"
#include "experimental/svg/model/SkSVGTypes.h"
#include "experimental/svg/model/SkSVGTransformableNode.h"
#include "experimental/svg/model/SkSVGRenderContext.h"
#include "experimental/svg/model/SkSVGAttribute.h"
#include "experimental/svg/model/SkSVGAttributeParser.h"
#include "experimental/svg/model/SkSVGIDMapper.h"

#include "ReactSkia/components/RSkComponent.h"
#include "ReactSkia/utils/RnsUtils.h"

using namespace std;

namespace facebook {
namespace react {


class RSkSVGNode : public SkSVGTransformableNode{
  public:
    ~RSkSVGNode()override = default;
    
    static RSkSVGNode* getRSkSVGNodeForComponetWithName(std::shared_ptr<RSkComponent> newChildComponent);

    bool setNumberAttribute( SkSVGAttribute attr,const char* stringValue);
    bool setStringAttribute( SkSVGAttribute attr,const char* stringValue);
    bool setPaintAttribute( SkSVGAttribute attr,const char* stringValue);
    bool setColorAttribute( SkSVGAttribute attr,const char* stringValue);
    bool setLengthAttribute( SkSVGAttribute attr,const char* stringValue);
    bool setPathDataAttribute( SkSVGAttribute attr,const char* stringValue);
    bool setFillRuleAttribute( SkSVGAttribute attr,const char* stringValue);
    bool setLineCapAttribute( SkSVGAttribute attr,const char* stringValue);
    bool setLineJoinAttribute( SkSVGAttribute attr,const char* stringValue);
    bool setViewBoxAttribute( SkSVGAttribute attr,const char* stringValue);   
    bool setIRIAttribute( SkSVGAttribute attr,const char* stringValue);
    bool setSpreadMethodAttribute( SkSVGAttribute attr,const char* stringValue);
    bool setStopColorAttribute( SkSVGAttribute attr,const char* stringValue);  
    bool setPointsAttribute( SkSVGAttribute attr,const char* stringValue);
    bool setVisibilityAttribute( SkSVGAttribute attr,const char* stringValue);
    bool setClipPathAttribute( SkSVGAttribute attr,const char* stringValue);
    bool setTransformAttribute(SkSVGAttribute attr,const std::vector<Float> matrix);
    bool setDashArrayAttribute( SkSVGAttribute attr,const std::vector<std::string> dashArray);    

    std::string nodeName;
    
  protected:
    RSkSVGNode(SkSVGTag tag); 

    SkPath onAsPath(const SkSVGRenderContext&)  const override { SkPath path;return path; };
    void appendChild(sk_sp<SkSVGNode>)  override {};

  private :

    typedef SkSVGTransformableNode INHERITED;

};

} // namespace react
} // namespace facebook
/*
 * Copyright (C) 1994-present OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */
#pragma once

#include <string>
#include <better/map.h>

#include "experimental/svg/model/SkSVGValue.h"
#include "include/utils/SkParsePath.h"
#include "experimental/svg/model/SkSVGTypes.h"
#include "experimental/svg/model/SkSVGTransformableNode.h"
#include "experimental/svg/model/SkSVGRenderContext.h"
#include "experimental/svg/model/SkSVGAttribute.h"
#include "experimental/svg/model/SkSVGAttributeParser.h"

#include "ReactSkia/RSkThirdPartyFabricComponentsProvider.h"
#include "ReactSkia/utils/RnsUtils.h"

using namespace std;

namespace facebook {
namespace react {


class RSkSVGNode : public SkSVGTransformableNode{
  public:
    ~RSkSVGNode() = default;

    virtual void appendChild(sk_sp<RSkSVGNode>) = 0;
    virtual sk_sp<RSkSVGNode> findNodeById(const char* id) { return nullptr;}
    void setParentNode(sk_sp<RSkSVGNode> node) {parentNode=node;}

    static sk_sp<RSkSVGNode> getRSkSVGNodeForComponnetWIthName(std::string componentName,std::shared_ptr<RSkComponent> newChildComponent);
    
    std::string nodeName;
   static RSkComponentProviderProtocol RSKSVGComponentViewClassWithName(ComponentName componentName) {
     return RSkThirdPartyFabricComponentsProvider(componentName);
   }

    bool SetPaintAttribute(const sk_sp<RSkSVGNode>& node, SkSVGAttribute attr,const char* stringValue);
    bool SetColorAttribute(const sk_sp<RSkSVGNode>& node, SkSVGAttribute attr,const char* stringValue);
    bool SetLengthAttribute(const sk_sp<RSkSVGNode>& node, SkSVGAttribute attr,const char* stringValue);
    bool SetPathDataAttribute(const sk_sp<RSkSVGNode>& node, SkSVGAttribute attr,const char* stringValue);
    bool SetLineCapAttribute(const sk_sp<RSkSVGNode>& node, SkSVGAttribute attr,const char* stringValue);
    bool SetLineJoinAttribute(const sk_sp<RSkSVGNode>& node, SkSVGAttribute attr,const char* stringValue);
    bool SetSpreadMethodAttribute(const sk_sp<RSkSVGNode>& node, SkSVGAttribute attr,const char* stringValue);
    bool SetStopColorAttribute(const sk_sp<RSkSVGNode>& node, SkSVGAttribute attr,const char* stringValue);  
    bool SetPointsAttribute(const sk_sp<RSkSVGNode>& node, SkSVGAttribute attr,const char* stringValue);
    bool SetFillRuleAttribute(const sk_sp<RSkSVGNode>& node, SkSVGAttribute attr,const char* stringValue);
    bool SetVisibilityAttribute(const sk_sp<RSkSVGNode>& node, SkSVGAttribute attr,const char* stringValue);
    bool SetDashArrayAttribute(const sk_sp<RSkSVGNode>& node, SkSVGAttribute attr,const char* stringValue);    
    bool SetViewBoxAttribute(const sk_sp<RSkSVGNode>& node, SkSVGAttribute attr,const char* stringValue);   
    bool SetNumberAttribute(const sk_sp<RSkSVGNode>& node, SkSVGAttribute attr,const char* stringValue);
    bool SetTransformAttribute(const sk_sp<RSkSVGNode>& node, SkSVGAttribute attr,const char* stringValue);
    bool SetStringAttribute(const sk_sp<RSkSVGNode>& node, SkSVGAttribute attr,const char* stringValue);
    bool SetClipPathAttribute(const sk_sp<RSkSVGNode>& node, SkSVGAttribute attr,const char* stringValue);
    bool SetIRIAttribute(const sk_sp<RSkSVGNode>& node, SkSVGAttribute attr,const char* stringValue);
  protected:
    RSkSVGNode(SkSVGTag tag); 
    sk_sp<RSkSVGNode> parentNode;

    SkPath onAsPath(const SkSVGRenderContext&)  const override { SkPath path;return path; };
    void appendChild(sk_sp<SkSVGNode>)  override {};

  private :

    typedef SkSVGTransformableNode INHERITED;

};

} // namespace react
} // namespace facebook
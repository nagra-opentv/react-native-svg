/*
 * Copyright (C) 1994-present OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "RSkComponentRNSVGCircle.h"
#include "RSkComponentRNSVGRect.h"
#include "RSkComponentRNSVGEllipse.h"
#include "RSkComponentRNSVGPath.h"
#include "RSkComponentRNSVGG.h"
#include "RSkComponentRNSVGView.h"
#include "RSkComponentRNSVGDefs.h"
#include "RSkComponentRNSVGUse.h"
#include "RSkSVGNode.h"

namespace facebook {
namespace react {

RSkSVGNode::RSkSVGNode(SkSVGTag tag) : INHERITED(tag) {};
 
bool RSkSVGNode::SetPaintAttribute(const sk_sp<RSkSVGNode>& node, SkSVGAttribute attr,
                       const char* stringValue) {
    SkSVGPaint paint;
    SkSVGAttributeParser parser(stringValue);
    if (!parser.parsePaint(&paint)) {
        return false;
    }

    node->setAttribute(attr, SkSVGPaintValue(paint));
    return true;
}

bool RSkSVGNode::SetColorAttribute(const sk_sp<RSkSVGNode>& node, SkSVGAttribute attr,
                       const char* stringValue) {
    SkSVGColorType color;
    SkSVGAttributeParser parser(stringValue);
    if (!parser.parseColor(&color)) {
        return false;
    }

    node->setAttribute(attr, SkSVGColorValue(color));
    return true;
}

bool RSkSVGNode::SetIRIAttribute(const sk_sp<RSkSVGNode>& node, SkSVGAttribute attr,
                      const char* stringValue) {
    SkSVGStringType iri;
    SkSVGAttributeParser parser(stringValue);
    if (!parser.parseIRI(&iri)) {
        return false;
    }

    node->setAttribute(attr, SkSVGStringValue(iri));
    return true;
}

bool RSkSVGNode::SetClipPathAttribute(const sk_sp<RSkSVGNode>& node, SkSVGAttribute attr,
                          const char* stringValue) {
    SkSVGClip clip;
    SkSVGAttributeParser parser(stringValue);
    if (!parser.parseClipPath(&clip)) {
        return false;
    }

    node->setAttribute(attr, SkSVGClipValue(clip));
    return true;
}


bool RSkSVGNode::SetPathDataAttribute(const sk_sp<RSkSVGNode>& node, SkSVGAttribute attr,
                          const char* stringValue) {
    SkPath path;
    if (!SkParsePath::FromSVGString(stringValue, &path)) {
        return false;
    }

    node->setAttribute(attr, SkSVGPathValue(path));
    return true;
}

bool RSkSVGNode::SetStringAttribute(const sk_sp<RSkSVGNode>& node, SkSVGAttribute attr,
                           const char* stringValue) {
    SkString str(stringValue, strlen(stringValue));
    SkSVGStringType strType = SkSVGStringType(str);
    node->setAttribute(attr, SkSVGStringValue(strType));
    return true;
}

bool RSkSVGNode::SetTransformAttribute(const sk_sp<RSkSVGNode>& node, SkSVGAttribute attr,
                           const char* stringValue) {
    SkSVGTransformType transform;
    SkSVGAttributeParser parser(stringValue);
    if (!parser.parseTransform(&transform)) {
        return false;
    }

    node->setAttribute(attr, SkSVGTransformValue(transform));
    return true;
}

bool RSkSVGNode::SetLengthAttribute(const sk_sp<RSkSVGNode>& node, SkSVGAttribute attr,
                        const char* stringValue) {
    SkSVGLength length;
    SkSVGAttributeParser parser(stringValue);
    if (!parser.parseLength(&length)) {
        return false;
    }

    node->setAttribute(attr, SkSVGLengthValue(length));
    return true;
}

bool RSkSVGNode::SetNumberAttribute(const sk_sp<RSkSVGNode>& node, SkSVGAttribute attr,
                        const char* stringValue) {
    SkSVGNumberType number;
    SkSVGAttributeParser parser(stringValue);
    if (!parser.parseNumber(&number)) {
        return false;
    }

    node->setAttribute(attr, SkSVGNumberValue(number));
    return true;
}

bool RSkSVGNode::SetViewBoxAttribute(const sk_sp<RSkSVGNode>& node, SkSVGAttribute attr,
                         const char* stringValue) {
    SkSVGViewBoxType viewBox;
    SkSVGAttributeParser parser(stringValue);
    if (!parser.parseViewBox(&viewBox)) {
        return false;
    }

    node->setAttribute(attr, SkSVGViewBoxValue(viewBox));
    return true;
}

bool RSkSVGNode::SetLineCapAttribute(const sk_sp<RSkSVGNode>& node, SkSVGAttribute attr,
                         const char* stringValue) {
    SkSVGLineCap lineCap;
    SkSVGAttributeParser parser(stringValue);
    if (!parser.parseLineCap(&lineCap)) {
        return false;
    }

    node->setAttribute(attr, SkSVGLineCapValue(lineCap));
    return true;
}

bool RSkSVGNode::SetLineJoinAttribute(const sk_sp<RSkSVGNode>& node, SkSVGAttribute attr,
                          const char* stringValue) {
    SkSVGLineJoin lineJoin;
    SkSVGAttributeParser parser(stringValue);
    if (!parser.parseLineJoin(&lineJoin)) {
        return false;
    }

    node->setAttribute(attr, SkSVGLineJoinValue(lineJoin));
    return true;
}

bool RSkSVGNode::SetSpreadMethodAttribute(const sk_sp<RSkSVGNode>& node, SkSVGAttribute attr,
                             const char* stringValue) {
    SkSVGSpreadMethod spread;
    SkSVGAttributeParser parser(stringValue);
    if (!parser.parseSpreadMethod(&spread)) {
        return false;
    }

    node->setAttribute(attr, SkSVGSpreadMethodValue(spread));
    return true;
}

bool RSkSVGNode::SetStopColorAttribute(const sk_sp<RSkSVGNode>& node, SkSVGAttribute attr,
                           const char* stringValue) {
    SkSVGStopColor stopColor;
    SkSVGAttributeParser parser(stringValue);
    if (!parser.parseStopColor(&stopColor)) {
        return false;
    }

    node->setAttribute(attr, SkSVGStopColorValue(stopColor));
    return true;
}

bool RSkSVGNode::SetPointsAttribute(const sk_sp<RSkSVGNode>& node, SkSVGAttribute attr,
                        const char* stringValue) {
    SkSVGPointsType points;
    SkSVGAttributeParser parser(stringValue);
    if (!parser.parsePoints(&points)) {
        return false;
    }

    node->setAttribute(attr, SkSVGPointsValue(points));
    return true;
}

bool RSkSVGNode::SetFillRuleAttribute(const sk_sp<RSkSVGNode>& node, SkSVGAttribute attr,
                          const char* stringValue) {
    SkSVGFillRule fillRule;
    SkSVGAttributeParser parser(stringValue);
    if (!parser.parseFillRule(&fillRule)) {
        return false;
    }

    node->setAttribute(attr, SkSVGFillRuleValue(fillRule));
    return true;
}

bool RSkSVGNode::SetVisibilityAttribute(const sk_sp<RSkSVGNode>& node, SkSVGAttribute attr,
                            const char* stringValue) {
    SkSVGVisibility visibility;
    SkSVGAttributeParser parser(stringValue);
    if (!parser.parseVisibility(&visibility)) {
        return false;
    }

    node->setAttribute(attr, SkSVGVisibilityValue(visibility));
    return true;
}

bool RSkSVGNode::SetDashArrayAttribute(const sk_sp<RSkSVGNode>& node, SkSVGAttribute attr,
                           const char* stringValue) {
    SkSVGDashArray dashArray;
    SkSVGAttributeParser parser(stringValue);
    if (!parser.parseDashArray(&dashArray)) {
        return false;
    }

    node->setAttribute(attr, SkSVGDashArrayValue(dashArray));
    return true;
}

sk_sp<RSkSVGNode> RSkSVGNode::getRSkSVGNodeForComponnetWIthName(std::string componentName,std::shared_ptr<RSkComponent> component) { 

  enum componentName {
 	RNSVGCircle,
 	RNSVGRect,
    RNSVGEllipse,
    RNSVGPath,
    RNSVGDefs,
    RNSVGUse,
    RNSVGGroup,
    RNSVGView
 };
 static std::map<std::string, enum componentName> s_mapStringValues ={
 	{ "RNSVGCircle", RNSVGCircle},
 	{ "RNSVGRect",RNSVGRect},
    { "RNSVGEllipse",RNSVGEllipse},
    { "RNSVGPath",RNSVGPath},
    { "RNSVGDefs",RNSVGDefs},
    { "RNSVGUse",RNSVGUse},
    { "RNSVGGroup",RNSVGGroup},
    { "RNSVGView",RNSVGView}
 };
 int index =-1;
 auto it=s_mapStringValues.find(componentName.c_str()); 
 if(it != s_mapStringValues.end()) {
 	index = s_mapStringValues[componentName.c_str()];
 }
 switch(index) {
 	case RNSVGCircle:
 	  RNS_LOG_INFO("\n getRRSkSVGNodeForComponnetWIthName :RNSVGCircle \n");
      return static_cast<RSkComponentRNSVGCircle *>(component.get())->getComponentNode();
 	break;
 	case RNSVGRect:
 	RNS_LOG_INFO("\n getRRSkSVGNodeForComponnetWIthName :RNSVGRect Class \n");
      return static_cast<RSkComponentRNSVGRect *>(component.get())->getComponentNode();
 	break;
 	case RNSVGEllipse:
 	RNS_LOG_INFO("\n getRRSkSVGNodeForComponnetWIthName :RNSVGEllipse Class \n");
      return static_cast<RSkComponentRNSVGEllipse *>(component.get())->getComponentNode();
 	break;
 	case RNSVGPath:
 	RNS_LOG_INFO("\n getRRSkSVGNodeForComponnetWIthName :RNSVGPath Class \n");
      return static_cast<RSkComponentRNSVGPath *>(component.get())->getComponentNode();
 	break;
 	case RNSVGDefs:
 	RNS_LOG_INFO("\n getRRSkSVGNodeForComponnetWIthName :RNSVGDefs Class \n");
      return static_cast<RSkComponentRNSVGDefs *>(component.get())->getComponentNode();
 	break;
 	case RNSVGUse:
 	RNS_LOG_INFO("\n getRRSkSVGNodeForComponnetWIthName :RNSVGUse Class \n");
      return static_cast<RSkComponentRNSVGUse *>(component.get())->getComponentNode();
 	break;
 	case RNSVGGroup:
 	RNS_LOG_INFO("\n getRRSkSVGNodeForComponnetWIthName :RNSVGGroup Class \n");
      return static_cast<RSkComponentRNSVGGroup *>(component.get())->getComponentNode();
 	break;
 	case RNSVGView:
 	RNS_LOG_INFO("\n getRRSkSVGNodeForComponnetWIthName :RNSVGView Class \n");
      return static_cast<RSkComponentRNSVGView *>(component.get())->getComponentNode();
 	break;
 	default:
 	RNS_LOG_INFO("\n getRRSkSVGNodeForComponnetWIthName :UNKNOWN Class \n");
      return nullptr;
 	break;
 }
 
}



} // namespace react
} // namespace facebook
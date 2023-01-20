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


bool RSkSVGNode::setPaintAttribute(const sk_sp<SkSVGNode>& node,SkSVGAttribute attr, const char* stringValue) {
    SkSVGPaint paint;
    SkSVGAttributeParser parser(stringValue);
    if (!parser.parsePaint(&paint)) {
        return false;
    }
   node->setAttribute(attr, SkSVGPaintValue(paint));
    return true;
}

bool RSkSVGNode::setColorAttribute(const sk_sp<SkSVGNode>& node,SkSVGAttribute attr, const char* stringValue) {
    SkSVGColorType color;
    SkSVGAttributeParser parser(stringValue);
    if (!parser.parseColor(&color)) {
        return false;
    }
   node->setAttribute(attr, SkSVGColorValue(color));
    return true;
}

bool RSkSVGNode::setIRIAttribute(const sk_sp<SkSVGNode>& node,SkSVGAttribute attr, const char* stringValue) {
    SkSVGStringType iri;
    SkSVGAttributeParser parser(stringValue);
    if (!parser.parseIRI(&iri)) {
        return false;
    }
   node->setAttribute(attr, SkSVGStringValue(iri));
    return true;
}

bool RSkSVGNode::setClipPathAttribute(const sk_sp<SkSVGNode>& node,SkSVGAttribute attr, const char* stringValue) {
    SkSVGClip clip;
    SkSVGAttributeParser parser(stringValue);
    if (!parser.parseClipPath(&clip)) {
        return false;
    }
   node->setAttribute(attr, SkSVGClipValue(clip));
    return true;
}


bool RSkSVGNode::setPathDataAttribute(const sk_sp<SkSVGNode>& node,SkSVGAttribute attr, const char* stringValue) {
    SkPath path;
    if (!SkParsePath::FromSVGString(stringValue, &path)) {
        return false;
    }
   node->setAttribute(attr, SkSVGPathValue(path));
    return true;
}

bool RSkSVGNode::setStringAttribute(const sk_sp<SkSVGNode>& node,SkSVGAttribute attr, const char* stringValue) {
    SkString str(stringValue, strlen(stringValue));
    SkSVGStringType strType = SkSVGStringType(str);
   node->setAttribute(attr, SkSVGStringValue(strType));
    return true;
}

bool RSkSVGNode::setLengthAttribute(const sk_sp<SkSVGNode>& node,SkSVGAttribute attr, const char* stringValue) {
    SkSVGLength length;
    SkSVGAttributeParser parser(stringValue);
    if (!parser.parseLength(&length)) {
        return false;
    }
   node->setAttribute(attr, SkSVGLengthValue(length));
    return true;
}

bool RSkSVGNode::setNumberAttribute(const sk_sp<SkSVGNode>& node,SkSVGAttribute attr, const char* stringValue) {
    SkSVGNumberType number;
    SkSVGAttributeParser parser(stringValue);
    if (!parser.parseNumber(&number)) {
        return false;
    }
   node->setAttribute(attr, SkSVGNumberValue(number));
    return true;
}

bool RSkSVGNode::setViewBoxAttribute(const sk_sp<SkSVGNode>& node,SkSVGAttribute attr, const char* stringValue) {
    SkSVGViewBoxType viewBox;
    SkSVGAttributeParser parser(stringValue);
    if (!parser.parseViewBox(&viewBox)) {
        return false;
    }
   node->setAttribute(attr, SkSVGViewBoxValue(viewBox));
    return true;
}

bool RSkSVGNode::setLineCapAttribute(const sk_sp<SkSVGNode>& node,SkSVGAttribute attr, const char* stringValue) {
    SkSVGLineCap lineCap;
    SkSVGAttributeParser parser(stringValue);
    if (!parser.parseLineCap(&lineCap)) {
        return false;
    }
   node->setAttribute(attr, SkSVGLineCapValue(lineCap));
    return true;
}

bool RSkSVGNode::setLineJoinAttribute(const sk_sp<SkSVGNode>& node,SkSVGAttribute attr, const char* stringValue) {
    SkSVGLineJoin lineJoin;
    SkSVGAttributeParser parser(stringValue);
    if (!parser.parseLineJoin(&lineJoin)) {
        return false;
    }
   node->setAttribute(attr, SkSVGLineJoinValue(lineJoin));
    return true;
}

bool RSkSVGNode::setSpreadMethodAttribute(const sk_sp<SkSVGNode>& node,SkSVGAttribute attr,  const char* stringValue) {
    SkSVGSpreadMethod spread;
    SkSVGAttributeParser parser(stringValue);
    if (!parser.parseSpreadMethod(&spread)) {
        return false;
    }
   node->setAttribute(attr, SkSVGSpreadMethodValue(spread));
    return true;
}

bool RSkSVGNode::setStopColorAttribute(const sk_sp<SkSVGNode>& node,SkSVGAttribute attr, const char* stringValue) {
    SkSVGStopColor stopColor;
    SkSVGAttributeParser parser(stringValue);
    if (!parser.parseStopColor(&stopColor)) {
        return false;
    }
   node->setAttribute(attr, SkSVGStopColorValue(stopColor));
    return true;
}

bool RSkSVGNode::setPointsAttribute(const sk_sp<SkSVGNode>& node,SkSVGAttribute attr, const char* stringValue) {
    SkSVGPointsType points;
    SkSVGAttributeParser parser(stringValue);
    if (!parser.parsePoints(&points)) {
        return false;
    }
   node->setAttribute(attr, SkSVGPointsValue(points));
    return true;
}

bool RSkSVGNode::setFillRuleAttribute(const sk_sp<SkSVGNode>& node,SkSVGAttribute attr, const char* stringValue) {
    SkSVGFillRule fillRule;
    SkSVGAttributeParser parser(stringValue);
    if (!parser.parseFillRule(&fillRule)) {
        return false;
    }
   node->setAttribute(attr, SkSVGFillRuleValue(fillRule));
    return true;
}

bool RSkSVGNode::setVisibilityAttribute(const sk_sp<SkSVGNode>& node,SkSVGAttribute attr, const char* stringValue) {
    SkSVGVisibility visibility;
    SkSVGAttributeParser parser(stringValue);
    if (!parser.parseVisibility(&visibility)) {
        return false;
    }
   node->setAttribute(attr, SkSVGVisibilityValue(visibility));
    return true;
}

bool RSkSVGNode::setDashArrayAttribute(const sk_sp<SkSVGNode>& node,SkSVGAttribute attr, const std::vector<std::string> dashArrayAttribute) {

    if(dashArrayAttribute.empty()) return false;

    std::string dashArray;
    for(auto value : dashArrayAttribute) {
        RNS_LOG_INFO("has strokeDasharray value: "<<value.c_str());
        dashArray.append(value);
        dashArray.append(" ");
    }

    SkSVGDashArray parsedDashArray;
    SkSVGAttributeParser parser(dashArray.c_str());
    if (!parser.parseDashArray(&parsedDashArray)) {
        return false;
    }
   node->setAttribute(attr, SkSVGDashArrayValue(parsedDashArray));
    return true;
}

bool RSkSVGNode::setTransformAttribute(const sk_sp<SkSVGNode>& node,SkSVGAttribute attr,const std::vector<Float> matrix) {

    if(matrix.size() == 6) {
        RNS_LOG_INFO(" Matrix 0 : "<<matrix[0]);
        RNS_LOG_INFO(" Matrix 1 : "<<matrix[1]);
        RNS_LOG_INFO(" Matrix 2 : "<<matrix[2]);
        RNS_LOG_INFO(" Matrix 3 : "<<matrix[3]);
        RNS_LOG_INFO(" Matrix 4 : "<<matrix[4]);
        RNS_LOG_INFO(" Matrix 5 : "<<matrix[5]);

        SkMatrix svgTransforMatrix=SkMatrix::Translate(matrix[4],matrix[5]);
        svgTransforMatrix.preConcat(SkMatrix::Scale(matrix[0],matrix[3]));
       node->setAttribute(attr,SkSVGTransformValue(svgTransforMatrix));

        RNS_LOG_INFO("getScaleX :"<<svgTransforMatrix.getScaleX());
        RNS_LOG_INFO("getScaleY :"<<svgTransforMatrix.getScaleY());
        RNS_LOG_INFO("getTranslateX :"<<svgTransforMatrix.getTranslateX());
        RNS_LOG_INFO("getTranslateY :"<<svgTransforMatrix.getTranslateY());
        RNS_LOG_INFO("getSkewX :"<<svgTransforMatrix.getSkewX());
        RNS_LOG_INFO("getSkewY :"<<svgTransforMatrix.getSkewY());
        return true;
    }
    return false;
}

sk_sp<SkSVGNode> RSkSVGNode::getRSkSVGNodeForComponetWithName(std::shared_ptr<RSkComponent> component) { 

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

  std::string componentName=component->getComponentData().componentName;

  int index =-1;
  if(s_mapStringValues.find(componentName.c_str()) != s_mapStringValues.end()) {
 	index = s_mapStringValues[componentName.c_str()];
  } 
  
  switch(index) {

 	case RNSVGCircle:
 	  RNS_LOG_INFO("\n SVG COMPONENT :" <<componentName.c_str());
      return static_cast<RSkComponentRNSVGCircle *>(component.get())->getComponentNode();
 	break;
 	case RNSVGRect:
 	  RNS_LOG_INFO("\n SVG COMPONENT :" <<componentName.c_str());
      return static_cast<RSkComponentRNSVGRect *>(component.get())->getComponentNode();
 	break;
 	case RNSVGEllipse:
 	  RNS_LOG_INFO("\n SVG COMPONENT :" <<componentName.c_str());
      return static_cast<RSkComponentRNSVGEllipse *>(component.get())->getComponentNode();
 	break;
 	case RNSVGPath:
 	  RNS_LOG_INFO("\n SVG COMPONENT :" <<componentName.c_str());
      return static_cast<RSkComponentRNSVGPath *>(component.get())->getComponentNode();
 	break;
 	case RNSVGDefs:
 	  RNS_LOG_INFO("\n SVG COMPONENT :" <<componentName.c_str());
      return static_cast<RSkComponentRNSVGDefs *>(component.get())->getComponentNode();
 	break;
 	case RNSVGUse:
 	  RNS_LOG_INFO("\n SVG COMPONENT :" <<componentName.c_str());
      return static_cast<RSkComponentRNSVGUse *>(component.get())->getComponentNode();
 	break;
 	case RNSVGGroup:
 	  RNS_LOG_INFO("\n SVG COMPONENT :" <<componentName.c_str());
      return static_cast<RSkComponentRNSVGGroup *>(component.get())->getComponentNode();
 	break;
 	case RNSVGView:
 	  RNS_LOG_INFO("\n SVG COMPONENT :" <<componentName.c_str());
      return static_cast<RSkComponentRNSVGView *>(component.get())->getComponentNode();
 	break;
 	default:
 	  RNS_LOG_INFO("\n SVG COMPONENT :UNKNOWN Class \n");
      return nullptr;
 	break;
 }
 
}

 RSkSVGNode* RSkSVGNode::getSVGRefNameForComponetWithName(std::shared_ptr<RSkComponent> component) { 

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

  std::string componentName=component->getComponentData().componentName;

  int index =-1;
  if(s_mapStringValues.find(componentName.c_str()) != s_mapStringValues.end()) {
 	index = s_mapStringValues[componentName.c_str()];
  } 
  
  switch(index) {
  
 	case RNSVGCircle:
 	  RNS_LOG_INFO("\n SVG COMPONENT :" <<componentName.c_str());
      return static_cast<RSkComponentRNSVGCircle *>(component.get());
 	break;
 	case RNSVGRect:
 	  RNS_LOG_INFO("\n SVG COMPONENT :" <<componentName.c_str());
      return static_cast<RSkComponentRNSVGRect *>(component.get());
 	break;
 	case RNSVGEllipse:
 	  RNS_LOG_INFO("\n SVG COMPONENT :" <<componentName.c_str());
      return static_cast<RSkComponentRNSVGEllipse *>(component.get());
 	break;
 	case RNSVGPath:
 	  RNS_LOG_INFO("\n SVG COMPONENT :" <<componentName.c_str());
      return static_cast<RSkComponentRNSVGPath *>(component.get());
 	break;
 	case RNSVGDefs:
 	  RNS_LOG_INFO("\n SVG COMPONENT :" <<componentName.c_str());
      return static_cast<RSkComponentRNSVGDefs *>(component.get());
 	break;
 	case RNSVGUse:
 	  RNS_LOG_INFO("\n SVG COMPONENT :" <<componentName.c_str());
      return static_cast<RSkComponentRNSVGUse *>(component.get());
 	break;
 	case RNSVGGroup:
 	  RNS_LOG_INFO("\n SVG COMPONENT :" <<componentName.c_str());
      return static_cast<RSkComponentRNSVGGroup *>(component.get());
 	break;
 	
 	case RNSVGView:
 	  RNS_LOG_INFO("\n SVG COMPONENT :" <<componentName.c_str());
      return static_cast<RSkComponentRNSVGView *>(component.get());
 	break;
 	default:
 	  RNS_LOG_INFO("\n SVG COMPONENT :UNKNOWN Class \n");
      return nullptr;
 	break;
 }
 
}

} // namespace react
} // namespace facebook
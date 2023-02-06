/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "ReactSkia/utils/RnsLog.h"
#include "RSkSVGContainer.h"
#include "RSkSVGNode.h"

namespace facebook {
namespace react {

RSkSVGNode::RSkSVGNode(SkSVGTag tag) : INHERITED(tag) {};

void RSkSVGNode::setCommonRenderableProps(const RNSVGCommonRenderableProps  &renderableProps) {

  RNS_LOG_DEBUG("Supported Properties count  :" << renderableProps.propList.size() << " : for SVG TAG: "<< (int)tag());
  RNS_LOG_DEBUG("##################");
  for (auto props : renderableProps.propList ) {
    RNS_LOG_DEBUG(props);
  }
  RNS_LOG_DEBUG("##################");

  for (auto &item : renderableProps.propList) {
    //Fill Props
    if(!strcmp(item.c_str(),"fill")) {
      setColorFromColorStruct(renderableProps.fill,SkSVGAttribute::kFill);
    } else if(!strcmp(item.c_str(),"fillOpacity")) {
      setNumberAttribute( SkSVGAttribute::kFillOpacity,std::to_string(renderableProps.fillOpacity));
    } else if(!strcmp(item.c_str(),"fillRule")) {
      setFillRuleAttribute(SkSVGAttribute::kFillRule,(renderableProps.fillRule == 0 ) ? "evenodd" :"nonzero");
    } else if(!strcmp(item.c_str(),"stroke")) {
      setColorFromColorStruct(renderableProps.stroke,SkSVGAttribute::kStroke);
    } else if(!strcmp(item.c_str(),"strokeOpacity")) {
      setNumberAttribute( SkSVGAttribute::kStrokeOpacity,std::to_string(renderableProps.strokeOpacity));
    } else if(!strcmp(item.c_str(),"strokeWidth")) {
      setLengthAttribute( SkSVGAttribute::kStrokeWidth,renderableProps.strokeWidth);
    } else  if(!strcmp(item.c_str(),"strokeLinecap")) {
      setLineCapAttribute(SkSVGAttribute::kStrokeLineCap,(renderableProps.strokeLinecap == 0 ) ? "butt" :
                                                        ((renderableProps.strokeLinecap == 1 ) ? "round":"square"));
    } else if(!strcmp(item.c_str(),"strokeLinejoin")) {
      setLineJoinAttribute(SkSVGAttribute::kStrokeLineJoin,(renderableProps.strokeLinejoin == 0 ) ? "miter" :
                                                          ((renderableProps.strokeLinejoin == 1 ) ? "round":"bevel")); 
    } else if(!strcmp(item.c_str(),"strokeDasharray")) {
      setDashArrayAttribute(SkSVGAttribute::kStrokeDashArray,renderableProps.strokeDasharray);
    } else if(!strcmp(item.c_str(),"strokeDashoffset")) {
      setLengthAttribute(SkSVGAttribute::kStrokeDashOffset,std::to_string(renderableProps.strokeDashoffset));
    } else if(!strcmp(item.c_str(),"strokeMiterlimit")) {
      setNumberAttribute( SkSVGAttribute::kStrokeMiterLimit,std::to_string(renderableProps.strokeMiterlimit));
    } else if(!strcmp(item.c_str(),"vectorEffect")) {
      //TODO : Vector EFFECT
    } else {
      RNS_LOG_WARN(" Unknown Property : "<<item);
    }
  }
}

void RSkSVGNode::setCommonNodeProps(const RNSVGCommonNodeProps &nodeProps){

  nodeName=nodeProps.name.c_str();
  //set Opacity
  setNumberAttribute(SkSVGAttribute::kOpacity,std::to_string(nodeProps.opacity).c_str());
  //set Transform
  setTransformAttribute(SkSVGAttribute::kTransform,nodeProps.matrix);
  //set clip properties :: TODO -- check the inheritence behavour for clip Props
  setFillRuleAttribute(SkSVGAttribute::kClipRule,(nodeProps.clipRule == 0 ) ? "evenodd" :"nonzero");
  setClipPathAttribute(SkSVGAttribute::kClipPath,nodeProps.clipPath.c_str());
}

void RSkSVGNode::setCommonGroupProps(const RNSVGGroupProps &groupProps) {
  RNS_LOG_TODO("setCommonGroupProps To Be Handled");
}

void RSkSVGNode::setColorFromColorStruct(RNSVGColorFillStruct  colorStruct,SkSVGAttribute attr){

  if(colorStruct.type == 0)  {
    if(colorStruct.payload) {
      auto colorValue = colorComponentsFromColor(colorStruct.payload);
      SkColor color= SkColorSetARGB(colorValue.alpha * 255.99,colorValue.red * 255.99,colorValue.green * 255.99,colorValue.blue * 255.99);
      SkSVGPaint paint(color);
      setAttribute(attr,SkSVGPaintValue(paint));
    } else {
      // Color specified as none
        setPaintAttribute(attr,"none");
    } 
 } else if(colorStruct.type ==  2) { // currentColor
   setPaintAttribute(attr,"currentColor");
 } else if(colorStruct.type == 3) { // context-fill
   RNS_LOG_TODO(" Support for color : context-fill , color struct type : " <<colorStruct.type);
 }else if(colorStruct.type == 4) { // context-stroke
   RNS_LOG_TODO(" Support for color : context-stroke , color struct type : " <<colorStruct.type);
 }else if(colorStruct.type == 1) { // brush ref
   RNS_LOG_TODO(" Support for color as brush Ref , color struct type : " <<colorStruct.type);
 }
}

bool RSkSVGNode::setPaintAttribute(SkSVGAttribute attr, std::string stringValue) {
  SkSVGPaint paint;
  SkSVGAttributeParser parser(stringValue.c_str());
  if (!parser.parsePaint(&paint)) {
    return false;
  }
  setAttribute(attr, SkSVGPaintValue(paint));
  return true;
}

bool RSkSVGNode::setColorAttribute(SkSVGAttribute attr, std::string stringValue) {
  SkSVGColorType color;
  SkSVGAttributeParser parser(stringValue.c_str());
  if (!parser.parseColor(&color)) {
    return false;
  }
  setAttribute(attr, SkSVGColorValue(color));
  return true;
}

bool RSkSVGNode::setIRIAttribute(SkSVGAttribute attr, std::string stringValue) {
  SkSVGStringType iri;
  SkSVGAttributeParser parser(stringValue.c_str());
  if (!parser.parseIRI(&iri)) {
    return false;
  }
  setAttribute(attr, SkSVGStringValue(iri));
  return true;
}

bool RSkSVGNode::setClipPathAttribute(SkSVGAttribute attr, std::string stringValue) {
  SkSVGClip clip;
  SkSVGAttributeParser parser(stringValue.c_str());
  if (!parser.parseClipPath(&clip)) {
    return false;
  }
  setAttribute(attr, SkSVGClipValue(clip));
  return true;
}

bool RSkSVGNode::setPathDataAttribute(SkSVGAttribute attr, std::string stringValue) {
  SkPath path;
  if (!SkParsePath::FromSVGString(stringValue.c_str(), &path)) {
    return false;
  }
  setAttribute(attr, SkSVGPathValue(path));
  return true;
}

bool RSkSVGNode::setStringAttribute(SkSVGAttribute attr, std::string stringValue) {
  SkString str(stringValue.c_str(), stringValue.length());
  SkSVGStringType strType = SkSVGStringType(str);
  setAttribute(attr, SkSVGStringValue(strType));
  return true;
}

bool RSkSVGNode::setLengthAttribute(SkSVGAttribute attr, std::string stringValue) {
  SkSVGLength length;
  SkSVGAttributeParser parser(stringValue.c_str());
  if (!parser.parseLength(&length)) {
    return false;
  }
  setAttribute(attr, SkSVGLengthValue(length));
  return true;
}

bool RSkSVGNode::setNumberAttribute(SkSVGAttribute attr, std::string stringValue) {
  SkSVGNumberType number;
  SkSVGAttributeParser parser(stringValue.c_str());
  if (!parser.parseNumber(&number)) {
    return false;
  }
  setAttribute(attr, SkSVGNumberValue(number));
  return true;
}

bool RSkSVGNode::setViewBoxAttribute(SkSVGAttribute attr, std::string stringValue) {
  SkSVGViewBoxType viewBox;
  SkSVGAttributeParser parser(stringValue.c_str());
  if (!parser.parseViewBox(&viewBox)) {
    return false;
  }
  setAttribute(attr, SkSVGViewBoxValue(viewBox));
  return true;
}

bool RSkSVGNode::setLineCapAttribute(SkSVGAttribute attr, std::string stringValue) {
  SkSVGLineCap lineCap;
  SkSVGAttributeParser parser(stringValue.c_str());
  if (!parser.parseLineCap(&lineCap)) {
    return false;
  }
  setAttribute(attr, SkSVGLineCapValue(lineCap));
  return true;
}

bool RSkSVGNode::setLineJoinAttribute(SkSVGAttribute attr, std::string stringValue) {
  SkSVGLineJoin lineJoin;
  SkSVGAttributeParser parser(stringValue.c_str());
  if (!parser.parseLineJoin(&lineJoin)) {
    return false;
  }
  setAttribute(attr, SkSVGLineJoinValue(lineJoin));
  return true;
}

bool RSkSVGNode::setSpreadMethodAttribute(SkSVGAttribute attr,  std::string stringValue) {
  SkSVGSpreadMethod spread;
  SkSVGAttributeParser parser(stringValue.c_str());
  if (!parser.parseSpreadMethod(&spread)) {
    return false;
  }
  setAttribute(attr, SkSVGSpreadMethodValue(spread));
  return true;
}

bool RSkSVGNode::setStopColorAttribute(SkSVGAttribute attr, std::string stringValue) {
  SkSVGStopColor stopColor;
  SkSVGAttributeParser parser(stringValue.c_str());
  if (!parser.parseStopColor(&stopColor)) {
    return false;
  }
  setAttribute(attr, SkSVGStopColorValue(stopColor));
  return true;
}

bool RSkSVGNode::setPointsAttribute(SkSVGAttribute attr, std::string stringValue) {
  SkSVGPointsType points;
  SkSVGAttributeParser parser(stringValue.c_str());
  if (!parser.parsePoints(&points)) {
    return false;
  }
  setAttribute(attr, SkSVGPointsValue(points));
  return true;
}

bool RSkSVGNode::setFillRuleAttribute(SkSVGAttribute attr, std::string stringValue) {
  SkSVGFillRule fillRule;
  SkSVGAttributeParser parser(stringValue.c_str());
  if (!parser.parseFillRule(&fillRule)) {
    return false;
  }
  setAttribute(attr, SkSVGFillRuleValue(fillRule));
  return true;
}

bool RSkSVGNode::setVisibilityAttribute(SkSVGAttribute attr, std::string stringValue) {
  SkSVGVisibility visibility;
  SkSVGAttributeParser parser(stringValue.c_str());
  if (!parser.parseVisibility(&visibility)) {
    return false;
  }
  setAttribute(attr, SkSVGVisibilityValue(visibility));
  return true;
}

bool RSkSVGNode::setDashArrayAttribute(SkSVGAttribute attr, const std::vector<std::string> dashArrayAttribute) {

  if(dashArrayAttribute.empty()) return false;

  std::string dashArray;
  for(auto value : dashArrayAttribute) {
    RNS_LOG_DEBUG("has strokeDasharray value: "<<value.c_str());
    dashArray.append(value + " ");
  }

  SkSVGDashArray parsedDashArray;
  SkSVGAttributeParser parser(dashArray.c_str());
  if (!parser.parseDashArray(&parsedDashArray)) {
    return false;
  }
  setAttribute(attr, SkSVGDashArrayValue(parsedDashArray));
  return true;
}

bool RSkSVGNode::setTransformAttribute(SkSVGAttribute attr,const std::vector<Float> matrix) {

  if(matrix.size() == 6) {
    RNS_LOG_DEBUG(" Matrix 0 : "<<matrix[0]);
    RNS_LOG_DEBUG(" Matrix 1 : "<<matrix[1]);
    RNS_LOG_DEBUG(" Matrix 2 : "<<matrix[2]);
    RNS_LOG_DEBUG(" Matrix 3 : "<<matrix[3]);
    RNS_LOG_DEBUG(" Matrix 4 : "<<matrix[4]);
    RNS_LOG_DEBUG(" Matrix 5 : "<<matrix[5]);

    SkMatrix svgTransforMatrix=SkMatrix::Translate(matrix[4],matrix[5]);
    svgTransforMatrix.preConcat(SkMatrix::Scale(matrix[0],matrix[3]));
    setAttribute(attr,SkSVGTransformValue(svgTransforMatrix));

    return true;
  }
  return false;
}

SkPath RSkSVGNode::onAsPath(const SkSVGRenderContext&)  const  { 
  SkPath path;
  RNS_LOG_TODO("onAsPath : TO BE IMPLEMENTED IN CONTAINER & EACH SHAPE COMPONENT");
  return path;
};

void RSkSVGNode::appendChild(sk_sp<SkSVGNode>) {
  // Override from SKSVG Engine is Deprecated. 
  // Will use MountChildComponent to AppendChild from RSKSVGContainer Module
}

} // namespace react
} // namespace facebook
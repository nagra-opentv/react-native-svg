/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "ReactSkia/utils/RnsLog.h"
#include "RSkSVGNode.h"

namespace facebook {
namespace react {

RSkSVGNode::RSkSVGNode(SkSVGTag tag) : INHERITED(tag) {};

void RSkSVGNode::setCommonRenderableProps(const RNSVGCommonRenderableProps  &renderableProps) {
  RNS_LOG_INFO("Supported Properties count  :" << renderableProps.propList.size() << " : for SVG TAG: "<< (int)tag());
  RNS_LOG_INFO("##################");
  for (auto props : renderableProps.propList ) {
    RNS_LOG_ERROR(props);
  }
  RNS_LOG_INFO("##################");
  
    //set Fill Properties if specified.Else set to inherit from parent's Props
  if(std::find (renderableProps.propList.begin(), renderableProps.propList.end(), "fill") != renderableProps.propList.end()) {
    setColorFromColorStruct(renderableProps.fill,SkSVGAttribute::kFill);
  } else {
    setPaintAttribute(SkSVGAttribute::kFill,"inherit");
  }

  if(std::find (renderableProps.propList.begin(), renderableProps.propList.end(), "fillOpacity") != renderableProps.propList.end()) {
    setNumberAttribute( SkSVGAttribute::kFillOpacity,std::to_string(renderableProps.fillOpacity).c_str());
  }

  if(std::find (renderableProps.propList.begin(), renderableProps.propList.end(), "fillRule") != renderableProps.propList.end()) {
    setFillRuleAttribute(SkSVGAttribute::kFillRule,(renderableProps.fillRule == 0 ) ? "evenodd" :"nonzero");
  } else {
     setFillRuleAttribute(SkSVGAttribute::kFillRule,"inherit");
  }

  //set Stroke Properties if specified.If NOt set to Inherit from Parent's Props.
  if(std::find (renderableProps.propList.begin(), renderableProps.propList.end(), "stroke") != renderableProps.propList.end()) {
    setColorFromColorStruct(renderableProps.stroke,SkSVGAttribute::kStroke);
  } else {
    setPaintAttribute(SkSVGAttribute::kStroke,"inherit");
  }

  if(std::find (renderableProps.propList.begin(), renderableProps.propList.end(), "strokeOpacity") != renderableProps.propList.end()) {
    setNumberAttribute( SkSVGAttribute::kStrokeOpacity,std::to_string(renderableProps.strokeOpacity).c_str());
  }

  if(std::find (renderableProps.propList.begin(), renderableProps.propList.end(), "strokeWidth") != renderableProps.propList.end()) {
    setLengthAttribute( SkSVGAttribute::kStrokeWidth,renderableProps.strokeWidth.c_str());
  }

  if(std::find (renderableProps.propList.begin(), renderableProps.propList.end(), "strokeLinecap") != renderableProps.propList.end()) {
    setLineCapAttribute(SkSVGAttribute::kStrokeLineCap,(renderableProps.strokeLinecap == 0 ) ? "butt" :
                                                              ((renderableProps.strokeLinecap == 1 ) ? "round":"square"));
  } else {
    setLineCapAttribute(SkSVGAttribute::kStrokeLineCap,"inherit" );
  }

  if(std::find (renderableProps.propList.begin(), renderableProps.propList.end(), "strokeLinejoin") != renderableProps.propList.end()) {
    setLineJoinAttribute(SkSVGAttribute::kStrokeLineJoin,(renderableProps.strokeLinejoin == 0 ) ? "miter" :
                                                              ((renderableProps.strokeLinejoin == 1 ) ? "round":"bevel"));
  } else {
    setLineJoinAttribute(SkSVGAttribute::kStrokeLineJoin,"inherit" );
  }

  if(std::find (renderableProps.propList.begin(), renderableProps.propList.end(), "strokeDasharray") != renderableProps.propList.end()) {
    setDashArrayAttribute(SkSVGAttribute::kStrokeDashArray,renderableProps.strokeDasharray);
  } 

  if(std::find (renderableProps.propList.begin(), renderableProps.propList.end(), "strokeDashoffset") != renderableProps.propList.end()) {
    setLengthAttribute(SkSVGAttribute::kStrokeDashOffset,std::to_string(renderableProps.strokeDashoffset).c_str());
  }

  if(std::find (renderableProps.propList.begin(), renderableProps.propList.end(), "strokeMiterlimit") != renderableProps.propList.end()) {
    setNumberAttribute( SkSVGAttribute::kStrokeMiterLimit,std::to_string(renderableProps.strokeMiterlimit).c_str());
  }

  if(std::find (renderableProps.propList.begin(), renderableProps.propList.end(), "vectorEffect") != renderableProps.propList.end()) {
  //TODO : Vector EFFECT
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
  RNS_LOG_TODO("To Be Handled");
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

bool RSkSVGNode::setPaintAttribute(SkSVGAttribute attr, const char* stringValue) {
  SkSVGPaint paint;
  SkSVGAttributeParser parser(stringValue);
  if (!parser.parsePaint(&paint)) {
    return false;
  }
  setAttribute(attr, SkSVGPaintValue(paint));
  return true;
}

bool RSkSVGNode::setColorAttribute(SkSVGAttribute attr, const char* stringValue) {
  SkSVGColorType color;
  SkSVGAttributeParser parser(stringValue);
  if (!parser.parseColor(&color)) {
    return false;
  }
  setAttribute(attr, SkSVGColorValue(color));
  return true;
}

bool RSkSVGNode::setIRIAttribute(SkSVGAttribute attr, const char* stringValue) {
  SkSVGStringType iri;
  SkSVGAttributeParser parser(stringValue);
  if (!parser.parseIRI(&iri)) {
    return false;
  }
  setAttribute(attr, SkSVGStringValue(iri));
  return true;
}

bool RSkSVGNode::setClipPathAttribute(SkSVGAttribute attr, const char* stringValue) {
  SkSVGClip clip;
  SkSVGAttributeParser parser(stringValue);
  if (!parser.parseClipPath(&clip)) {
    return false;
  }
  setAttribute(attr, SkSVGClipValue(clip));
  return true;
}

bool RSkSVGNode::setPathDataAttribute(SkSVGAttribute attr, const char* stringValue) {
  SkPath path;
  if (!SkParsePath::FromSVGString(stringValue, &path)) {
    return false;
  }
  setAttribute(attr, SkSVGPathValue(path));
  return true;
}

bool RSkSVGNode::setStringAttribute(SkSVGAttribute attr, const char* stringValue) {
  SkString str(stringValue, strlen(stringValue));
  SkSVGStringType strType = SkSVGStringType(str);
  setAttribute(attr, SkSVGStringValue(strType));
  return true;
}

bool RSkSVGNode::setLengthAttribute(SkSVGAttribute attr, const char* stringValue) {
  SkSVGLength length;
  SkSVGAttributeParser parser(stringValue);
  if (!parser.parseLength(&length)) {
    return false;
  }
  setAttribute(attr, SkSVGLengthValue(length));
  return true;
}

bool RSkSVGNode::setNumberAttribute(SkSVGAttribute attr, const char* stringValue) {
  SkSVGNumberType number;
  SkSVGAttributeParser parser(stringValue);
  if (!parser.parseNumber(&number)) {
    return false;
  }
  setAttribute(attr, SkSVGNumberValue(number));
  return true;
}

bool RSkSVGNode::setViewBoxAttribute(SkSVGAttribute attr, const char* stringValue) {
  SkSVGViewBoxType viewBox;
  SkSVGAttributeParser parser(stringValue);
  if (!parser.parseViewBox(&viewBox)) {
    return false;
  }
  setAttribute(attr, SkSVGViewBoxValue(viewBox));
  return true;
}

bool RSkSVGNode::setLineCapAttribute(SkSVGAttribute attr, const char* stringValue) {
  SkSVGLineCap lineCap;
  SkSVGAttributeParser parser(stringValue);
  if (!parser.parseLineCap(&lineCap)) {
    return false;
  }
  setAttribute(attr, SkSVGLineCapValue(lineCap));
  return true;
}

bool RSkSVGNode::setLineJoinAttribute(SkSVGAttribute attr, const char* stringValue) {
  SkSVGLineJoin lineJoin;
  SkSVGAttributeParser parser(stringValue);
  if (!parser.parseLineJoin(&lineJoin)) {
    return false;
  }
  setAttribute(attr, SkSVGLineJoinValue(lineJoin));
  return true;
}

bool RSkSVGNode::setSpreadMethodAttribute(SkSVGAttribute attr,  const char* stringValue) {
  SkSVGSpreadMethod spread;
  SkSVGAttributeParser parser(stringValue);
  if (!parser.parseSpreadMethod(&spread)) {
    return false;
  }
  setAttribute(attr, SkSVGSpreadMethodValue(spread));
  return true;
}

bool RSkSVGNode::setStopColorAttribute(SkSVGAttribute attr, const char* stringValue) {
  SkSVGStopColor stopColor;
  SkSVGAttributeParser parser(stringValue);
  if (!parser.parseStopColor(&stopColor)) {
    return false;
  }
  setAttribute(attr, SkSVGStopColorValue(stopColor));
  return true;
}

bool RSkSVGNode::setPointsAttribute(SkSVGAttribute attr, const char* stringValue) {
  SkSVGPointsType points;
  SkSVGAttributeParser parser(stringValue);
  if (!parser.parsePoints(&points)) {
    return false;
  }
  setAttribute(attr, SkSVGPointsValue(points));
  return true;
}

bool RSkSVGNode::setFillRuleAttribute(SkSVGAttribute attr, const char* stringValue) {
  SkSVGFillRule fillRule;
  SkSVGAttributeParser parser(stringValue);
  if (!parser.parseFillRule(&fillRule)) {
    return false;
  }
  setAttribute(attr, SkSVGFillRuleValue(fillRule));
  return true;
}

bool RSkSVGNode::setVisibilityAttribute(SkSVGAttribute attr, const char* stringValue) {
  SkSVGVisibility visibility;
  SkSVGAttributeParser parser(stringValue);
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
    RNS_LOG_INFO("has strokeDasharray value: "<<value.c_str());
    dashArray.append(value);
    dashArray.append(" ");
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
    RNS_LOG_INFO(" Matrix 0 : "<<matrix[0]);
    RNS_LOG_INFO(" Matrix 1 : "<<matrix[1]);
    RNS_LOG_INFO(" Matrix 2 : "<<matrix[2]);
    RNS_LOG_INFO(" Matrix 3 : "<<matrix[3]);
    RNS_LOG_INFO(" Matrix 4 : "<<matrix[4]);
    RNS_LOG_INFO(" Matrix 5 : "<<matrix[5]);

    SkMatrix svgTransforMatrix=SkMatrix::Translate(matrix[4],matrix[5]);
    svgTransforMatrix.preConcat(SkMatrix::Scale(matrix[0],matrix[3]));
    setAttribute(attr,SkSVGTransformValue(svgTransforMatrix));

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

SkPath RSkSVGNode::onAsPath(const SkSVGRenderContext&)  const  { 
  SkPath path;
  RNS_LOG_TODO("TO BE IMPLEMENTED IN CONTAINER & EACH COMPONENT");
  return path;
};

void RSkSVGNode::appendChild(sk_sp<SkSVGNode>) {
  // Override from SKSVG Engine is Deprecated. 
  // Will use MountChildComponent to AppendChild from RSKSVGContainer Module
}

} // namespace react
} // namespace facebook
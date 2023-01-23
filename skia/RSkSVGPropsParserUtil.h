#pragma once

#include <map>
#include <string>


#include "experimental/svg/model/SkSVGAttribute.h"
#include "RSkSVGNode.h"

template <typename T>
void updateCommonNodeProps(T props ,sk_sp<facebook::react::RSkSVGNode> Node){

  if(!Node ) return;

    Node->nodeName=props.name.c_str();
  
  RNS_LOG_INFO("Property Info");
  RNS_LOG_INFO("---------------");
  RNS_LOG_INFO("name :"<<Node->nodeName.c_str());
  RNS_LOG_INFO("Opacity : "<<props.opacity);
  RNS_LOG_INFO("clipRule : "<<props.clipRule);
  RNS_LOG_INFO("fillOpacity : "<<props.fillOpacity);
  RNS_LOG_INFO("has strokeDasharray: "<<props.strokeDasharray.empty());
  RNS_LOG_INFO("stroke.type : "<<props.stroke.type);
  RNS_LOG_INFO("props.fill.type :"<<props.fill.type);
  RNS_LOG_INFO("---------------");

  //set Opacity
  Node->setNumberAttribute(SkSVGAttribute::kOpacity,std::to_string(props.opacity).c_str());

  //set Fill Prroperties
  updateColorFromColorStruct(props.fill,SkSVGAttribute::kFill,Node);
  Node->setNumberAttribute( SkSVGAttribute::kFillOpacity,std::to_string(props.fillOpacity).c_str());
  Node->setFillRuleAttribute(SkSVGAttribute::kFillRule,(props.fillRule == 0 ) ? "evenodd" :"nonzero");

  //set Stroke Properties
  updateColorFromColorStruct(props.stroke,SkSVGAttribute::kStroke,Node);
  Node->setNumberAttribute( SkSVGAttribute::kStrokeOpacity,std::to_string(props.strokeOpacity).c_str());
  Node->setNumberAttribute( SkSVGAttribute::kStrokeOpacity,std::to_string(props.strokeOpacity).c_str());
  Node->setLengthAttribute( SkSVGAttribute::kStrokeWidth,props.strokeWidth.c_str());
  Node->setLineCapAttribute(SkSVGAttribute::kStrokeLineCap,(props.strokeLinecap == 0 ) ? "butt" :
                                                              ((props.strokeLinecap == 1 ) ? "round":"square"));
  Node->setLineJoinAttribute(SkSVGAttribute::kStrokeLineJoin,(props.strokeLinejoin == 0 ) ? "miter" :
                                                              ((props.strokeLinejoin == 1 ) ? "round":"bevel"));
  Node->setDashArrayAttribute(SkSVGAttribute::kStrokeDashArray,props.strokeDasharray);
  Node->setNumberAttribute(SkSVGAttribute::kStrokeDashOffset,std::to_string(props.strokeDashoffset).c_str());
  Node->setNumberAttribute( SkSVGAttribute::kStrokeMiterLimit,std::to_string(props.strokeMiterlimit).c_str()); 

  //set Transform
  Node->setTransformAttribute(SkSVGAttribute::kTransform,props.matrix);

  //set clip properties
   Node->setFillRuleAttribute(SkSVGAttribute::kClipRule,(props.clipRule == 0 ) ? "evenodd" :"nonzero");
  //Node->setClipPathAttribute();   // SkSVGAttribute::kClipPath

}

template <typename T>
void updateColorFromColorStruct(T colorStruct,SkSVGAttribute attr,
                                sk_sp<facebook::react::RSkSVGNode> Node){

  if((colorStruct.type == 0) && colorStruct.payload) {

    auto colorValue = colorComponentsFromColor(colorStruct.payload);
    SkColor strokeColor= SkColorSetARGB(colorValue.alpha * 255.99,colorValue.red * 255.99,colorValue.green * 255.99,colorValue.blue * 255.99);
    SkSVGPaint paint(strokeColor);

    Node->setAttribute(attr,SkSVGPaintValue(paint));

 } else if(colorStruct.type ==  2) { // currentColor
   Node->setPaintAttribute(attr,"currentColor");
 } else if(colorStruct.type == 3) { // context-fill
   RNS_LOG_TODO(" Support for color : context-fill , color struct type : " <<colorStruct.type);
 }else if(colorStruct.type == 4) { // context-stroke
   RNS_LOG_TODO(" Support for color : context-stroke , color struct type : " <<colorStruct.type);
 }else if(colorStruct.type == 1) { // brush ref
   RNS_LOG_TODO(" Support for color as brush Ref , color struct type : " <<colorStruct.type);
 }
}



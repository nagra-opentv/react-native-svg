/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <unordered_map>

#include "ReactSkia/utils/RnsLog.h"

#include "RSkComponentRNSVGLinearGradient.h"
#include "RSkComponentRNSVGSvgView.h"
#include "RSkSVGComponentNode.h"
#include "RSkSVGContainer.h"

#define ENABLE_NATIVE_PROPS_DEBUG

namespace facebook {
namespace react {

RSkSVGNode::RSkSVGNode(SkSVGTag tag) : INHERITED(tag) {};

void RSkSVGNode::setCommonRenderableProps(const RNSVGCommonRenderableProps  &renderableProps) {

#ifdef ENABLE_NATIVE_PROPS_DEBUG
  RNS_LOG_INFO("========== Common Renderable Props ==========");
  RSkComponent* componetNode=dynamic_cast<RSkSVGComponentNode *>(this);
  RNS_LOG_INFO("Supported Properties count  :" << renderableProps.propList.size() <<
               " : for component: "<< componetNode->getComponentData().componentName);
  for (auto props : renderableProps.propList ) {
    RNS_LOG_INFO(props);
  }
  RNS_LOG_INFO("=============================================");
#endif /*ENABLE_NATIVE_PROPS_DEBUG*/

  #define APPLY_FILL_COLOUR         [](RSkSVGNode *node,const RNSVGCommonRenderableProps  &renderableProps) \
                                      {node->setColorFromColorStruct((renderableProps).fill,SkSVGAttribute::kFill);}

  #define APPLY_STROKE_COLOUR       [](RSkSVGNode *node,const RNSVGCommonRenderableProps  &renderableProps) \
                                      {node->setColorFromColorStruct((renderableProps).stroke,SkSVGAttribute::kStroke);}

  #define APPLY_FILL_RULE           [](RSkSVGNode *node,const RNSVGCommonRenderableProps  &renderableProps) \
                                      {node->setFillRuleAttribute(SkSVGAttribute::kFillRule,(renderableProps.fillRule == 0 ) ? "evenodd" :"nonzero");}

  #define APPLY_FILL_OPACITY        [](RSkSVGNode *node,const RNSVGCommonRenderableProps  &renderableProps) \
                                      {node->setNumberAttribute( SkSVGAttribute::kFillOpacity,std::to_string(renderableProps.fillOpacity));}

  #define APPLY_STROKE_OPACITY      [](RSkSVGNode *node,const RNSVGCommonRenderableProps  &renderableProps) \
                                      {node->setNumberAttribute( SkSVGAttribute::kStrokeOpacity,std::to_string(renderableProps.strokeOpacity));}

  #define APPLY_STROKE_WIDTH        [](RSkSVGNode *node,const RNSVGCommonRenderableProps  &renderableProps) \
                                      {node->setLengthAttribute( SkSVGAttribute::kStrokeWidth,renderableProps.strokeWidth);}

  #define APPLY_STROKE_LINECAP      [](RSkSVGNode *node,const RNSVGCommonRenderableProps  &renderableProps) \
                                      {node->setLineCapAttribute(SkSVGAttribute::kStrokeLineCap,(renderableProps.strokeLinecap == 0 ) ? "butt" : \
                                          ((renderableProps.strokeLinecap == 1 ) ? "round":"square"));}

  #define APPLY_STROKE_LINEJOIN     [](RSkSVGNode *node,const RNSVGCommonRenderableProps  &renderableProps) \
                                      {node->setLineJoinAttribute(SkSVGAttribute::kStrokeLineJoin,(renderableProps.strokeLinejoin == 0 ) ? "miter" : \
                                          ((renderableProps.strokeLinejoin == 1 ) ? "round":"bevel"));}

  #define APPLY_STROKE_DASHARRAY    [](RSkSVGNode *node,const RNSVGCommonRenderableProps  &renderableProps) \
                                      {node->setDashArrayAttribute(SkSVGAttribute::kStrokeDashArray,renderableProps.strokeDasharray);}

  #define APPLY_STROKE_DASHOFFSET   [](RSkSVGNode *node,const RNSVGCommonRenderableProps  &renderableProps) \
                                      {node->setLengthAttribute(SkSVGAttribute::kStrokeDashOffset,std::to_string(renderableProps.strokeDashoffset));}

  #define APPLY_STROKE_MITERLIMIT   [](RSkSVGNode *node,const RNSVGCommonRenderableProps  &renderableProps) \
                                      {node->setNumberAttribute( SkSVGAttribute::kStrokeMiterLimit,std::to_string(renderableProps.strokeMiterlimit));}

  #define APPLY_VECTOR_EFFECT      [](RSkSVGNode *node,const RNSVGCommonRenderableProps  &renderableProps) \
                                     {/*TODO*/}

  static std::unordered_map<std::string, std::function<void(RSkSVGNode *node,const RNSVGCommonRenderableProps)>> s_propUpdateFunctionMap={
    {"fill",APPLY_FILL_COLOUR},
    {"stroke",APPLY_STROKE_COLOUR},
    {"fillOpacity",APPLY_FILL_OPACITY},
    {"strokeOpacity",APPLY_STROKE_OPACITY},
    {"fillRule",APPLY_FILL_RULE},
    {"strokeWidth",APPLY_STROKE_WIDTH},
    {"strokeLinecap",APPLY_STROKE_LINECAP},
    {"strokeLinejoin",APPLY_STROKE_LINEJOIN},
    {"strokeDasharray",APPLY_STROKE_DASHARRAY},
    {"strokeDashoffset",APPLY_STROKE_DASHOFFSET},
    {"strokeMiterlimit",APPLY_STROKE_MITERLIMIT},
    {"vectorEffect",APPLY_VECTOR_EFFECT}
  };

  for (auto &item : renderableProps.propList) {
    //Fill Props
    if(s_propUpdateFunctionMap.count(item) ) {
      s_propUpdateFunctionMap[item](this,renderableProps);
    } else {
      RNS_LOG_WARN(" Unknown Property : "<<item);
    }
  }
  renderablePropList=renderableProps.propList;
}

void RSkSVGNode::setCommonNodeProps(const RNSVGCommonNodeProps &nodeProps){

  svgNodeId=nodeProps.name;
  //set Opacity
  setNumberAttribute(SkSVGAttribute::kOpacity,std::to_string(nodeProps.opacity).c_str());
  //set Transform
  setTransformAttribute(SkSVGAttribute::kTransform,nodeProps.matrix);
  //set clip properties :: TODO -- check the inheritence behavour for clip Props
  setFillRuleAttribute(SkSVGAttribute::kClipRule,(nodeProps.clipRule == 0 ) ? "evenodd" :"nonzero");
  setClipPathAttribute(SkSVGAttribute::kClipPath,nodeProps.clipPath.c_str());
}

void RSkSVGNode::setCommonGroupProps(const RNSVGGroupCommonrops &commonGroupProps) {

  #define RNS_SVG_SET_TEXT_FONT_ATTR(attr,value)                                 \
    if(!value.empty()) {                                                 \
     setStringAttribute(attr,value);                                     \
    }

  setLengthAttribute(SkSVGAttribute::kFontSize,commonGroupProps.font.fontSize);
  setLengthAttribute(static_cast<SkSVGAttribute>(RSkSVGAttribute::kLetterSpacing),commonGroupProps.font.letterSpacing);
  setLengthAttribute(static_cast<SkSVGAttribute>(RSkSVGAttribute::kWordSpacing),commonGroupProps.font.wordSpacing);

  RNS_SVG_SET_TEXT_FONT_ATTR(SkSVGAttribute::kFontFamily,commonGroupProps.font.fontFamily)
  RNS_SVG_SET_TEXT_FONT_ATTR(SkSVGAttribute::kFontStyle,commonGroupProps.font.fontStyle)
  RNS_SVG_SET_TEXT_FONT_ATTR(SkSVGAttribute::kFontWeight,commonGroupProps.font.fontWeight)
  RNS_SVG_SET_TEXT_FONT_ATTR(static_cast<SkSVGAttribute>(RSkSVGAttribute::kFontStretch),commonGroupProps.font.fontStretch)
  RNS_SVG_SET_TEXT_FONT_ATTR(static_cast<SkSVGAttribute>(RSkSVGAttribute::kTextDecoration),commonGroupProps.font.textDecoration)
  RNS_SVG_SET_TEXT_FONT_ATTR(SkSVGAttribute::kTextAnchor,commonGroupProps.font.textAnchor)

  #ifdef ENABLE_NATIVE_PROPS_DEBUG
    RNS_LOG_INFO("\n" <<
                 "=== Common Text Props ==="<< "\n" <<
                 "FontSize     : "<<commonGroupProps.font.fontSize << "\n" <<
                 "FontStyle    : "<<commonGroupProps.font.fontStyle << "\n" <<
                 "FontWeight   : "<<commonGroupProps.font.fontWeight << "\n" <<
                 "fontFamily   : "<<commonGroupProps.font.fontFamily << "\n" <<
                 "FontStretch  : "<<commonGroupProps.font.fontStretch << "\n" <<
                 "textAnchor   : "<<commonGroupProps.font.textAnchor << "\n" <<
                 "LetterSpacing: "<<commonGroupProps.font.letterSpacing << "\n" <<
                 "WordSpacing  : "<<commonGroupProps.font.wordSpacing<< "\n" <<
                 "========================");
  #endif /*ENABLE_NATIVE_PROPS_DEBUG*/
}

void RSkSVGNode::setColorFromColorStruct(RNSVGColorFillStruct  colorStruct,SkSVGAttribute attr){

  #ifdef ENABLE_NATIVE_PROPS_DEBUG
  RNS_LOG_INFO(" Color for prop : "<< ((attr == SkSVGAttribute::kFill) ? "Fill" : "Stroke" ) << "\n" <<
               " Color Type : "<<colorStruct.type <<
               " SharedColor: "<<colorStruct.payload <<
               " Brush Ref : "<<colorStruct.brushRef);
  #endif/*ENABLE_NATIVE_PROPS_DEBUG*/

  if(colorStruct.type == RNSVGColorType::SOLID)  {
    if(colorStruct.payload) {
      SkColor color= RSkColorFromSharedColor(colorStruct.payload, SK_ColorTRANSPARENT);
      SkSVGPaint paint(color);
      setAttribute(attr,SkSVGPaintValue(paint));
    } else {
      // Color specified as none
      setPaintAttribute(attr,"none");
    }
 } else if(colorStruct.type ==  RNSVGColorType::CURRENT_COLOR) {
   setPaintAttribute(attr,"currentColor");
 } else if(colorStruct.type == RNSVGColorType::BRUSH_REF) {
    (attr == SkSVGAttribute::kFill) ? (fillColor=colorStruct) : (strokeColor=colorStruct);
 } else if(colorStruct.type == RNSVGColorType::CONTEXT_FILL) {
   RNS_LOG_TODO(" Support for color : context-fill , color struct type : " <<colorStruct.type);
 } else if(colorStruct.type == RNSVGColorType::CONTEXT_STROKE) {
   RNS_LOG_TODO(" Support for color : context-stroke , color struct type : " <<colorStruct.type);
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

#ifdef ENABLE_NATIVE_PROPS_DEBUG
    RNS_LOG_INFO("\n"<<
                  " Matrix 0 : "<<matrix[0] << "\n" <<
                  " Matrix 1 : "<<matrix[1] << "\n" <<
                  " Matrix 2 : "<<matrix[2] << "\n" <<
                  " Matrix 3 : "<<matrix[3] << "\n" <<
                  " Matrix 4 : "<<matrix[4] << "\n" <<
                  " Matrix 5 : "<<matrix[5]);
#endif/*ENABLE_NATIVE_PROPS_DEBUG*/

    SkMatrix svgTransforMatrix;
    // Converting received Matrix from React Native framework which is in column major Order to row Major Order for SKia
    svgTransforMatrix[SkMatrix::kMScaleX] = matrix[0];  //horizontal scale factor
    svgTransforMatrix[SkMatrix::kMSkewY]  = matrix[1];  // vertical skew factor
    svgTransforMatrix[SkMatrix::kMSkewX]  = matrix[2];  //horizontal skew factor
    svgTransforMatrix[SkMatrix::kMScaleY] = matrix[3];  //vertical scale factor
    svgTransforMatrix[SkMatrix::kMTransX] = matrix[4];  //horizontal translation
    svgTransforMatrix[SkMatrix::kMTransY] = matrix[5];  // vertical translation

    setAttribute(attr,SkSVGTransformValue(svgTransforMatrix));
    return true;
  }
  return false;
}

void RSkSVGNode::setRootNode(RSkSVGNode * rootNode) {
  if(rootNode && (rootNode->tag() == SkSVGTag::kSvg)) {
    rootNode_=rootNode;
  } 
}

SkSize RSkSVGNode::getContainerSize() const {
  if( rootNode_ && (rootNode_->tag() == SkSVGTag::kSvg)) {
    auto node=dynamic_cast<RSkComponentRNSVGSvgView *>(rootNode_);
    if(node) {
      return node->getContainerSize();
    }
  }
  return SkSize::Make(0, 0);
}

void RSkSVGNode::applyShader(SkPaint* paint,std::string brushRef,const SkSVGRenderContext& ctx) const{
  if(rootNode_) {
    auto rootSvgContainerNode=static_cast<RSkComponentRNSVGSvgView *>(rootNode_);
    if(rootSvgContainerNode) {
       RSkSVGNode**  nodeRef = rootSvgContainerNode->rskNodeIDMapper.find(SkString(brushRef));
      if (nodeRef && (*nodeRef) && ((*nodeRef)->tag() == SkSVGTag::kLinearGradient)) {
        auto linearGradientNode=dynamic_cast<RSkComponentRNSVGLinearGradient *>(*nodeRef);
        if(linearGradientNode) {
          paint->setShader(linearGradientNode->getShader(ctx));
        }
      } else {
        RNS_LOG_ERROR(" Provided Invalid Svg Element as a brushRef : "<<brushRef);
      }
    }
  }
}

void RSkSVGNode::invalidateLayer(){
  if(rootNode_) {
    auto rootSvgContainerNode=static_cast<RSkComponentRNSVGSvgView *>(rootNode_);
    if(rootSvgContainerNode) {
     //  rootSvgContainerNode->layer()->invalidate(RnsShell::LayerInvalidateAll);
       rootSvgContainerNode->drawAndSubmit(RnsShell::LayerInvalidateAll);
    }
  }
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

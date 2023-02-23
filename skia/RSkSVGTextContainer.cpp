
/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "RSkSVGTextContainer.h"

namespace facebook {
namespace react {

RSkSVGTextContainer::RSkSVGTextContainer(const ShadowView &shadowView,
                                         RnsShell::LayerType layerType,
                                         SkSVGTag tag)
    : INHERITED(shadowView,layerType,tag) {
//TODO: To improve performance, Good to have single FontCollection & use it across all the TextContainers.
  fontCollection_ = sk_make_sp<skia::textlayout::FontCollection>();
  fontCollection_->setDefaultFontManager(SkFontMgr::RefDefault());
}

void RSkSVGTextContainer::mountChildComponent(
    std::shared_ptr<RSkComponent> childComponent,
    const int index) {

  RNS_LOG_DEBUG("Parent Componet :" << this->getComponentData().componentName<<" holding child :" << childComponent->getComponentData().componentName);

  if(!childComponent || !childComponent.get()) {
    RNS_LOG_ERROR("Invalid child component received");
    return;
  }
  auto node=static_cast<RSkSVGTextContainer *>(childComponent.get());
  if (node) { 
    node->setTextParent(this);
  }
  INHERITED::mountChildComponent(childComponent,index);
}

void  RSkSVGTextContainer::updateCommonTextProps(SharedProps newViewProps) {

  auto const &newRNSVGTextPropsProps = *std::static_pointer_cast<RNSVGTextProps const>(newViewProps);

  setCommonRenderableProps(newRNSVGTextPropsProps);
  setCommonNodeProps(newRNSVGTextPropsProps);
  setCommonGroupProps(newRNSVGTextPropsProps);

#define SET_TEXT_FRAME_ATTR(attr,vectorValue,index)                      \
  if(vectorValue.size() && (index < vectorValue.size() )) {             \
    setLengthAttribute(attr,vectorValue[index]);                         \
  }

// The vector's first element (Vec[0]) specifies the dimensions for the entire text,
// while subsequent elements specify the dimensions for each individual character.
// At present, the placement of the text as a whole is being considered.

  SET_TEXT_FRAME_ATTR(SkSVGAttribute::kX,newRNSVGTextPropsProps.x,0)
  SET_TEXT_FRAME_ATTR(SkSVGAttribute::kY,newRNSVGTextPropsProps.y,0)
  SET_TEXT_FRAME_ATTR(static_cast<SkSVGAttribute>(RSkSVGAttribute::kDX),newRNSVGTextPropsProps.dx,0)
  SET_TEXT_FRAME_ATTR(static_cast<SkSVGAttribute>(RSkSVGAttribute::kDY),newRNSVGTextPropsProps.dy,0)

#ifdef ENABLE_RNSVG_TEXT_NATIVE_PROPS_DEBUG
  RNS_LOG_INFO("========== TEXT Geometry Props ==========");
  for(auto value:newRNSVGTextPropsProps.x)
    RNS_LOG_INFO("x"<<value);
  for(auto value:newRNSVGTextPropsProps.y)
    RNS_LOG_INFO("y"<<value);
  for(auto value:newRNSVGTextPropsProps.dx)
    RNS_LOG_INFO("dx"<<value);
  for(auto value:newRNSVGTextPropsProps.dy)
    RNS_LOG_INFO("dy"<<value);
  RNS_LOG_INFO("========================================");
#endif /*ENABLE_RNSVG_TEXT_NATIVE_PROPS_DEBUG*/
}

TextStyle RSkSVGTextContainer::getContentTextStyle() const {
  TextStyle textStyle;
  SkSVGLength fontSize,letterSpacing,wordSpacing;
  SkString fontFamily;

  //TODO: To Avoid querring Props on each render, Maintain  & Use Inherited Props Info.

  if(getFontFamily(fontFamily)) {
    textStyle.setFontFamilies({fontFamily});
  }
  if(getFontSize(fontSize)) {
    textStyle.setFontSize(fontSize.value());
  }
  if(getLetterSpacing(letterSpacing)) {
    textStyle.setLetterSpacing(letterSpacing.value());
  }
  if(getWordSpacing(wordSpacing)) {
    textStyle.setWordSpacing(wordSpacing.value());
  }
  return textStyle;
}

SkPoint RSkSVGTextContainer::getContentDrawCoOrdinates() const{
  bool findAttrY{true}; // There is a possibility attrY found as part search for attrX
  SkScalar positionX{0},positionY{0},deltaX{0},deltaY{0};
  std::vector<SkScalar> attrVec;
  //Get Position X
  if(getPositionX(attrVec)) {
    positionX =attrVec[0];
    if(attrVec.size() == 2) {
      positionY =attrVec[1];
      findAttrY=false;
    }
  }
  //Get Position Y
  if(PositionYHasValue()) {
    positionY =getPositionY().value();
  } else if(findAttrY && getPositionY(attrVec)) {
    positionY =attrVec[attrVec.size()-1 ];
  }
  // get dx & dy
  if(getDeltaX(deltaX)) {
    positionX += deltaX;
  }
  if(getDeltaY(deltaY)) {
    positionY += deltaY;
  }
  RNS_LOG_DEBUG(" positionX :[ "<<positionX <<
                " ] positionY :[ "<<positionY <<
                " ]");

  return {positionX,positionY};
}

void RSkSVGTextContainer::updateContainerContentBounds(SkRect frame) const{
  contentBounds_.push_back(frame);//Add to it's own container bound list
  // Add to it's parent container bound list
  auto node=static_cast<RSkSVGTextContainer *>(textParentNode_);
  if(node) {
    node->updateContainerContentBounds(frame);
  }
}

void RSkSVGTextContainer::setTextParent(RSkSVGNode * textParentNode) {
  if(!textParentNode) return;

  textParentNode_=textParentNode;
}

void RSkSVGTextContainer::onSetAttribute(SkSVGAttribute attr, const SkSVGValue& attrValue) {
  switch (attr) {
    case SkSVGAttribute::kX:
      if (const auto* x = attrValue.as<SkSVGLengthValue>()) {
        setPositionX(*x);
      }
      break;
    case SkSVGAttribute::kY:
      if (const auto* y = attrValue.as<SkSVGLengthValue>()) {
        setPositionY(*y);
      }
      break;
    case SkSVGAttribute::kFontFamily:
      if (const auto* font_family = attrValue.as<SkSVGStringValue>()) {
        setFontFamily(*font_family);
      }
      break;
    case SkSVGAttribute::kFontSize:
      if (const auto* font_size = attrValue.as<SkSVGLengthValue>()) {
        setFontSize(*font_size);
      }
      break;
      case SkSVGAttribute::kTextAnchor:
        if (const auto* text_anchor = attrValue.as<SkSVGStringValue>()) {
          setTextAnchor(*text_anchor);
        }
      break;
    default:
      onSetRSkSVGAttribute(static_cast<RSkSVGAttribute>(attr),attrValue);
  }
}

void RSkSVGTextContainer::onSetRSkSVGAttribute(RSkSVGAttribute attr, const SkSVGValue& attrValue) {
  switch (attr) {
    case RSkSVGAttribute::kDX:
      if (const auto* dx = attrValue.as<SkSVGLengthValue>()) {
        setDeltaX(*dx);
      }
      break;
    case RSkSVGAttribute::kDY:
      if (const auto* dy = attrValue.as<SkSVGLengthValue>()) {
        setDeltaY(*dy);
      }
      break;
    case RSkSVGAttribute::kLetterSpacing:
      if (const auto*letter_spacing = attrValue.as<SkSVGLengthValue>()) {
        setLetterSpacing(*letter_spacing);
      }
      break;
    case RSkSVGAttribute::kWordSpacing:
      if (const auto* word_spacing = attrValue.as<SkSVGLengthValue>()) {
        setWordSpacing(*word_spacing);
      }
      break;
    default:
      this->INHERITED::onSetAttribute(static_cast<SkSVGAttribute>(attr), attrValue);
  }
}

} // namespace react
} // namespace facebook

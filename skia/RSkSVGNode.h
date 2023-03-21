/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */
#pragma once

#include <string>

#include "experimental/svg/model/SkSVGAttribute.h"
#include "experimental/svg/model/SkSVGAttributeParser.h"
#include "experimental/svg/model/SkSVGRenderContext.h"
#include "experimental/svg/model/SkSVGTransformableNode.h"
#include "experimental/svg/model/SkSVGTypes.h"
#include "experimental/svg/model/SkSVGValue.h"
#include "include/core/SkColor.h"
#include "include/utils/SkParsePath.h"

#include "ReactSkia/views/common/RSkConversion.h"

#include "react/renderer/components/rnsvg/RNSVGProps.h"

namespace facebook {
namespace react {

// SVG Attributes , which are not handled in SKSVG Engine
constexpr int RSkSVGAttrStart =(int)SkSVGAttribute::kUnknown +1;
enum RSkSVGAttribute {
  kDX =RSkSVGAttrStart,// DeltaX
  kDY, //DeltaY
  kLetterSpacing,
  kWordSpacing,
  kFontStretch,
  kTextDecoration
};

enum RNSVGColorStruct {
  SOLID,
  BRUSH_REF,
  CURRENT_COLOR,
  CONTEXT_FILL,
  CONTEXT_STROKE,
};

class RSkSVGNode : public SkSVGTransformableNode {

 public:

  ~RSkSVGNode() {}

  std::string svgNodeId;

  virtual void setRoot(RSkSVGNode * rootNode);
  virtual SkSize getContainerSize()const;
  void setColorFromColorStruct(RNSVGColorFillStruct  colorStruct,SkSVGAttribute attr);
  bool setNumberAttribute( SkSVGAttribute attr,std::string stringValue);
  bool setStringAttribute( SkSVGAttribute attr,std::string stringValue);
  bool setPaintAttribute( SkSVGAttribute attr,std::string stringValue);
  bool setColorAttribute( SkSVGAttribute attr,std::string stringValue);
  bool setLengthAttribute( SkSVGAttribute attr,std::string stringValue);
  bool setPathDataAttribute( SkSVGAttribute attr,std::string stringValue);
  bool setFillRuleAttribute( SkSVGAttribute attr,std::string stringValue);
  bool setLineCapAttribute( SkSVGAttribute attr,std::string stringValue);
  bool setLineJoinAttribute( SkSVGAttribute attr,std::string stringValue);
  bool setViewBoxAttribute( SkSVGAttribute attr,std::string stringValue);
  bool setIRIAttribute( SkSVGAttribute attr,std::string stringValue);
  bool setSpreadMethodAttribute( SkSVGAttribute attr,std::string stringValue);
  bool setStopColorAttribute( SkSVGAttribute attr,std::string stringValue);
  bool setPointsAttribute( SkSVGAttribute attr,std::string stringValue);
  bool setVisibilityAttribute( SkSVGAttribute attr,std::string stringValue);
  bool setClipPathAttribute( SkSVGAttribute attr,std::string stringValue);
  bool setTransformAttribute(SkSVGAttribute attr,const std::vector<Float> matrix);
  bool setDashArrayAttribute( SkSVGAttribute attr,const std::vector<std::string> dashArray);

 protected:

  RSkSVGNode * rootNode_{nullptr};
  std::string fillBrushRef;
  std::string strokeBrushRef;

  explicit RSkSVGNode(SkSVGTag tag);

  SkPath onAsPath(const SkSVGRenderContext&)  const override;
  void appendChild(sk_sp<SkSVGNode>)  override;

  void setCommonRenderableProps(const RNSVGCommonRenderableProps  &renderableProps);
  void setCommonNodeProps(const RNSVGCommonNodeProps &nodeProps);
  void setCommonGroupProps(const RNSVGGroupCommonrops &commonGroupProps);

 private :

  typedef SkSVGTransformableNode INHERITED;

};

} // namespace react
} // namespace facebook

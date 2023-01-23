#pragma once

#include <map>
#include <string>

#include "experimental/svg/model/SkSVGAttribute.h"
#include "experimental/svg/model/SkSVGRenderContext.h"
#include "experimental/svg/model/SkSVGValue.h"

#include "RSkSVGNode.h"

template <typename T>
void updateCommonNodeProps(T props ,sk_sp<facebook::react::RSkSVGNode> Node){

	if(!Node ) return;

    Node->nodeName=props.name.c_str();
	
	printf("\n Property Info : ");
	printf("\n ---------------");
	printf("\n name : [%s]",Node->nodeName.c_str());
	printf("\n Opacity : [%f]",props.opacity);
	printf("\n clipRule : [%d]",props.clipRule);
	printf("\n fillOpacity : [%g]",props.fillOpacity);
	printf("\n has strokeDasharray: [%d]",props.strokeDasharray.empty());
    printf("\n props.stroke.type :[%d]\n",props.stroke.type);
	printf("\n props.fill.type :[%d]\n",props.fill.type);
	printf("\n props.name [%s]\n",props.name.c_str());
	printf("\n Size of Matrix :: [%lu]\n",props.matrix.size());
    if(props.matrix.size() == 6) {
	printf("\n Matrix 0 : [%f]",props.matrix[0]);
	printf("\n Matrix 1 : [%f]",props.matrix[1]);
	printf("\n Matrix 2 : [%f]",props.matrix[2]);
	printf("\n Matrix 3 : [%f]",props.matrix[3]);
	printf("\n Matrix 4 : [%f]",props.matrix[4]);
	printf("\n Matrix 5 : [%f]",props.matrix[5]);

	SkMatrix svgTransforMatrix=SkMatrix::Translate(props.matrix[4],props.matrix[5]);
    svgTransforMatrix.preConcat(SkMatrix::Scale(props.matrix[0],props.matrix[3]));
	#if 0
	Node->svgTransforMatrix=SkMatrix::MakeAll(props.matrix[0],0,props.matrix[4],
	                         0,props.matrix[3],props.matrix[5],
							 0,0,0);
    #endif
    Node->setAttribute(SkSVGAttribute::kTransform,SkSVGTransformValue(svgTransforMatrix));
	printf("\n getScaleX [%f]\n",svgTransforMatrix.getScaleX());
	printf("\n getScaleY [%f]\n",svgTransforMatrix.getScaleY());
	printf("\n getTranslateX [%f]\n",svgTransforMatrix.getTranslateX());
	printf("\n getTranslateY [%f]\n",svgTransforMatrix.getTranslateY());
	printf("\n getSkewX [%f]\n",svgTransforMatrix.getSkewX());
	printf("\n getSkewY [%f]\n",svgTransforMatrix.getSkewY());
	}
	printf("\n ---------------");

Node->SetNumberAttribute(Node,SkSVGAttribute::kOpacity,std::to_string(props.opacity).c_str()); 
//Node->SetTransformAttribute();    //SkSVGAttribute::kTransform
//Node->SetClipPathAttribute();   // SkSVGAttribute::kClipPath
Node->SetFillRuleAttribute(Node,SkSVGAttribute::kClipRule,
						   (props.clipRule == 0 ) ? "evenodd" :"nonzero");

 if((props.stroke.type == 0) && props.stroke.payload) {

        auto colorValue = colorComponentsFromColor(props.stroke.payload);
        SkColor strokeColor= SkColorSetARGB(colorValue.alpha * 255.99,colorValue.red * 255.99,colorValue.green * 255.99,colorValue.blue * 255.99);
        SkSVGPaint paint(strokeColor);
        Node->setAttribute(SkSVGAttribute::kStroke,SkSVGPaintValue(paint));
 } else if(props.stroke.type ==  2) {
	 Node->SetPaintAttribute(Node,SkSVGAttribute::kStroke,"currentColor");
 }
  if((props.fill.type == 0) && props.fill.payload) {

        auto colorValue = colorComponentsFromColor(props.fill.payload);
        SkColor fillColor= SkColorSetARGB(colorValue.alpha * 255.99,colorValue.red * 255.99,colorValue.green * 255.99,colorValue.blue * 255.99);
        SkSVGPaint paint(fillColor);
        Node->setAttribute(SkSVGAttribute::kFill,SkSVGPaintValue(paint));
 } else if(props.fill.type ==  2) {
	 Node->SetPaintAttribute(Node,SkSVGAttribute::kFill,"currentColor");
 }

 Node->SetNumberAttribute(Node, SkSVGAttribute::kFillOpacity,std::to_string(props.fillOpacity).c_str());    //
 Node->SetFillRuleAttribute(Node,SkSVGAttribute::kFillRule,
 						        (props.fillRule == 0 ) ? "evenodd" :"nonzero");   //  
  Node->SetNumberAttribute(Node, SkSVGAttribute::kStrokeOpacity,std::to_string(props.strokeOpacity).c_str());       // 
  Node->SetLengthAttribute(Node, SkSVGAttribute::kStrokeWidth,props.strokeWidth.c_str());       // 
   Node->SetLineCapAttribute(Node,SkSVGAttribute::kStrokeLineCap,
						   (props.strokeLinecap == 0 ) ? "butt" :
						   ((props.strokeLinecap == 1 ) ? "round":"square"));      // 
 Node->SetLineJoinAttribute(Node,SkSVGAttribute::kStrokeLineJoin,
						   (props.strokeLinejoin == 0 ) ? "miter" :
						   ((props.strokeLinejoin == 1 ) ? "round":"bevel"));      // 
 if(!props.strokeDasharray.empty()) {
 	std::string strokeDashArray;
 	for(auto value : props.strokeDasharray) {
 		printf("\n has strokeDasharray value: [%s]",value.c_str());
 		strokeDashArray.append(value);
 		strokeDashArray.append(" ");
 	}
 	Node->SetDashArrayAttribute(Node,SkSVGAttribute::kStrokeDashArray,strokeDashArray.c_str());    // 
 }
 Node->SetNumberAttribute(Node,SkSVGAttribute::kStrokeDashOffset,std::to_string(props.strokeDashoffset).c_str());       // 

 Node->SetNumberAttribute(Node, SkSVGAttribute::kStrokeMiterLimit,std::to_string(props.strokeMiterlimit).c_str());       // 
 
}



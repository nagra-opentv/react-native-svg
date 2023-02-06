#########################################################################################################
In the future, files for integrating ReactNativeSVG with ReactNativeSkia will be automatically generated.
Until then, the required third-party modules and components must be manually added to the ReactNativeSkia source.
#########################################################################################################

To include ReactNatievSVG as part of ReactNativeSKia's Build:
-------------------------------------------------------------
Add ReactNatievSVG Build gn path as below in BUILD gn of ReactSkia/external/BUILD.gn

source_set("ReactSkiaExternal") {
  deps = [
    "//ReactSkia/external/react-native-svg/skia:Rnsvg"
  ]
}

To incorporate RNSSVGComponents from the third-party ReactNativeSVG:
--------------------------------------------------------------------

1.To add support for SVG elements, include the following mapping in the fabricComponentsClassMap map in file - 
    ReactSkia/RSkThirdPartyFabricComponentsProvider.cpp

    {"RNSVGSvgView",RSkComponentProviderRNSVGSvgViewCls},
    {"RNSVGGroup",RSkComponentProviderRNSVGGroupCls},
    {"RNSVGCircle",RSkComponentProviderRNSVGCircleCls},
    {"RNSVGRect",RSkComponentProviderRNSVGRectCls},
    {"RNSVGPath",RSkComponentProviderRNSVGPathCls},
    {"RNSVGEllipse",RSkComponentProviderRNSVGEllipseCls}, 
    {"RNSVGLine",RSkComponentProviderRNSVGLineCls},    
    {"RNSVGDefs",RSkComponentProviderRNSVGDefsCls}, 
    {"RNSVGUse",RSkComponentProviderRNSVGUseCls}

to add elemnts , add an entry in the following format
{RNSVGElementName,RSkComponentProviderRNSVGElemnet functionobject}

2. Add the Componentprovider function prototype in ReactSkia/RSkThirdPartyFabricComponentsProvider.h

RSkComponentProvider *RSkComponentProviderRNSVGSvgViewCls(); // RNSVGSVG
RSkComponentProvider *RSkComponentProviderRNSVGGroupCls(); // RNSVGG
RSkComponentProvider *RSkComponentProviderRNSVGCircleCls(); // RNSVGCircle
RSkComponentProvider *RSkComponentProviderRNSVGRectCls(); // RNSVGRect
RSkComponentProvider *RSkComponentProviderRNSVGPathCls(); // RNSVGPath
RSkComponentProvider *RSkComponentProviderRNSVGEllipseCls() ; // RNSVGEllipse
RSkComponentProvider *RSkComponentProviderRNSVGLineCls() ; // RNSVGLine
RSkComponentProvider *RSkComponentProviderRNSVGDefsCls(); // RNSVGDefs
RSkComponentProvider *RSkComponentProviderRNSVGUseCls(); // RNSVGUse

Follow the same pattern to extend the support for more SVG component.

To include RNSSVGModules from thirdParty ReactNativeSVG:
--------------------------------------------------------
Add below module entry in ReactSkia/RSkThirdPartyNativeModuleProvider.cpp

{"RNSVGRenderableModule",RNSVGRenderableModuleCls}

& it's declaration in ReactSkia/RSkThirdPartyNativeModuleProvider.h

xplat::module::CxxModule* RNSVGRenderableModuleCls(void) RNS_USED; // RNSVGRenderableModule 

To Add supported for SVG Elememts
---------------------------------

Add below in ReactSkia/LegacyNativeModules/uimanager/UiManagerModule.cpp

dynamic Uimanager::getConstantsForThirdpartyViewManager(std::string viewManagerName) {

  dynamic svgCommonNodeProps = folly::dynamic::object("name", true)("opacity", true)("matrix",true)(
        "mask", true)("markerStart",true)("markerMid",true)("markerEnd", true)(
        "clipPath", true)("clipRule", true)(
        "responsible",true)("display",true)("pointerEvents",true);

  dynamic svgCommonRenderableProps = folly::dynamic::object("fill", true)("fillOpacity",true)("fillRule",true)(
        "stroke", true)("strokeWidth", true)("style", true)(
        "strokeOpacity",true)("strokeLinecap",true)("strokeLinejoin",true)(
        "strokeDasharray",true)("strokeDashoffset",true)("strokeMiterlimit",true)(
        "vectorEffect",true)("propList",true);

  if(viewManagerName == "RNSVGSvgView") {
    auto nativeProps = folly::dynamic::object("bbWidth", true)("bbHeight", true)(
        "minX", true)("minY", true)("vbWidth", true)("vbHeight", true)("align", true)(
        "meetOrSlice",true)("color",true)("tintColor",true)("pointerEvents",true);

    auto bubblingEventTypes = folly::dynamic::object();
    auto directEventTypes = folly::dynamic::object();
    auto registry = folly::dynamic::object(
        NATIVE_PROPS_KEY, std::move(nativeProps))(+        BASE_MODULE_NAME_KEY, "RCTView")(
        BUBBLING_EVENTS_KEY, std::move(bubblingEventTypes))(
        DIRECT_EVENTS_KEY, std::move(directEventTypes));
    return {std::move(registry)};
  }else if(viewManagerName == "RNSVGGroup") {

    auto nativeProps = folly::dynamic::merge_diff(svgCommonNodeProps,svgCommonRenderableProps) ;

    auto bubblingEventTypes = folly::dynamic::object();
    auto directEventTypes = folly::dynamic::object();
    auto registry = folly::dynamic::object(
        NATIVE_PROPS_KEY, std::move(nativeProps))(+        BASE_MODULE_NAME_KEY, "RCTView")(
        BUBBLING_EVENTS_KEY, std::move(bubblingEventTypes))(
        DIRECT_EVENTS_KEY, std::move(directEventTypes));
    return {std::move(registry)};
  }else  if(viewManagerName == "RNSVGUse") {
    dynamic componentNativeProps = folly::dynamic::object(
         "href", true)("x", true)("y", true)("width", true)("height", true);

    auto nativeProps = folly::dynamic::merge_diff(svgCommonNodeProps,svgCommonRenderableProps) ;
    nativeProps = folly::dynamic::merge_diff(componentNativeProps,nativeProps) ;

    auto bubblingEventTypes = folly::dynamic::object();
    auto directEventTypes = folly::dynamic::object();
    auto registry = folly::dynamic::object(
        NATIVE_PROPS_KEY, std::move(nativeProps))(+        BASE_MODULE_NAME_KEY, "RCTView")(
        BUBBLING_EVENTS_KEY, std::move(bubblingEventTypes))(
        DIRECT_EVENTS_KEY, std::move(directEventTypes));
    return {std::move(registry)};
  }else if(viewManagerName == "RNSVGCircle") {

    dynamic componentNativeProps = folly::dynamic::object(
         "cx", true)("cy", true)("r", true);

    auto nativeProps = folly::dynamic::merge_diff(svgCommonNodeProps,svgCommonRenderableProps) ;
    nativeProps = folly::dynamic::merge_diff(componentNativeProps,nativeProps) ;

    auto bubblingEventTypes = folly::dynamic::object();
    auto directEventTypes = folly::dynamic::object();
    auto registry = folly::dynamic::object(
        NATIVE_PROPS_KEY, std::move(nativeProps))(+        BASE_MODULE_NAME_KEY, "RCTView")(
        BUBBLING_EVENTS_KEY, std::move(bubblingEventTypes))(
        DIRECT_EVENTS_KEY, std::move(directEventTypes));
    return {std::move(registry)};
  }
  else if(viewManagerName == "RNSVGRect") {

    dynamic componentNativeProps = folly::dynamic::object(
         "x", true)("y", true)("rx", true)("ry", true)("width", true)("height", true);

    auto nativeProps = folly::dynamic::merge_diff(svgCommonNodeProps,svgCommonRenderableProps) ;
    nativeProps = folly::dynamic::merge_diff(componentNativeProps,nativeProps) ;

    auto bubblingEventTypes = folly::dynamic::object();
    auto directEventTypes = folly::dynamic::object();
    auto registry = folly::dynamic::object(
        NATIVE_PROPS_KEY, std::move(nativeProps))(
        BASE_MODULE_NAME_KEY, "RCTView")(
        BUBBLING_EVENTS_KEY, std::move(bubblingEventTypes))(
       DIRECT_EVENTS_KEY, std::move(directEventTypes));
    return {std::move(registry)};
  }  else if(viewManagerName == "RNSVGPath") {

    dynamic componentNativeProps = folly::dynamic::object("d", true);

    auto nativeProps = folly::dynamic::merge_diff(svgCommonNodeProps,svgCommonRenderableProps) ;
    nativeProps = folly::dynamic::merge_diff(componentNativeProps,nativeProps) ;

    auto bubblingEventTypes = folly::dynamic::object();
    auto directEventTypes = folly::dynamic::object();
    auto registry = folly::dynamic::object(
        NATIVE_PROPS_KEY, std::move(nativeProps))(
        BASE_MODULE_NAME_KEY, "RCTView")(
        BUBBLING_EVENTS_KEY, std::move(bubblingEventTypes))(
       DIRECT_EVENTS_KEY, std::move(directEventTypes));
    return {std::move(registry)};
  } else if(viewManagerName == "RNSVGEllipse") {

    dynamic componentNativeProps = folly::dynamic::object(
         "cx", true)("cy", true)("rx", true)("ry", true);

    auto nativeProps = folly::dynamic::merge_diff(svgCommonNodeProps,svgCommonRenderableProps) ;
    nativeProps = folly::dynamic::merge_diff(componentNativeProps,nativeProps) ;

    auto bubblingEventTypes = folly::dynamic::object();
    auto directEventTypes = folly::dynamic::object();
    auto registry = folly::dynamic::object(
        NATIVE_PROPS_KEY, std::move(nativeProps))(
        BASE_MODULE_NAME_KEY, "RCTView")(
        BUBBLING_EVENTS_KEY, std::move(bubblingEventTypes))(
       DIRECT_EVENTS_KEY, std::move(directEventTypes));
    return {std::move(registry)};
  } else if(viewManagerName == "RNSVGLine") {

    dynamic componentNativeProps = folly::dynamic::object(
         "x1", true)("x2", true)("y1", true)("y2", true);

    auto nativeProps = folly::dynamic::merge_diff(svgCommonNodeProps,svgCommonRenderableProps) ;
    nativeProps = folly::dynamic::merge_diff(componentNativeProps,nativeProps) ;

    auto bubblingEventTypes = folly::dynamic::object();
    auto directEventTypes = folly::dynamic::object();
    auto registry = folly::dynamic::object(
        NATIVE_PROPS_KEY, std::move(nativeProps))(
        BASE_MODULE_NAME_KEY, "RCTView")(
        BUBBLING_EVENTS_KEY, std::move(bubblingEventTypes))(
       DIRECT_EVENTS_KEY, std::move(directEventTypes));
    return {std::move(registry)};
  } else {
  RNS_LOG_WARN("getConstantsForThirdpartyViewManager viewManagerName : " << viewManagerName << " not found");
}
  auto nativeProps = folly::dynamic::object();
  auto bubblingEventTypes = folly::dynamic::object();
  auto directEventTypes = folly::dynamic::object();
  auto registry = folly::dynamic::object(
      NATIVE_PROPS_KEY, std::move(nativeProps))(
      BASE_MODULE_NAME_KEY, "RCTView")(
      BUBBLING_EVENTS_KEY, std::move(bubblingEventTypes))(
      DIRECT_EVENTS_KEY, std::move(directEventTypes));
  return {std::move(registry)};
}

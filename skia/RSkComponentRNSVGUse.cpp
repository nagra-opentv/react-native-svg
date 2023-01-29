#include "RSkComponentRNSVGUse.h"
#include "experimental/svg/model/SkSVGRenderContext.h"
#include "experimental/svg/model/SkSVGValue.h"
#include "include/core/SkCanvas.h"

#include "react/renderer/components/rnsvg/RNSVGProps.h"

#include "RSkSVGPropsParserUtil.h"
#include "RSkSVGContainer.h"

namespace facebook {
namespace react {

RSkComponentRNSVGUse::RSkComponentRNSVGUse(const ShadowView &shadowView)
    : RSkComponent(shadowView,LAYER_TYPE_DEFAULT),
    INHERITED(SkSVGTag::kUse) {}

RnsShell::LayerInvalidateMask  RSkComponentRNSVGUse::updateComponentProps(SharedProps newViewProps,bool forceUpdate) {
  auto component = getComponentData();

  auto const &newRNSVGUseProps = *std::static_pointer_cast<RNSVGUseProps const>(newViewProps);
  
  RNS_LOG_INFO(" X: "<<newRNSVGUseProps.x);
  RNS_LOG_INFO(" Y: "<<newRNSVGUseProps.y);
  RNS_LOG_INFO(" Href: "<<newRNSVGUseProps.href.c_str());
  RNS_LOG_INFO(" Width: "<<newRNSVGUseProps.width);
  RNS_LOG_INFO(" Height: "<<newRNSVGUseProps.height);

  setLengthAttribute(SkSVGAttribute::kX,newRNSVGUseProps.x.c_str());
  setLengthAttribute(SkSVGAttribute::kY,newRNSVGUseProps.y.c_str());
  setAttribute(SkSVGAttribute::kHref,SkSVGStringValue(SkString(newRNSVGUseProps.href.c_str())));
  setLengthAttribute(SkSVGAttribute::kWidth,newRNSVGUseProps.width.c_str());
  setLengthAttribute(SkSVGAttribute::kHeight,newRNSVGUseProps.height.c_str());
  
  updateCommonNodeProps(newRNSVGUseProps,this);

   return RnsShell::LayerInvalidateNone;
}

void RSkComponentRNSVGUse::mountChildComponent(
    std::shared_ptr<RSkComponent> newChildComponent,
    const int index) {
  RNS_LOG_INFO("cannot append child nodes to an SVG shape.\n");
}

void RSkComponentRNSVGUse::onSetAttribute(SkSVGAttribute attr, const SkSVGValue& v) {
    switch (attr) {
    case SkSVGAttribute::kHref:
        if (const auto* href = v.as<SkSVGStringValue>()) {
            href_ = *href;
        }
        break;
    case SkSVGAttribute::kX:
        if (const auto* x = v.as<SkSVGLengthValue>()) {
            x_ = *x;
        }
        break;
    case SkSVGAttribute::kY:
        if (const auto* y = v.as<SkSVGLengthValue>()) {
            y_ = *y;
        }
        break;
    default:
        this->INHERITED::onSetAttribute(attr, v);
    }
}

bool RSkComponentRNSVGUse::onPrepareToRender(SkSVGRenderContext* ctx) const {

    RNS_LOG_INFO("---onPrepareToRender For Use Component--- : "<<href_.c_str());

    if (href_.isEmpty() || !INHERITED::onPrepareToRender(ctx)) {
        return false;
    }

    if (x_.value() || y_.value()) {
        // Restored when the local SkSVGRenderContext leaves scope.
        ctx->saveOnce();
        ctx->canvas()->translate(x_.value(), y_.value());
    }
    RNS_LOG_INFO("---onPrepareToRender For Use Component--- : "<<href_.c_str());

    return true;
}

void RSkComponentRNSVGUse::onRender(const SkSVGRenderContext& ctx) const {

    const auto ref = ctx.findNodeById(href_);
    if (!ref) {
      RNS_LOG_ERROR(" !!! Id not Found !!!!");
      return;
    } 
    ref->render(ctx);
}

SkPath RSkComponentRNSVGUse::onAsPath(const SkSVGRenderContext& ctx) const {
    const auto ref =  ctx.findNodeById(href_);
    if (!ref) {
        return SkPath();
    }

    return ref->asPath(ctx);
}

} // namespace react
} // namespace facebook
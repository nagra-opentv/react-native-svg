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
    INHERITED(SkSVGTag::kUse) {
      selfNode=sk_sp<RSkSVGNode>(this);
}

RnsShell::LayerInvalidateMask  RSkComponentRNSVGUse::updateComponentProps(const ShadowView &newShadowView,bool forceUpdate) {
  auto component = getComponentData();

  auto const &newRNSVGUseProps = *std::static_pointer_cast<RNSVGUseProps const>(newShadowView.props);
  
  RNS_LOG_INFO(" X: "<<newRNSVGUseProps.x);
  RNS_LOG_INFO(" Y: "<<newRNSVGUseProps.y);
  RNS_LOG_INFO(" Href: "<<newRNSVGUseProps.href.c_str());
  RNS_LOG_INFO(" Width: "<<newRNSVGUseProps.width);
  RNS_LOG_INFO(" Height: "<<newRNSVGUseProps.height);


     selfNode->SetLengthAttribute(selfNode,SkSVGAttribute::kX,newRNSVGUseProps.x.c_str());

     selfNode->SetLengthAttribute(selfNode,SkSVGAttribute::kY,newRNSVGUseProps.y.c_str());

     selfNode->setAttribute(SkSVGAttribute::kHref,SkSVGStringValue(SkString(newRNSVGUseProps.href.c_str())));
  
 
     selfNode->SetLengthAttribute(selfNode,SkSVGAttribute::kWidth,newRNSVGUseProps.width.c_str());

     selfNode->SetLengthAttribute(selfNode,SkSVGAttribute::kHeight,newRNSVGUseProps.height.c_str());
updateCommonNodeProps(newRNSVGUseProps,selfNode);
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
            fHref = *href;
        }
        break;
    case SkSVGAttribute::kX:
        if (const auto* x = v.as<SkSVGLengthValue>()) {
            fX = *x;
        }
        break;
    case SkSVGAttribute::kY:
        if (const auto* y = v.as<SkSVGLengthValue>()) {
            fY = *y;
        }
        break;
    default:
        this->INHERITED::onSetAttribute(attr, v);
    }
}

bool RSkComponentRNSVGUse::onPrepareToRender(SkSVGRenderContext* ctx) const {

    printf("\n RSkComponentRNSVGUse::onPrepareToRender \n");

    if (fHref.isEmpty() || !INHERITED::onPrepareToRender(ctx)) {
        return false;
    }

    if (fX.value() || fY.value()) {
        // Restored when the local SkSVGRenderContext leaves scope.
        ctx->saveOnce();
        ctx->canvas()->translate(fX.value(), fY.value());
    }

    printf("\n RSkComponentRNSVGUse::onPrepareToRender returns true \n");

    return true;
}

void RSkComponentRNSVGUse::onRender(const SkSVGRenderContext& ctx) const {

    printf("\n RSkComponentRNSVGUse::onRender [%s] \n",fHref.c_str());

    const auto ref = parentNode->findNodeById(fHref.c_str());
    if (!ref) {
            printf("\n !!! Id not Foumd !!!!\n");

        return;
    } 
    printf("\n RSkComponentRNSVGUse::render for [%d]  \n",ref->tag());

    ref->render(ctx);
}

SkPath RSkComponentRNSVGUse::onAsPath(const SkSVGRenderContext& ctx) const {
    const auto ref = parentNode->findNodeById(fHref.c_str());
    if (!ref) {
        return SkPath();
    }

    return ref->asPath(ctx);
}

void RSkComponentRNSVGUse::appendChild(sk_sp<RSkSVGNode>) {
    RNS_LOG_INFO("cannot append child nodes to an SVG shape.\n");
}

} // namespace react
} // namespace facebook
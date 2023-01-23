#include "RSkComponentRNSVGDefs.h"

namespace facebook {
namespace react {

RSkComponentRNSVGDefs::RSkComponentRNSVGDefs(const ShadowView &shadowView)
    : RSkComponent(shadowView,LAYER_TYPE_DEFAULT),
    INHERITED(SkSVGTag::kDefs) {
     selfNode=sk_sp<RSkSVGNode>(this);
}

RnsShell::LayerInvalidateMask  RSkComponentRNSVGDefs::updateComponentProps(const ShadowView &newShadowView,bool forceUpdate) {
   return RnsShell::LayerInvalidateNone;
}

void RSkComponentRNSVGDefs::mountChildComponent(
    std::shared_ptr<RSkComponent> newChildComponent,
    const int index) {

  RNS_LOG_INFO(" RSkComponentRNSVGDefs holding child :" << newChildComponent->getComponentData().componentName);
  
  appendChild(newChildComponent);

  RNS_LOG_INFO("Defs in RSkComponentRNSVGDefs Container:: "<<IDMapper.count());
  RNS_LOG_INFO("Childs in  RSkComponentRNSVGDefs Container :: "<<childrenContainer.count());
}

} // namespace react
} // namespace facebook
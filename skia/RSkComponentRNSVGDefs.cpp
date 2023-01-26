#include "RSkComponentRNSVGDefs.h"

namespace facebook {
namespace react {

RSkComponentRNSVGDefs::RSkComponentRNSVGDefs(const ShadowView &shadowView)
    : RSkComponent(shadowView,LAYER_TYPE_DEFAULT),
    INHERITED(SkSVGTag::kDefs) {
     selfNode=sk_sp<RSkSVGNode>(this);
}

RnsShell::LayerInvalidateMask  RSkComponentRNSVGDefs::updateComponentProps(SharedProps newViewProps,bool forceUpdate) {
   return RnsShell::LayerInvalidateNone;
}

void RSkComponentRNSVGDefs::mountChildComponent(
    std::shared_ptr<RSkComponent> newChildComponent,
    const int index) {

  RNS_LOG_INFO(" RSkComponentRNSVGDefs holding child :" << newChildComponent->getComponentData().componentName);
  
  addComponentToSVGContainer(newChildComponent);

}

} // namespace react
} // namespace facebook
#include "RSkComponentRNSVGDefs.h"

namespace facebook {
namespace react {

RSkComponentRNSVGDefs::RSkComponentRNSVGDefs(const ShadowView &shadowView)
    : RSkComponent(shadowView,LAYER_TYPE_DEFAULT),
    INHERITED(SkSVGTag::kDefs) {}

RnsShell::LayerInvalidateMask  RSkComponentRNSVGDefs::updateComponentProps(SharedProps newViewProps,bool forceUpdate) {
   return RnsShell::LayerInvalidateNone;
}

void RSkComponentRNSVGDefs::mountChildComponent(
    std::shared_ptr<RSkComponent> newChildComponent,
    const int index) {

  RNS_LOG_INFO(" RSkComponentRNSVGDefs holding child :" << newChildComponent->getComponentData().componentName);
  
  addChildAtIndex(newChildComponent,index);

}

void RSkComponentRNSVGDefs::unmountChildComponent(
    std::shared_ptr<RSkComponent> oldChildComponent,
    const int index) {
  RNS_LOG_INFO("RSkComponentRNSVGDefs recieved unmount for child :" << oldChildComponent->getComponentData().componentName);
  removeChildAtIndex(oldChildComponent,index);
}

} // namespace react
} // namespace facebook
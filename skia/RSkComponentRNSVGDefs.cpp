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
  RNS_LOG_INFO("@@@@@@@@@@ON mountChildComponent :: RSkComponentRNSVGGroup holding child :" << newChildComponent->getComponentData().componentName);
if(RSKSVGComponentViewClassWithName(newChildComponent->getComponentData().componentName)) {
  RNS_LOG_INFO("@@@@@@@@@@ON iT IS A svg coMPONENT" );
  auto ref = RSkSVGNode::getRSkSVGNodeForComponnetWIthName(newChildComponent->getComponentData().componentName,newChildComponent);
  if(ref) {
   selfNode->appendChild(ref);
  }
}
  RNS_LOG_INFO("total defs :: "<<fIDMapper.size());
 RNS_LOG_INFO("\n Group : childrenContainer.count() "<<childrenContainer.count());
}

} // namespace react
} // namespace facebook
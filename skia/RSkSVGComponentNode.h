/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include "include/core/SkCanvas.h"
#include "include/core/SkPaint.h"

#include "ReactSkia/components/RSkComponent.h"
#include "RSkSVGNode.h"

using namespace std;

using RSkSVGIDMapper = SkTHashMap<SkString, RSkSVGNode*>;

template<typename componentType,typename propsType>
  const RNSVGCommonRenderableProps *  getCommonRenderablePropsFromComponent(RSkComponent* component) {
    if(component) {
      auto componetNode=static_cast<componentType *>(component);
      auto const props= std::static_pointer_cast<propsType const>(componetNode->getComponentData().props);
       return dynamic_cast<RNSVGCommonRenderableProps const*>(props.get());
    } else {
      return nullptr;
    }
}

namespace facebook {
namespace react {

class RSkSVGComponentNode : public RSkComponent,public RSkSVGNode {

 public:

  ~RSkSVGComponentNode() {}

  // Overrides for Base Class: RSkComponent
  void mountChildComponent(std::shared_ptr<RSkComponent> newChildComponent, const int index)override {};
  void unmountChildComponent(std::shared_ptr<RSkComponent> oldChildComponent,const int index)override {};

  virtual SkSize getContainerSize()const;
  void invalidateParentSvgContainer();
  std::string getRSkSvgComponentName(RSkSVGNode *node) const;

  const RNSVGCommonRenderableProps * getCommonRenderableProps(RSkSVGNode* node) const;

 protected:

  explicit RSkSVGComponentNode(const ShadowView &shadowView,
                               RnsShell::LayerType layerType,
                               SkSVGTag tag)
            : RSkComponent(shadowView,layerType),
              RSkSVGNode(tag) {};

  // Override from Base Class: RSkComponent
  void OnPaint(SkCanvas *canvas) override{};

 private:

};

} // namespace react
} // namespace facebook

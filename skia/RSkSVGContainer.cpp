
/*
 * Copyright (C) 1994-present OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */
#include <string>
#include "include/core/SkPath.h"
#include "include/pathops/SkPathOps.h"

#include "RSkSVGContainer.h"
#include "ReactSkia/RSkThirdPartyFabricComponentsProvider.h"


#include "ReactSkia/utils/RnsUtils.h"

namespace facebook {
namespace react {


RSkSVGContainer::RSkSVGContainer(SkSVGTag t) : INHERITED(t) { }


void RSkSVGContainer::appendSVGChildElements(std::shared_ptr<RSkComponent> childComponent) {

    if(RSkThirdPartyFabricComponentsProvider(childComponent->getComponentData().componentName)) {
      RNS_LOG_INFO("Child Node Name : "<<childComponent->getComponentData().componentName);
     auto node=RSkSVGNode::getRSkSVGNodeForComponetWithName(childComponent);
     if(node) {
       RNS_LOG_INFO("Child Node type  : "<<(int)node->tag());
       auto RskNode=RSkSVGNode::getRSkSVGNodeForComponetWithName(childComponent);
       std::string nodeName = RSkSVGNode::getSVGRefNameForComponetWithName(childComponent)->nodeName;
       if(!nodeName.empty()) {
         RNS_LOG_INFO("Child Node has ID : "<<nodeName);
         IDMapper.set(SkString(nodeName),node);
       }
       if(dynamic_cast<RSkSVGContainer *>(node.get())) {
          auto mergeFn= [&](SkString keyName,sk_sp<SkSVGNode> *value){
            RNS_LOG_ERROR("  MERGING child Defs with It's Parent" );
            IDMapper.set(keyName,*value);
          };
          dynamic_cast<RSkSVGContainer *>(node.get())->IDMapper.foreach(mergeFn);
       }
       // Store node with SKSVG ENgine
       appendChild(node);
     }
    }
}

} // namespace react
} // namespace facebook


/*
 * Copyright (C) 1994-present OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "include/core/SkPath.h"
#include "include/pathops/SkPathOps.h"

#include "RSkSVGContainer.h"
#include "ReactSkia/RSkThirdPartyFabricComponentsProvider.h"


#include "ReactSkia/utils/RnsUtils.h"

namespace facebook {
namespace react {


RSkSVGContainer::RSkSVGContainer(SkSVGTag t) : INHERITED(t) { }

void RSkSVGContainer::appendChild(std::shared_ptr<RSkComponent> childComponent) {

    if(RSkThirdPartyFabricComponentsProvider(childComponent->getComponentData().componentName)) {
      RNS_LOG_INFO("Child Node Name : "<<childComponent->getComponentData().componentName);
     auto node=RSkSVGNode::getRSkSVGNodeForComponetWithName(childComponent);
     if(node) {
       RNS_LOG_INFO("Child Node type  : "<<(int)node->tag());
       if(!node->nodeName.empty()) {
         RNS_LOG_INFO("Child Node has ID : "<<node->nodeName);
         IDMapper.set(SkString(node->nodeName),node);
       }
       if(dynamic_cast<RSkSVGContainer *>(node.get())) {
          auto mergeFn= [&](SkString keyName,sk_sp<SkSVGNode> *value){
            RNS_LOG_ERROR("  MERGING child Defs with It's Parent" );
            IDMapper.set(keyName,*value);
          };
          dynamic_cast<RSkSVGContainer *>(node.get())->IDMapper.foreach(mergeFn);
       }
       childrenContainer.push_back(std::move(node));
     }
    }
}


bool RSkSVGContainer::hasChildren() const {
    return !childrenContainer.empty();
}

void RSkSVGContainer::onRender(const SkSVGRenderContext& ctx) const {
     RNS_LOG_INFO("---Render Childern---");
    for (int i = 0; i < childrenContainer.count(); ++i) {
        RNS_LOG_INFO(" Child Tag : "<<(int)childrenContainer[i]->tag());
        childrenContainer[i]->render(ctx);
    }
}


SkPath RSkSVGContainer::onAsPath(const SkSVGRenderContext& ctx) const {
    SkPath path;

    for (int i = 0; i < childrenContainer.count(); ++i) {
        const SkPath childPath = childrenContainer[i]->asPath(ctx);

        Op(path, childPath, kUnion_SkPathOp, &path);
    }

    this->mapToParent(&path);
    return path;
}

void RSkSVGContainer::printContainiersNodeInfo() {
    for (int i = 0; i < childrenContainer.count(); ++i) {
        RNS_LOG_INFO(" Child Tag : "<<(int)childrenContainer[i]->tag());
        if(dynamic_cast<RSkSVGContainer *>(childrenContainer[i].get())) {
          RNS_LOG_INFO("Is Child Node a container : "<<(void *)dynamic_cast<RSkSVGContainer *>(childrenContainer[i].get()));
          dynamic_cast<RSkSVGContainer *>(childrenContainer[i].get())->printContainiersNodeInfo();
       }
    }
}

} // namespace react
} // namespace facebook

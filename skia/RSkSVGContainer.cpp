
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

void RSkSVGContainer::addComponentToSVGContainer(std::shared_ptr<RSkComponent> childComponent) {

    if(RSkThirdPartyFabricComponentsProvider(childComponent->getComponentData().componentName)) {
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
       rskSVGChildNodeContainer.push_back(node);
      }
      RNS_LOG_INFO("RSK SVG Def Map Size for component : "<< childComponent->getComponentData().componentName << " : "<<IDMapper.count());
      RNS_LOG_INFO("RSK SVG container Size for the Parent : "<<rskSVGChildNodeContainer.count());
    }
}


bool RSkSVGContainer::hasChildren() const {
    return !rskSVGChildNodeContainer.empty();
}

void RSkSVGContainer::onRender(const SkSVGRenderContext& ctx) const {
     RNS_LOG_INFO("---Render Childern---");
    for (int i = 0; i < rskSVGChildNodeContainer.count(); ++i) {
        RNS_LOG_INFO(" Child Tag : "<<(int)rskSVGChildNodeContainer[i]->tag());
        rskSVGChildNodeContainer[i]->render(ctx);
    }
}


SkPath RSkSVGContainer::onAsPath(const SkSVGRenderContext& ctx) const {
    SkPath path;

    for (int i = 0; i < rskSVGChildNodeContainer.count(); ++i) {
        const SkPath childPath = rskSVGChildNodeContainer[i]->asPath(ctx);

        Op(path, childPath, kUnion_SkPathOp, &path);
    }

    this->mapToParent(&path);
    return path;
}

void RSkSVGContainer::printContainiersNodeInfo() {
    for (int i = 0; i < rskSVGChildNodeContainer.count(); ++i) {
        RNS_LOG_INFO(" Child Tag : "<<(int)rskSVGChildNodeContainer[i]->tag());
        if(dynamic_cast<RSkSVGContainer *>(rskSVGChildNodeContainer[i].get())) {
          RNS_LOG_INFO("Is Child Node a container : "<<(void *)dynamic_cast<RSkSVGContainer *>(rskSVGChildNodeContainer[i].get()));
          dynamic_cast<RSkSVGContainer *>(rskSVGChildNodeContainer[i].get())->printContainiersNodeInfo();
       }
    }
}

} // namespace react
} // namespace facebook

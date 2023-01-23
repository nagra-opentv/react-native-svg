
#include "RSkSVGContainer.h"

#include "include/core/SkPath.h"
#include "include/pathops/SkPathOps.h"
#include "ReactSkia/utils/RnsUtils.h"

namespace facebook {
namespace react {


RSkSVGContainer::RSkSVGContainer(SkSVGTag t) : INHERITED(t) { }

void RSkSVGContainer::appendChild(sk_sp<RSkSVGNode> node) {
    
     if(!node) return;

    if(!node->nodeName.empty())
      fIDMapper.insert(std::pair<std::string, sk_sp<RSkSVGNode>>(node->nodeName,node));
     printf("\n @@@@@@@@@@@ tag [%d] of type container ::[%p]@@@@@@@@\n ",node->tag(),(void *)dynamic_cast<RSkSVGContainer *>(node.get()));

     if(dynamic_cast<RSkSVGContainer *>(node.get())) {
       dynamic_cast<RSkSVGContainer *>(node.get())->mergeWithParentMap(fIDMapper);
     }
      node->setParentNode(sk_sp<RSkSVGNode>(this));
    
    childrenContainer.push_back(std::move(node));
}

 sk_sp<RSkSVGNode> RSkSVGContainer::findNodeById(const char* id) {
    std::string idStr(id);
         printf("\n $$$$$$$ Parents[%d]. Map count ;[%lu]$$$$$$$$\n",static_cast<RSkSVGNode *>(this)->tag(),fIDMapper.size());

     RSkSVGIDMapper::iterator it= fIDMapper.find(idStr);
    return (it != fIDMapper.end() ? it->second: nullptr);
 }

 void RSkSVGContainer::mergeWithParentMap(RSkSVGIDMapper &ParentMap) {
     printf("\n $$$$$$$ Parents[%d]. Map count ;[%lu]$$$$$$$$\n",static_cast<RSkSVGNode *>(this)->tag(),ParentMap.size());
     RSkSVGIDMapper::iterator it=fIDMapper.begin();
        while( it != fIDMapper.end()) {
            printf("\n Parents[%d] name [%s] \n",(int)it->second->tag(),it->second->nodeName.c_str());
           if(!(it->first.empty())) {
             ParentMap.insert(std::pair<std::string, sk_sp<RSkSVGNode>>(it->second->nodeName,it->second));
            ++it;
           } 
       }
     printf("\n $$$$$$$ After insertionParents[%d]. Map count ;[%lu]$$$$$$$$\n",static_cast<RSkSVGNode *>(this)->tag(),ParentMap.size());

 }

bool RSkSVGContainer::hasChildren() const {
    return !childrenContainer.empty();
}

void RSkSVGContainer::onRender(const SkSVGRenderContext& ctx) const {
    for (int i = 0; i < childrenContainer.count(); ++i) {
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

} // namespace react
} // namespace facebook

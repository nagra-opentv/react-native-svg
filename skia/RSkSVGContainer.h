/*
 * Copyright (C) 1994-present OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */
#pragma once

#include "RSkSVGNode.h"
#include "include/private/SkTArray.h"

namespace facebook {
namespace react {

using RSkSVGIDMapper = better::map<std::string, sk_sp<RSkSVGNode>>;

class RSkSVGContainer : public RSkSVGNode {
  public:
    ~RSkSVGContainer() override = default;

    void appendChild(sk_sp<RSkSVGNode>) override;
    sk_sp<RSkSVGNode> findNodeById(const char* id) override;
  protected:
    explicit RSkSVGContainer(SkSVGTag);

    void onRender(const SkSVGRenderContext&) const override;

    SkPath onAsPath(const SkSVGRenderContext&) const override;

    bool hasChildren() const final;
   
     RSkSVGIDMapper    fIDMapper;
    SkSTArray<1, sk_sp<RSkSVGNode>, true> childrenContainer;
     void mergeWithParentMap(RSkSVGIDMapper &ParentMap);
  private:
    typedef RSkSVGNode INHERITED;
    
};

} // namespace react
} // namespace facebook




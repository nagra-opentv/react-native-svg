/*
 * Copyright (C) 1994-present OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */
#pragma once

#include <vector>

#include "ReactSkia/components/RSkComponent.h"
#include "RSkSVGNode.h"

namespace facebook {
namespace react {

class RSkSVGContainer : public RSkSVGNode {
  public:
    ~RSkSVGContainer() override;

  protected:
    explicit RSkSVGContainer(SkSVGTag);

    void onRender(const SkSVGRenderContext&) const override;

    SkPath onAsPath(const SkSVGRenderContext&) const override;

    void addChildAtIndex(std::shared_ptr<RSkComponent> childComponent,size_t index);
    void removeChildAtIndex(std::shared_ptr<RSkComponent> childComponent,size_t index);
    bool hasChildren() const final;
   
    SkSVGIDMapper    IDMapper;
    std::vector<sk_sp<SkSVGNode>> childRSkNodeList_;
    void printChildList();
  private:
    typedef RSkSVGNode INHERITED;
    
};

} // namespace react
} // namespace facebook




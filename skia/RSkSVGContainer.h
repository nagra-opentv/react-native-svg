/*
 * Copyright (C) 1994-present OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */
#pragma once

#include "ReactSkia/components/RSkComponent.h"
#include "RSkSVGNode.h"
#include "include/private/SkTArray.h"

namespace facebook {
namespace react {

class RSkSVGContainer : public RSkSVGNode {
  public:
    ~RSkSVGContainer() override = default;

  protected:
    explicit RSkSVGContainer(SkSVGTag);

    void onRender(const SkSVGRenderContext&) const override;

    SkPath onAsPath(const SkSVGRenderContext&) const override;

    void addComponentToSVGContainer(std::shared_ptr<RSkComponent> childComponent);

    bool hasChildren() const final;
   
    SkSVGIDMapper    IDMapper;
    SkSTArray<1, sk_sp<RSkSVGNode>, true> rskSVGChildNodeContainer;
    void printContainiersNodeInfo();
  private:
    typedef RSkSVGNode INHERITED;
    
};

} // namespace react
} // namespace facebook




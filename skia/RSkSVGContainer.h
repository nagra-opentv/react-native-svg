/*
 * Copyright (C) 1994-present OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */
#pragma once

#include "experimental/svg/model/SkSVGNode.h"
#include "experimental/svg/model/SkSVGIDMapper.h"
#include "experimental/svg/model/SkSVGContainer.h"
#include "include/private/SkTArray.h"
#include "RSkSVGNode.h"

#include "ReactSkia/components/RSkComponent.h"

namespace facebook {
namespace react {

class RSkSVGContainer : public SkSVGContainer,public RSkSVGNode{
  public:

  
  protected:
    RSkSVGContainer(SkSVGTag t);
    SkSVGIDMapper    IDMapper;
 //   using SkSVGContainer::appendChild;
    void appendSVGChildElements(std::shared_ptr<RSkComponent> childComponent);
  private:
    typedef SkSVGContainer INHERITED;
    
};

} // namespace react
} // namespace facebook




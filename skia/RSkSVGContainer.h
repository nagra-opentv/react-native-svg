/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */
#pragma once

#include <map>

#include "RSkSVGComponentNode.h"

namespace facebook {
namespace react {

class RSkSVGContainer : public RSkSVGComponentNode {
 public:

  ~RSkSVGContainer();

  //Overrides from Base Class :RSkComponent
  void mountChildComponent(std::shared_ptr<RSkComponent> newChildComponent, const int index)override;
  void unmountChildComponent(std::shared_ptr<RSkComponent> oldChildComponent,const int index)override;

  RSkSVGIDMapper    rskNodeIDMapper;

 protected:

  explicit RSkSVGContainer(const ShadowView &shadowView,
                                  RnsShell::LayerType layerType,
                                  SkSVGTag);

  //Override for Base Class :RSkComponent
  void OnPaint(SkCanvas *canvas) override;

  //Override for Base Class :RSkSVGNode
  void setRoot(RSkSVGNode * rootNode) override;
  void onRender(const SkSVGRenderContext&) const override;
  bool hasChildren() const final;

#ifdef ENABLE_SVG_CHILD_HIERARCHY_DEBUG
  void printChildList();
#endif //ENABLE_SVG_CHILD_HIERARCHY_DEBUG

  std::map<int,RSkSVGNode *> childRSkNodeList_;

 private:

  typedef RSkSVGComponentNode INHERITED;

};

} // namespace react
} // namespace facebook




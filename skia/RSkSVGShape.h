#pragma once

#include "include/core/SkPath.h"
#include "RSkSVGNode.h"
#include "RSkSVGPropsParserUtil.h"


using namespace std;

namespace facebook {
namespace react {

class RSkSVGShape : public RSkSVGNode {
  public:
    ~RSkSVGShape() = default;

    void appendChild(sk_sp<RSkSVGNode>) override;

  protected:
    RSkSVGShape(SkSVGTag);

    void onRender(const SkSVGRenderContext&) const final;
    virtual void onDraw(SkCanvas*, const SkSVGLengthContext&, const SkPaint&,
                        SkPathFillType) const = 0;
  private:
    typedef RSkSVGNode INHERITED;
};

} // namespace react
} // namespace facebook
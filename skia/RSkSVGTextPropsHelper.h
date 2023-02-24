/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
*/
#include <map>
#include "include/core/SkFontStyle.h"

using namespace skia::textlayout;

namespace facebook {
namespace react {

typedef std::map<std::string, SkFontStyle::Weight> FontWeightMap;
typedef std::map<std::string, SkFontStyle::Slant> FontSlantMap;
typedef std::map<std::string, SkFontStyle::Width> FontWidthMap;

static FontWeightMap fontWeightMap = {
  { "normal" , SkFontStyle::Weight::kNormal_Weight     },
  { "bold"   , SkFontStyle::Weight::kBold_Weight       },
  { "bolder" , SkFontStyle::Weight::kExtraBold_Weight  },
  { "lighter", SkFontStyle::Weight::kLight_Weight      },
  { "0"      , SkFontStyle::Weight::kInvisible_Weight  },
  { "100"    , SkFontStyle::Weight::kThin_Weight       },
  { "200"    , SkFontStyle::Weight::kExtraLight_Weight },
  { "300"    , SkFontStyle::Weight::kLight_Weight      },
  { "400"    , SkFontStyle::Weight::kNormal_Weight     },
  { "500"    , SkFontStyle::Weight::kMedium_Weight     },
  { "600"    , SkFontStyle::Weight::kSemiBold_Weight   },
  { "700"    , SkFontStyle::Weight::kBold_Weight       },
  { "800"    , SkFontStyle::Weight::kExtraBold_Weight  },
  { "900"    , SkFontStyle::Weight::kBlack_Weight      },
  { "1000"   , SkFontStyle::Weight::kExtraBlack_Weight },
};
static FontSlantMap fontSlantMap = {
  { "normal" , SkFontStyle::Slant::kUpright_Slant     },
  { "italic" , SkFontStyle::Slant::kItalic_Slant      },
  { "oblique", SkFontStyle::Slant::kOblique_Slant     },
};
static FontWidthMap fontWidthMap ={
  { "normal"          , SkFontStyle::Width::kNormal_Width          },
  { "wider"           , SkFontStyle::Width::kUltraExpanded_Width   },
  { "narrower"        , SkFontStyle::Width::kUltraCondensed_Width  },
  { "condensed"       , SkFontStyle::Width::kCondensed_Width       },
  { "ultra-condensed" , SkFontStyle::Width::kUltraCondensed_Width  },
  { "extra-condensed" , SkFontStyle::Width::kExtraCondensed_Width  },
  { "semi-condensed"  , SkFontStyle::Width::kSemiCondensed_Width   },
  { "semi-expanded"   , SkFontStyle::Width::kSemiExpanded_Width    },
  { "expanded"        , SkFontStyle::Width::kExpanded_Width        },
  { "extra-expanded"  , SkFontStyle::Width::kExtraExpanded_Width   },
  { "ultra-expanded"  , SkFontStyle::Width::kUltraExpanded_Width   },
};

#define DEFINE_TEXT_ATTR(attr_name,attr_type)                                 \
 private:                                                                     \
  attr_type attr_name##_;                                                     \
  bool    attr_name##Set_{false};                                             \
 public:                                                                      \
  void set##attr_name( attr_type a) {                                         \
    attr_name##_=a;                                                           \
    attr_name##Set_=true;                                                     \
  }                                                                           \
  attr_type get##attr_name() const{ return attr_name##_; }                    \
  bool attr_name##HasValue()const { return attr_name##Set_;}

/*
   The attribute finding rule for text style properties works as follows:
      1.Check if the element has the attribute set. If so, use it.
      2.If the attribute is not set, look for it in the parent element.
      3.Traverse the text container and repeat steps 1 and 2 until the attribute value is found 
        or until the root element is reached.
*/
#define DEFINE_TEXT_STYLE_ATTR_GETTER(attr_name,attr_type)                    \
 public:                                                                      \
  bool get##attr_name(attr_type& returnVar) const {                           \
    if(attr_name##HasValue()) {                                               \
      returnVar=get##attr_name();                                             \
      return true;                                                            \
    } else if (textParentNode_){                                              \
      auto node=static_cast<RSkSVGTextContainer *>(textParentNode_);          \
      if(node) {                                                              \
        return node->get##attr_name(returnVar);                               \
      }                                                                       \
    }                                                                         \
    return false;                                                             \
  }

/*
   The position attribute finding rule works as follows:
      1.Check if the element has the position attribute set. If so, use it.
      2.If the attribute is not set, get it from the parent 
            a. if the parent element has content bounds,then current conent to be retreated as a fragment.
               So , pass top-Right of the  last rendered content bounds as a Position info.
            b. if parent container doesn't have content bounds, use position attr from it, if defined.
      3.If neither the bounds nor the attributes defined in the parent element, continue to look for them
        in the parent's parent element ,applying rules 1 & 2.
*/

#define DEFINE_GET_POSITION_ATTR(attr_name)                                   \
 public:                                                                      \
  bool get##attr_name(std::vector<SkScalar>& attrVal) const {                 \
    attrVal.resize(0);                                                        \
    if(attr_name##HasValue()) {                                               \
      attrVal.push_back(get##attr_name().value());                            \
      return true;                                                            \
    } else if (textParentNode_){                                              \
      auto node=static_cast<RSkSVGTextContainer *>(textParentNode_);          \
      if(node) {                                                              \
        return node->get##attr_name##FromParent(attrVal);                     \
      }                                                                       \
    }                                                                         \
   return false;                                                              \
  }                                                                           \
  bool get##attr_name##FromParent(std::vector<SkScalar>& attrVal) const {     \
    if(!contentBounds_.empty()) {                                             \
      attrVal.push_back(contentBounds_.back().fRight);                        \
      attrVal.push_back(contentBounds_.back().fTop);                          \
      return true;                                                            \
    } else if(attr_name##HasValue()) {                                        \
      attrVal.push_back(get##attr_name().value());                            \
      return true;                                                            \
    } else if (textParentNode_){                                              \
      auto node=static_cast<RSkSVGTextContainer *>(textParentNode_);          \
      if(node) {                                                              \
        return node->get##attr_name##FromParent(attrVal);                     \
      }                                                                       \
    }                                                                         \
    return false;                                                             \
  }

/*
   The delta positionattribute finding rule works as follows:
      1.Check if the element has the delta attribute set. If so, use it.
      2.If the attribute is not set, continue look for it in parent element 
               a. If parent has content biunds ,stop searching because the delta attribute is no longer needed. 
                  This is because the parent's content has already been rendered with a delta and
                  that will be reflected in the position attribute.
               b. if parent container doesn't have content bounds, use delta attr from it, if defined in it.
      3.If neither the bounds nor the attributes defined in the parent element, continue to look for them
        in the parent's parent element ,applying rules 1 & 2.
*/

#define DEFINE_GET_DELTA_POSITION_ATTR(attr_name)                             \
 public:                                                                      \
  bool get##attr_name(SkScalar& delatAttrVal) const {                         \
    if(attr_name##HasValue()) {                                               \
      delatAttrVal= get##attr_name().value();                                 \
      return true;                                                            \
    } else if (textParentNode_){                                              \
      auto node=static_cast<RSkSVGTextContainer *>(textParentNode_);          \
      if(node) {                                                              \
        return node->get##attr_name##FromParent(delatAttrVal);                \
      }                                                                       \
    }                                                                         \
    return false;                                                             \
  }                                                                           \
  bool get##attr_name##FromParent(SkScalar& delatAttrVal) const {             \
    if(!contentBounds_.empty()) {                                             \
      return false;                                                           \
    } else if (attr_name##HasValue()){                                        \
      delatAttrVal= get##attr_name().value();                                 \
      return true;                                                            \
    } else if (textParentNode_){                                              \
      auto node=static_cast<RSkSVGTextContainer *>(textParentNode_);          \
      if(node) {                                                              \
        return node->get##attr_name##FromParent(delatAttrVal);                \
      }                                                                       \
    }                                                                         \
    return false;                                                             \
  }

#define SVG_TEXT_ATTR(attr_name,attr_type)                                    \
  DEFINE_TEXT_ATTR(attr_name,attr_type)                                       \
  DEFINE_TEXT_STYLE_ATTR_GETTER(attr_name,attr_type)

#define SVG_TEXT_POSITION_ATTR(attr_name,attr_type)                           \
  DEFINE_TEXT_ATTR(attr_name,attr_type)                                       \
  DEFINE_GET_POSITION_ATTR(attr_name)

#define SVG_TEXT_POSITION_DELTA_ATTR(attr_name,attr_type)                     \
  DEFINE_TEXT_ATTR(attr_name,attr_type)                                       \
  DEFINE_GET_DELTA_POSITION_ATTR(attr_name)
} // namespace react
} // namespace facebook

/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
*/

using namespace skia::textlayout;

namespace facebook {
namespace react {

#define DECLARE_TEXT_PARENT_NODE  \
 protected: \
  RSkSVGNode * textParentNode_{nullptr};

#define DECLARE_CONTAINER_CONTENT_BOUNDS  \
 protected: \
  mutable SkRect contentBounds_;

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
   The attribute finding rule for this finder works as follows:
      1. Check if the element has the attribute set. If so, use it.
      2. If the attribute is not set, look for it in the parent element.
      3.Traverse the text container and repeat steps 1 and 2 until the attribute value is found 
        or until the root element is reached.
*/
#define DEFINE_ATTR_FINDER(attr_name,attr_type)                               \
 public:                                                                      \
  bool find##attr_name(attr_type& returnVar) const {                          \
    if(attr_name##HasValue()) {                                               \
      returnVar=get##attr_name();                                             \
      return true;                                                            \
    } else if (textParentNode_){                                              \
      auto node=static_cast<RSkSVGTextContainer *>(textParentNode_);          \
      if(node) {                                                              \
        return node->find##attr_name(returnVar);                              \
      }                                                                       \
    }                                                                         \
    return false;                                                             \
  }

/*
   The attribute finding rule for this finder works as follows:
      1. Check if the element has the position attribute set. If so, use it.
      2. If the attribute is not set, and if the parent element has content, 
         then it have to be retreated as a fragment to its fragment.
         use the top-Right of the content bounds as a Position info.
      3. If the bounds are not defined in the parent element, continue to look for them
         in the parent's parent element ,applying rules 1 & 2.
*/

#define DEFINE_TEXT_POSITION_ATTR_FINDER(attr_name)                           \
 public:                                                                      \
  bool get##attr_name##FromParent(std::vector<SkScalar>& v) const {           \
    if(!contentBounds_.isEmpty()) {                                           \
      v.resize(0);                                                            \
      v.push_back(contentBounds_.fRight);                                     \
      v.push_back(contentBounds_.fTop);                                       \
      return true;                                                            \
    } else if(attr_name##HasValue()) {                                        \
      v.resize(0);                                                            \
      v.push_back(get##attr_name().value());                                  \
      return true;                                                            \
    }                                                                         \
    return false;                                                             \
  }                                                                           \
  bool find##attr_name(std::vector<SkScalar>& v) const {                      \
    if(attr_name##HasValue()) {                                               \
      v.resize(0);                                                            \
      v.push_back(get##attr_name().value());                                  \
      return true;                                                            \
    } else if (textParentNode_){                                              \
      auto node=static_cast<RSkSVGTextContainer *>(textParentNode_);          \
      if(node) {                                                              \
        return node->get##attr_name##FromParent(v);                           \
      }                                                                       \
    }                                                                         \
   return false;                                                              \
  }

#ifdef ENABLE_DELTA_ATTR_SUPPORT
/*
   The attribute finding rule for this finder works as follows:
      1. Check if the element has the delta attribute set. If so, use it.
      2. If the attribute is not set, and if the parent element has content, 
         stop searching because the delta attribute is no longer needed. 
         This is because the parent's content has already been rendered with a delta 
         that will be reflected in the position attribute.
      3. If the bounds are not defined in the parent element, use the delta attribute from parent,
         if avails.
      TODO: Delta  typcially to be applied on last drawn Text. 
            To Achieve it list of drawm text bounds to be maintained.
*/

#define DEFINE_TEXT_POSITION_DELTA_ATTR_FINDER(attr_name)                     \
 public:                                                                      \
  bool find##attr_name(std::vector<SkScalar>& v) const {                      \
    if(attr_name##HasValue()) {                                               \
     v.resize(0);                                                             \
     v.push_back(get##attr_name().value());                                   \
     return true;                                                             \
    } else if (textParentNode_){                                              \
      auto node=static_cast<RSkSVGTextContainer *>(textParentNode_) ;         \
      if(node) {                                                              \
        if(!node->contentBounds_.isEmpty() && node->attr_name##HasValue()) {  \
          v.resize(0);                                                        \
          v.push_back(get##attr_name().value());                              \
        }                                                                     \
      }                                                                       \
    }                                                                         \
   return false;                                                              \
  }
#endif/*ENABLE_DELTA_ATTR_SUPPORT*/

#define SVG_TEXT_ATTR(attr_name,attr_type)                                    \
  DEFINE_TEXT_ATTR(attr_name,attr_type)                                       \
  DEFINE_ATTR_FINDER(attr_name,attr_type)

#define SVG_TEXT_POSITION_ATTR(attr_name,attr_type)                           \
  DEFINE_TEXT_ATTR(attr_name,attr_type)                                       \
  DEFINE_TEXT_POSITION_ATTR_FINDER(attr_name)

#ifdef ENABLE_DELTA_ATTR_SUPPORT
#define SVG_TEXT_POSITION_DELTA_ATTR(attr_name,attr_type)                     \
  DEFINE_TEXT_ATTR(attr_name,attr_type)                                       \
  DEFINE_TEXT_POSITION_DELTA_ATTR_FINDER(attr_name)
#endif/*ENABLE_DELTA_ATTR_SUPPORT*/
} // namespace react
} // namespace facebook
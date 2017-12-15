#ifndef FAMILY_TREE_RELATIONSHIP_TYPE_H_
#define FAMILY_TREE_RELATIONSHIP_TYPE_H_

namespace family_tree {

enum class RelationshipType {
  SELF,
  PARENT,
  GRANDPARENT,
  SIBLING,
  HALF_SIBLING,
  CHILD,
  GRANDCHILD,
  // OTHER implies a familial relationship which is not one of the other named
  // relationship types.
  OTHER
  // Note that only familial relationships appear in a family tree, so there is
  // no need for a NONE enum here.
};

}  // namespace family_tree

#endif  // FAMILY_TREE_RELATIONSHIP_TYPE_H_

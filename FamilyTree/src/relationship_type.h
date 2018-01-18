#ifndef FAMILY_TREE_RELATIONSHIP_TYPE_H_
#define FAMILY_TREE_RELATIONSHIP_TYPE_H_

namespace family_tree {

enum class RelationshipType {
  SELF,
  PARENT,
  GRANDPARENT,
  // A sibling has the same parents.
  SIBLING,
  // A half-sibling shares only one parent through direct inheritance.
  HALF_SIBLING,
  // A step-sibling shares a parent, but not via inheritance -- only via a
  // spousal relationship between their parent and another parent's child.
  STEP_SIBLING,
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

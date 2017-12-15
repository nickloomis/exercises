#ifndef FAMILY_TREE_TYPEDEFS_H_
#define FAMILY_TREE_TYPEDEFS_H_

#include <map>

namespace family_tree {

// Forward class declarations.
class Person;
class TreeNode;

// Key for a map which stores unique nodes in a family tree.
typedef std::pair<const Person*, const Person*> NodeMapKey;

// Map which stores unique nodes in a family tree.
typedef std::map<NodeMapKey, TreeNode> NodeMap;

// An edge connects between two nodes in the family tree.
typedef std::pair<NodeMapKey, NodeMapKey> TreeEdge;

}  // namespace family_tree

#endif  // FAMILY_TREE_TYPEDEFS_H_

#ifndef FAMILY_TREE_TYPEDEFS_H_
#define FAMILY_TREE_TYPEDEFS_H_

#include <map>
#include <utility>

namespace family_tree {

// Forward class declarations.
class Person;
struct TreeNode;

// Key for a map which stores unique nodes in a family tree.
typedef std::pair<const Person*, const Person*> NodeMapKey;

// Map which stores unique nodes in a family tree.
typedef std::map<NodeMapKey, TreeNode> NodeMap;

}  // namespace family_tree

#endif  // FAMILY_TREE_TYPEDEFS_H_

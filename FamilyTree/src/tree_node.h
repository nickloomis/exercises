#ifndef FAMILY_TREE_TREE_NODE_H_
#define FAMILY_TREE_TREE_NODE_H_

#include <string>

#include "relationship_type.h"

namespace family_tree {

enum class TreeNodeType {
  INDIVIDUAL,
  OFFSPRING,
};

struct TreeNode {
  // TODO(nloomis): how is the relationship label set, normally? can that be
  //  init'd in the c'tor?
  TreeNode(const std::string& name_label, const RelationshipType& relationship, int relative_generation)
    : name_label(name_label),
      relationship(relationship),
      relative_generation(relative_generation),
      node_type(TreeNodeType::INDIVIDUAL) {
  }

  static TreeNode OffspringNode(int relative_generation) {
    TreeNode node("", RelationshipType::PARENT, relative_generation);
    node.node_type = TreeNodeType::OFFSPRING;
    return node;
  }

  // TODO(nloomis): static TreeNode TreeNode::OffspringNode(generation) fcn;
  // will need to explain why that's being done (clarity) versus a c'tor which
  // is nearly empty

  std::string name_label;
  RelationshipType relationship;
  int relative_generation;  // note: used for drawing graph
  // TODO(nloomis): TreeNodeType isn't a good descriptor. same for relationship "type".
  TreeNodeType node_type;
};

}  // namespace family_tree

#endif  // FAMILY_TREE_TREE_NODE_H_

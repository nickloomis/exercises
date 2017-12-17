// TODO(nloomis): overview of "tree" concepts, different node types.

#ifndef FAMILY_TREE_TREE_NODE_H_
#define FAMILY_TREE_TREE_NODE_H_

#include <list>
#include <map>
#include <string>
#include <vector>

#include "relationship_type.h"
#include "typedefs.h"

namespace family_tree {

enum class TreeNodeType {
  // Node which represents a single person.
  INDIVIDUAL,
  // Node which represents 
  OFFSPRING,
};

struct TreeNode {
  TreeNode(const std::string& name_label, const RelationshipType& relationship, int relative_generation)
    : name_label(name_label),
      relationship(relationship),
      relative_generation(relative_generation),
      node_type(TreeNodeType::INDIVIDUAL) {
  }

  static TreeNode OffspringNode(int relative_generation);

  // TODO(nloomis): static TreeNode TreeNode::OffspringNode(generation) fcn;
  // will need to explain why that's being done (clarity) versus a c'tor which
  // is nearly empty

  // Name to display on the node, such as the person's name.
  std::string name_label;
  // An enum which gives this node's relationship relative to the reference
  // individual at the center of the tree.
  RelationshipType relationship;
  // The number of generations remove this node is from the reference
  // individual. A value of zero is the same generation as the reference (eg,
  // part of the same cohort.) Negative values denote generations which came
  // before the reference (eg, parents, aunts/uncles, grandparents), while
  // positive values denote later generations (eg, children, grandchildren).
  int relative_generation;  // note: used for drawing graph
  // TODO(nloomis): TreeNodeType isn't a good descriptor. same for relationship "type".
  TreeNodeType node_type;
};

// A TreeEdge denotes a connection between two nodes in the tree.
// This is a struct (as opposed to a pair) so that new members can be added at
// a later time; one example use-case would be to include metadata about what
// the edge represents, such as "offspring", "adoption", or "spouse".
struct TreeEdge {
  TreeEdge(const NodeMapKey& tail_node, const NodeMapKey& head_node)
    : tail_node(tail_node), head_node(head_node) {
  }

  const NodeMapKey tail_node;
  const NodeMapKey head_node;
};

class Tree {
 public:
  // Accessors to member data.
  const  NodeMap& nodes() const {return nodes_; }
  const std::vector<TreeEdge>& edges() const {return edges_; }

  bool AddNode(const Person* person, const TreeNode& node);
  bool AddNode(const std::list<Person*>& parents, const TreeNode& node);
  void AddTreeEdge(const NodeMapKey& node1, const NodeMapKey& node2);

  bool NodeExists(const Person* person) const;
  bool NodeExists(const std::list<Person*>& parents) const;

  const NodeMapKey GetNodeMapKey(const Person*) const;
  const NodeMapKey GetNodeMapKey(const std::list<Person*>& parents) const;

  // Functions which return the depth of the tree and which nodes are at
  // which generational depth could be helpful when drawing the tree.

 private:
  NodeMap nodes_;
  std::vector<TreeEdge> edges_;

  // TODO(nloomis): map for which nodes belong to each generation.
};

}  // namespace family_tree

#endif  // FAMILY_TREE_TREE_NODE_H_

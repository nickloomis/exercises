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

  static TreeNode OffspringNode(int relative_generation);

  // TODO(nloomis): static TreeNode TreeNode::OffspringNode(generation) fcn;
  // will need to explain why that's being done (clarity) versus a c'tor which
  // is nearly empty

  std::string name_label;
  RelationshipType relationship;
  int relative_generation;  // note: used for drawing graph
  // TODO(nloomis): TreeNodeType isn't a good descriptor. same for relationship "type".
  TreeNodeType node_type;
};

struct TreeEdge {
  TreeEdge(const NodeMapKey& tail_node, const NodeMapKey& head_node)
    : tail_node(tail_node), head_node(head_node) {
  }

  const NodeMapKey tail_node;
  const NodeMapKey head_node;
  // TODO(nloomis): this is a struct so that it can be expanded later;
  // one use-case is to denote special relationships between pairs of
  // people, such as "spouse".
};

class Tree {
 public:
  const  NodeMap& nodes() const {return nodes_; }
  const std::vector<TreeEdge>& edges() const {return edges_; }

  void AddNode(const Person* person, const TreeNode& node);
  void AddNode(const std::list<Person*>& parents, const TreeNode& node);
  void AddTreeEdge(const NodeMapKey& node1, const NodeMapKey& node2);

  bool NodeExists(const Person* person) const;
  bool NodeExists(const std::list<Person*>& parents) const;

  // TODO(nloomis): better function names.
  const NodeMapKey NodeKey(const Person*) const;
  const NodeMapKey NodeKey(const std::list<Person*>& parents) const;

 private:
  NodeMap nodes_;
  std::vector<TreeEdge> edges_;
};

}  // namespace family_tree

#endif  // FAMILY_TREE_TREE_NODE_H_

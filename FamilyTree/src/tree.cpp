#include "tree.h"

#include <utility>

namespace family_tree {

TreeNode TreeNode::OffspringNode(int relative_generation) {
  TreeNode node("", RelationshipType::PARENT, relative_generation);
  node.node_type = TreeNodeType::OFFSPRING;
  return node;
}

bool Tree::AddIndividualNode(const Person* person, const TreeNode& node) {
  if (!NodeExists(person)) {
    nodes_.emplace(GetNodeMapKey(person), node);
    return true;
  }
  return false;
}

bool Tree::AddOffspringNode(const std::list<Person*>& parents,
                            int relative_generation) {
  if (!NodeExists(parents)) {
    nodes_.emplace(GetNodeMapKey(parents),
                   TreeNode::OffspringNode(relative_generation));
    return true;
  }
  return false;
}

void Tree::AddTreeEdge(const NodeMapKey& tail_node,
                       const NodeMapKey& head_node) {
  edges_.emplace_front(TreeEdge(tail_node, head_node));
}

bool Tree::NodeExists(const Person* person) const {
  return nodes_.find(GetNodeMapKey(person)) != nodes_.end();
}

bool Tree::NodeExists(const std::list<Person*>& parents) const {
  return nodes_.find(GetNodeMapKey(parents)) != nodes_.end();
}

const NodeMapKey Tree::GetNodeMapKey(const Person* person) const {
  // NodeMapKey is a std::pair for now; update this and the overloaded
  // GetNodeMapKey if the type ever changes.
  return std::make_pair(person, person);
}

const NodeMapKey Tree::GetNodeMapKey(const std::list<Person*>& parents) const {
  if (parents.empty()) {
    return std::make_pair(nullptr, nullptr);
  } else if (parents.size() == 1) {
    return std::make_pair(nullptr, parents.front());
  }
  return std::make_pair(std::min(parents.front(), parents.back()), 
                        std::max(parents.front(), parents.back()));
}

}  //namespace family_tree

#include "tree.h"

#include <utility>

namespace family_tree {

TreeNode TreeNode::OffspringNode(int relative_generation) {
  TreeNode node("", RelationshipType::PARENT, relative_generation);
  node.node_type = TreeNodeType::OFFSPRING;
  return node;
}

bool Tree::AddNode(const Person* person, const TreeNode& node) {
  if (!NodeExists(person)) {
    nodes_.emplace(GetNodeMapKey(person), node);
    return true;
  }
  return false;
}

bool Tree::AddNode(const std::list<Person*>& parents, const TreeNode& node) {
  if (!NodeExists(parents)) {
    nodes_.emplace(GetNodeMapKey(parents), node);
    return true;
  }
  return false;
}

void Tree::AddTreeEdge(const NodeMapKey& node1, const NodeMapKey& node2) {
  edges_.emplace_back(TreeEdge(node1, node2));
}

bool Tree::NodeExists(const Person* person) const {
  return nodes_.find(GetNodeMapKey(person)) != nodes_.end();
}

bool Tree::NodeExists(const std::list<Person*>& parents) const {
  return nodes_.find(GetNodeMapKey(parents)) != nodes_.end();
}

const NodeMapKey Tree::GetNodeMapKey(const Person* person) const {
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

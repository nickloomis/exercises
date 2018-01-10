// A family tree is represented in this implementation as a directed graph which
// shows the "flow" of ancestral information from generation to generation. Like
// any graph, the Tree is composed of nodes (or vertices) and edges.
//
// Nodes are distinct combinations of ancestral information, and come in two
// types. The first type is an individual person. The second type is an
// "offspring" node and represents a pairing of two individuals which resulted
// in descendants. The use of an offspring node is not strictly necessary, but
// does result in a cleaner image when the tree is rendered.
//
// Edges denote direct relationships bewtween nodes: the parents which paired
// together for an offspring node and which descendants came from an offspring
// node.

#ifndef FAMILY_TREE_TREE_NODE_H_
#define FAMILY_TREE_TREE_NODE_H_

#include <list>
#include <map>
#include <string>

#include "relationship_type.h"

namespace family_tree {

// Forward declarations:
class Person;

// Key for a map which stores unique nodes in a family tree.
typedef std::pair<const Person*, const Person*> NodeMapKey;


enum class TreeNodeType {
  // Node which represents a single person.
  INDIVIDUAL,

  // Node which represents the collection of offspring from a unique pairing of
  // two parent individuals.
  OFFSPRING,
};

// TreeNodes contain the metadata for a single node. A graph emitter is expected
// to use the metadata when rendering the ndoe. 
struct TreeNode {
  TreeNode(const std::string& name_label,
           const RelationshipType& relationship,
           int relative_generation)
    : name_label(name_label),
      relationship(relationship),
      relative_generation(relative_generation),
      node_type(TreeNodeType::INDIVIDUAL) {
  }

  // Returns a TreeNode for an offspring node. The following values are set:
  //  name_label: empty string
  //  relationship: RelationshipType::PARENT
  //  node_type: TreeNodeType::OFFSPRING
  static TreeNode OffspringNode(int relative_generation);
  // Note: a static is used here as a factory function.

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
  const std::map<NodeMapKey, TreeNode>& nodes() const {return nodes_; }
  const std::list<TreeEdge>& edges() const {return edges_; }

  // Attempts to add the supplied TreeNode to the nodes_ map for an individual
  // person, returning tree if successful or false if the node already exists.
  bool AddIndividualNode(const Person* person, const TreeNode& node);

  // Attempts to add an offspring node for a set of parents, at a specific
  // relative generation (usually the same as the parents' nodes).
  bool AddOffspringNode(const std::list<Person*>& parents,
                        int relative_generation);

  // Adds an edge between two NodeMapKeys.
  void AddTreeEdge(const NodeMapKey& tail_node, const NodeMapKey& head_node);

  // Returns true if a node exists in the graph, false if it does not. The first
  // form is used for individuals, while the second is used for offspring nodes.
  bool NodeExists(const Person* person) const;
  bool NodeExists(const std::list<Person*>& parents) const;

  // Generates a unique key for the Tree's NodeMap. The first form is for
  // individual people. The second form is for offspring nodes. 
  const NodeMapKey GetNodeMapKey(const Person*) const;
  const NodeMapKey GetNodeMapKey(const std::list<Person*>& parents) const;

  // Future extensions:
  // Functions which provide introspection on the graph could be useful when
  // rendering the graph -- for example, the spread in generations in the tree,
  // or which nodes belong to each generation.

 private:
  std::map<NodeMapKey, TreeNode> nodes_;
  std::list<TreeEdge> edges_;
};

}  // namespace family_tree

#endif  // FAMILY_TREE_TREE_NODE_H_

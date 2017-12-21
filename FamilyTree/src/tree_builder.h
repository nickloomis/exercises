#ifndef FAMILY_TREE_TREE_BUILDER_H_
#define FAMILY_TREE_TREE_BUILDER_H_

#include <limits>
#include <stack>
#include <vector>

#include "person.h"
#include "relationship_labeler.h"
#include "tree.h"

namespace family_tree {

struct TreeBuilderOptions {
  // The number of generations to build the tree in the upstream (parent)
  // direction from a reference individual. A value of 1 stops with the parents'
  // generation; a value of 2 stops at the grandparents' generation; etc.
  int upstream_depth = std::numeric_limits<int>::max();

  // The number of generations to build the tree in the downstream (child)
  // direction from a reference individual.
  int downstream_depth = std::numeric_limits<int>::max();
};

// A family tree is a directed graph which displays familial inheritance. The
// tree has special rules which allow it to be constructed from a collection of
// Person objects:
//
//   - each Person has a maximum of two parents
//   - each Person has its own graph node
//   - the parents of each Person imply an offspring node
//   - edges connect from the parents to the offspring to the Person
//
// These rules are sufficient to generate this inheritance subgraph:
//
//      +--------+        +--------+
//      | Person |        | Person |
//      |(parent)|        |(parent)|
//      +--------+        +--------+
//          |                 |
//          |   +---------+   |
//          +-->|offspring|<--+
//              +---------+
//                   |
//                   v
//              +---------+
//              | Person  |
//              +---------+
//
// Each parent has their own subgraph, as do the children (not depicted) of each
// Person. The TreeBuilder traverses the subgraphs, up to a maximum limit,
// creating the nodes and edges of the full graph as it goes.
//
// The tree is assumed to be acyclic (eg, no time travel allowed). If parents
// contribute to more than one generation, the shape of the tree will differ
// based on the order of node discovery; hence, it is not recommended for use
// with purebred animal or plant heritages without modifications.
class TreeBuilder {
 public:
  // The initial_person serves as the "center" of the tree: it is traced up to
  // some maximum depth from that person, and the relationship label for nodes
  // is relative to this person. The options gives the depth in each tracing
  // direction. The tree is built immediately upon object construction.
  TreeBuilder(const Person* initial_person, const TreeBuilderOptions& options);

  const Tree& tree() { return tree_; }

 private:

  // Minimum working data for following a traceable quantity through the tree.
  // Traceables are pushed to temporary stacks to denote where a later trace
  // should start.
  struct Traceable {
    Traceable(const Person* person, int generation)
      : person(person), generation(generation) {}

    // Person to use when tracing outgoing parent or child relationships.  
    const Person* person;

    // Absolute relative generation. The initial_person has generation = 0.
    // Upstream (parent) generations have negative values, while downstream
    // (child) generations have positive values.
    const int generation;
  };

  // Returns true when there are no futher Person* pointers to trace.
  bool IsDone() const;

  // Traces the next Traceable in the stacks, depth-first.
  void TraceNext();

  // Traces the next upstream Traceable. If the node for the Traceable's person
  // doesn't exist, it is added to nodes_.
  // TODO(nloomis): complete this thought.

  // Traces the next upstream Traceable, adding a node for the traceable.person.
  // An offspring node is added if it doesn't exist. If the parent nodes for
  // the traceable.person don't exist, they are added to the stack for later
  // tracing. Edges are added to the tree as needed. When nodes are added, a
  // Traceable is also added to the downstream stack to trace later.
  //
  // Note that upstream tracing is where the work of adding nodes and edges
  // occurs.
  void TraceNextUpstream();

  // Traces the next downstream Traceable. The descendants of the next
  // downstream traceable.person are checked for whether they exist in the tree;
  // if not, they are added to the upstream stack to trace later (and get
  // added to the tree).
  void TraceNextDownstream();

  // Track which Traceables need to have their subgraphs traced.
  std::stack<Traceable> upstream_to_trace_;
  std::stack<Traceable> downstream_to_trace_;

  // Storage for the tree built by the factory.
  Tree tree_;

  const TreeBuilderOptions options_;

  // Nodes are constructed with an enum giving the relationship of the node to
  // the initial_person, specified in the c-tor.
  const RelationshipLabeler relationship_;
};

}  // namespace family_tree

#endif  // FAMILY_TREE_TREE_BUILDER_H_
#ifndef FAMILY_TREE_TREE_BUILDER_H_
#define FAMILY_TREE_TREE_BUILDER_H_

#include <limits>
#include <map>
#include <stack>
#include <utility>
#include <vector>

#include "person.h"
#include "relationship_labeler.h"
#include "tree_node.h"
#include "typedefs.h"

namespace family_tree {

struct TreeBuilderOptions {
  int upstream_depth = std::numeric_limits<int>::max();
  int downstream_depth = std::numeric_limits<int>::max();
};

// A family tree is a specialized form of a directed graph.
//
// note: acyclic if inbreeding is not allowed; wouldn't work well for, eg,
// purebred horses or dogs or flowers or...
class TreeBuilder {
 public:
  TreeBuilder(const Person* initial_person, const TreeBuilderOptions& options);

  const  NodeMap& nodes() const {return nodes_; }
  const std::vector<TreeEdge>& edges() const {return edges_; }

//  std::string GraphString() const;

  void PrintStacks() const;

 private:

  // Minimum working data for following a traceable quantity through the tree.
  // Traceables are pushed to temporary stacks to denote where a later trace
  // should start.
  struct Traceable {
    Traceable(const Person* person, int generation)
      : person(person), generation(generation) {}
    const Person* person;
    int generation;
  };

  bool IsDone() const;
  void TraceNext();
  void TraceNextUpstream();
  void TraceNextDownstream();

  // TODO(nloomis): better function names.
  const NodeMapKey NodeKey(const Person*) const;
  const NodeMapKey NodeKey(const std::list<Person*>& parents) const;

  bool NodeExists(const Person*) const;
  bool NodeExists(const std::list<Person*>& parents) const;

  //std::stack<Traceable> upstream_to_trace_;
  //std::stack<Traceable> downstream_to_trace_;
  std::vector<Traceable> upstream_to_trace_;
  std::vector<Traceable> downstream_to_trace_;

  void AddTreeEdge(const NodeMapKey& node1, const NodeMapKey& node2);

  NodeMap nodes_;
  // TODO(nloomis): does this need to be a vector? easy, but more overhead.
  std::vector<TreeEdge> edges_;

  const TreeBuilderOptions options_;
  // TODO(nloomis): implement the named relationships thinger.
  const RelationshipLabeler relationship_;
};

}  // namespace family_tree

#endif  // FAMILY_TREE_TREE_BUILDER_H_
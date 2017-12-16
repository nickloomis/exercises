#ifndef FAMILY_TREE_GRAPH_EMITTER_H_
#define FAMILY_TREE_GRAPH_EMITTER_H_

#include <limits>
#include <ostream>
#include <string>

#include "relationship_type.h"
#include "tree.h"

namespace family_tree {

struct TreeBuilderOptions;

struct GraphEmitterOptions {
  int ancestor_depth = std::numeric_limits<int>::max();
  int descendant_depth = std::numeric_limits<int>::max();
  std::string reference_individual_background_color = "azure1";
  std::string default_individual_background_color = "white";
  // Extensions of this struct include:
  //  - colors for different individuals
  //  - whether to draw the tree using a directed or undirected graph
  //  - whether the offspring nodes should be drawn at the same height as the
  //    parents, or offset downwards
};

class GraphEmitter {
 public:
  GraphEmitter(const GraphEmitterOptions& options);

  void Emit(const Tree& tree, std::ostream& output_stream) const;

  // Returns a set of options for building a tree given the intended graph. The
  // options can be used directly when initializing a new TreeBuilder.
  TreeBuilderOptions TreeOptions() const;

 private:
  std::string RelationshipString(const RelationshipType& relationship) const;

  GraphEmitterOptions options_;
};

}  // namespace family_tree

#endif  // FAMILY_TREE_GRAPH_EMITTER_H_

#ifndef FAMILY_TREE_GRAPH_EMITTER_H_
#define FAMILY_TREE_GRAPH_EMITTER_H_

#include <limits>
#include <ostream>
#include <string>

#include "relationship_type.h"
#include "tree.h"

namespace family_tree {

struct TreeBuilderOptions;

// Options for how to compute and draw a family tree.
struct GraphEmitterOptions {
  // The number of generations which came before the reference individual. For
  // example, a value of one would limit the tree to parents; a value of two
  // would limit the tree to grandparents at most.
  int ancestor_depth = std::numeric_limits<int>::max();

  // The number of generations which come after the reference individual. For
  // example, a value of one would limit the tree to just the children, while a
  // value of two limits the tree to children and grandchildren.
  int descendant_depth = std::numeric_limits<int>::max();

  // Strings for the background color of the node when drawing the reference
  // individual's node or any other node. See
  // https://graphviz.gitlab.io/_pages/doc/info/attrs.html#k:color for more
  // details about specifying colors.
  std::string reference_individual_background_color = "azure1";
  std::string default_individual_background_color = "white";

  // Extensions of this struct include:
  //  - colors for different individuals or relationships
  //  - whether to draw the tree using a directed or undirected graph
  //  - whether the offspring nodes should be drawn at the same height as the
  //    parents, or offset downwards
};

class GraphEmitter {
 public:
  GraphEmitter(const GraphEmitterOptions& options);

  // Writes the tree as a DOT file to the output stream, using the options
  // passed to the object c'tor.
  // For details on the DOT format, see
  // https://en.wikipedia.org/wiki/DOT_(graph_description_language)
  void Emit(const Tree& tree, std::ostream& output_stream) const;

  // Returns a set of options for building a tree given the intended graph. The
  // options can be used directly when initializing a new TreeBuilder.
  TreeBuilderOptions TreeOptions() const;

 private:
  // Returns the string which describes the RelationshipType. Current returns
  // include "self", "parent", "grandparent", "sibling", "half-sibling",
  // "child", or "grandchild". A RelationshipType::OTHER returns an empty
  // string.
  std::string RelationshipString(const RelationshipType& relationship) const;

  GraphEmitterOptions options_;
};

}  // namespace family_tree

#endif  // FAMILY_TREE_GRAPH_EMITTER_H_

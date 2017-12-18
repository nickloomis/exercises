// A family tree is a graph -- and there are any number of libraries and
// utilities for plotting graphs. This implementation emits a DOT file which
// provides node (vertex) and edge metadata. The DOT file can then be consumed
// by a plotting tool which decides how to distribute and draw the nodes.
//
// The suggested tool for plotting DOT files is Graphviz, available from
// http://www.graphviz.org, licensed under the Common Public License v1. It has
// both command-line binaries and library versions, is cross-platform, and has
// bindings/ports for a variety of languages (including Java and Javascript).
// The Graphviz 'dot' binary, in particular, is ideal for plotting the DOT files
// to more closely resemble heirarchical family trees.
//
//   Example: if the emitted graph is saved to family_tree_graph.gv, use
//
//   >> dot -Tpng family_tree_graph.gv >> family_tree.png
//
//   to generate a PNG image of the tree and pipe it into a file.
//
// The implementation in this file uses streams for the data which would go into
// the DOT file, leaving the destination up to the user. For example, the file
// could be saved to a ofstream that points to a file on disk, or it could be
// routed completely in-memory for access by a library or further processing.

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
  //   https://graphviz.gitlab.io/_pages/doc/info/attrs.html#k:color for more
  // details about specifying colors, or
  //   https://graphviz.gitlab.io/_pages/doc/info/colors.html
  // for a large list of named colors.
  std::string reference_individual_background_color = "azure1";  // light blue
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

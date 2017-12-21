#include "graph_emitter.h"

#include <iostream>
#include <sstream>
#include <string>

#include "tree_builder.h"

namespace {

// Returns a unique identifier string for the input NodeMapKey. The ID is based
// on pointer values, and is not expected to be the same each time the binary is
// run.
std::string UniqueNodeIdString(const family_tree::NodeMapKey& key) {
  std::stringstream stream;
  stream << "\"";
  if (key.first == key.second) {
    stream << key.first;
  } else {
    if (key.first) {
      stream << key.first << "+" << key.second;
    } else {
      stream << "nullptr+" << key.second;
    }
  }
  stream << "\"";
  return stream.str();
}

}  // namespace anonymous

namespace family_tree {

GraphEmitter::GraphEmitter(const GraphEmitterOptions& options)
    : options_(options) {
}

void GraphEmitter::Emit(const Tree& tree, std::ostream& output_stream) const {
  // Start the graph.
  output_stream << "graph {\n";

  std::cout << "Emitting graph with " << tree.nodes().size() << " nodes and " << 
    tree.edges().size() << " edges\n";

  // Offspring nodes give more control over how the graph gets rendered (and
  // reduce visual clutter). To force the offspring nodes to appear at the same
  // height as the parents, they should all be listed as having the same rank
  // using the {rank=same; node1 node2 node3;} instruction.

  for (const auto& kv : tree.nodes()) {
    output_stream << UniqueNodeIdString(kv.first);
    if (kv.second.node_type == TreeNodeType::INDIVIDUAL) {
      output_stream << " [shape=box, label=\"" << kv.second.name_label;
      const std::string& relationship_string =
          RelationshipString(kv.second.relationship);
      if (!relationship_string.empty()) {
        output_stream << "\\n" << relationship_string;
      }
      output_stream << "\", ";
      if (kv.second.relationship == RelationshipType::SELF) {
        // Highlight the root individual.
        output_stream << "style=\"bold, filled\", fillcolor=" <<
          options_.reference_individual_background_color;
      } else {
        output_stream << "style=filled, fillcolor=" <<
          options_.default_individual_background_color;
      }
      output_stream << "];\n";
    } else {
      // Offspring node.
      // The shape and size are arbitrary, and could be set via the options
      // struct.
      output_stream << "[shape=circle, style=filled, label=\"\", " <<
       "height=0.1, width=0.1];\n";
    }
  }

  for (const TreeEdge& edge : tree.edges()) {
    output_stream << UniqueNodeIdString(edge.tail_node) << "--" <<
     UniqueNodeIdString(edge.head_node) << ";\n";
  }

  // End of graph definition.
  output_stream << "}\n";
}

TreeBuilderOptions GraphEmitter::TreeOptions() const {
  TreeBuilderOptions tree_options;
  tree_options.upstream_depth = options_.ancestor_depth;
  tree_options.downstream_depth = options_.descendant_depth;
  return tree_options;
}

std::string GraphEmitter::RelationshipString(
    const RelationshipType& relationship) const {
  switch (relationship) {
    case RelationshipType::SELF: return "self";
    case RelationshipType::PARENT: return "parent";
    case RelationshipType::GRANDPARENT: return "grandparent";
    case RelationshipType::SIBLING: return "sibling";
    case RelationshipType::HALF_SIBLING: return "half-sibling";
    case RelationshipType::CHILD: return "child";
    case RelationshipType::GRANDCHILD: return "grandchild";
    case RelationshipType::OTHER: return "";
    // There is no default, so all enum values must be handled.
  }
}

}  // namespace family_tree

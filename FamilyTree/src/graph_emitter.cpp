#include "graph_emitter.h"

#include <iostream>  // TODO(nloomis): for debug messages
#include <sstream>
#include <string>

#include "tree_builder.h"

namespace {

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

void GraphEmitter::Emit(const NodeMap& nodes, const std::vector<TreeEdge>& edges, std::ostream& output_stream) const {
  // Start the graph.
  output_stream << "graph {\n";

  std::cout << "Emitting graph with " << nodes.size() << " nodes and " << 
    edges.size() << " edges\n";

  // TODO(nloomis): {rank=same; node1 node2 node3;}

  for (const auto& kv : nodes) {
    output_stream << UniqueNodeIdString(kv.first);
    if (kv.second.node_type == TreeNodeType::INDIVIDUAL) {
      output_stream << " [shape=box, label=\"" << kv.second.name_label;
      const std::string& relationship_string = RelationshipString(kv.second.relationship);
      if (!relationship_string.empty()) {
        output_stream << "\n" << relationship_string;
      }
      output_stream << "\", ";
      if (kv.second.relationship == RelationshipType::SELF) {
        output_stream << "style=\"bold, filled\", fillcolor=" <<
          options_.reference_individual_background_color;
      } else {
        output_stream << "style=filled, fillcolor=" <<
          options_.default_individual_background_color;
      }
      output_stream << "];\n";
      // TODO(nloomis): highlight the root individual
    } else {
      // offspring node.
      output_stream << "[shape=circle, style=filled, label=\"\", height=0.1, width=0.1];\n";
    }
  }

  for (const TreeEdge& edge : edges) {
    output_stream << UniqueNodeIdString(edge.first) << "--" << UniqueNodeIdString(edge.second) << ";\n";
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

std::string GraphEmitter::RelationshipString(const RelationshipType& relationship) const {
  switch (relationship) {
    case RelationshipType::SELF: return "self";
    case RelationshipType::PARENT: return "parent";
    case RelationshipType::GRANDPARENT: return "grandparent";
    case RelationshipType::SIBLING: return "sibling";
    case RelationshipType::HALF_SIBLING: return "half-sibling";
    case RelationshipType::CHILD: return "child";
    case RelationshipType::GRANDCHILD: return "grandchild";
    case RelationshipType::OTHER: return "";
  }
}

}  // namespace family_tree

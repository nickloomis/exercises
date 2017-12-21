#include "tree_builder.h"

#include <algorithm>
#include <list>
#include <iostream>

namespace family_tree {

TreeBuilder::TreeBuilder(const Person* initial_person,
                         const TreeBuilderOptions& options)
    : options_(options),
      relationship_(initial_person) {
  // Start the tracing from the initial_person.
  upstream_to_trace_.emplace(initial_person, 0);
  downstream_to_trace_.emplace(initial_person, 0);

  // Build the tree.
  while (!IsDone()) {
    TraceNext();
  }
}

bool TreeBuilder::IsDone() const {
  return upstream_to_trace_.empty() && downstream_to_trace_.empty();
}

void TreeBuilder::TraceNext() {
  if (!upstream_to_trace_.empty()) {
    TraceNextUpstream();
  } else {
    TraceNextDownstream();
  }
}

void TreeBuilder::TraceNextUpstream() {
  const Traceable traceable = upstream_to_trace_.top();
  upstream_to_trace_.pop();

  tree_.AddIndividualNode(traceable.person,
                          TreeNode(traceable.person->name(),
                                   relationship_.Label(traceable.person),
                                   traceable.generation));

  if (traceable.generation <= -options_.upstream_depth) {
    return;
  }

  downstream_to_trace_.emplace(traceable.person, traceable.generation);

  const std::list<Person*>& parents = traceable.person->parents();
  if (!parents.empty()) {
    NodeMapKey offspring_key = tree_.GetNodeMapKey(parents);
    tree_.AddTreeEdge(offspring_key, tree_.GetNodeMapKey(traceable.person));

    // Add an offspring node for these parents if it doesn't aleady exist.
    if (tree_.AddOffspringNode(parents, traceable.generation - 1)) {
      for (const Person* parent : parents) {
        tree_.AddTreeEdge(tree_.GetNodeMapKey(parent), offspring_key);
      }
    }

    for (const Person* parent : parents) {
      if (!tree_.NodeExists(parent)) {
        upstream_to_trace_.emplace(parent, traceable.generation - 1);
        downstream_to_trace_.emplace(parent, traceable.generation - 1);
      }
    }
  }
}

void TreeBuilder::TraceNextDownstream() {
  Traceable traceable = downstream_to_trace_.top();
  downstream_to_trace_.pop();
  const std::list<Person*> descendants = traceable.person->descendants();
  if (traceable.generation >= options_.downstream_depth) {
    return;
  }
  if (descendants.empty()) {
    return;
  }
  for (Person* descendant : descendants) {
    if (!tree_.NodeExists(descendant)) {
      upstream_to_trace_.emplace(descendant, traceable.generation + 1);
    }
  }
}

}  // namespace family_tree

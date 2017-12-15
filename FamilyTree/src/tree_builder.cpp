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
  // upstream_to_trace_.push(initial_person);
  // downstream_to_trace_.push(initial_person);
  upstream_to_trace_.emplace_back(initial_person, 0);
  downstream_to_trace_.emplace_back(initial_person, 0);
  PrintStacks();  // TODO(nloomis): remove, debug only

  // Build the tree.
  while (!IsDone()) {
    TraceNext();
  }
}

void TreeBuilder::PrintStacks() const {
  std::cout << "up-todo: ";
  for (const Traceable& traceable : upstream_to_trace_) {
    std::cout << traceable.person->name() << "  ";
  }
  std::cout << "\ndown-todo: ";
  for (const Traceable& traceable : downstream_to_trace_) {
    std::cout << traceable.person->name() << "  ";
  }
  std::cout << "\n";
}

bool TreeBuilder::IsDone() const {
  return upstream_to_trace_.empty() && downstream_to_trace_.empty();
}

void TreeBuilder::TraceNext() {
  if (!upstream_to_trace_.empty()) {
    std::cout << "Tracing next UPSTREAM...\n";
    TraceNextUpstream();
  } else {
    std::cout << "Tracing next DOWNSTREAM...\n";
    TraceNextDownstream();
  }
  PrintStacks();
  std::cout << "...tracing round done.\n\n";
}

void TreeBuilder::TraceNextUpstream() {
//  Person* const person = upstream_to_trace_.top();
  Traceable traceable = upstream_to_trace_.back();
  //  upstream_to_trace_.pop();
  upstream_to_trace_.pop_back();

  std::cout << "Next upstream is " << traceable.person->name() << "\n";
  if (!NodeExists(traceable.person)) {
    // Add a node for the person.
    std::cout << "Adding a node for " << traceable.person->name() <<
     " (" << traceable.person << ")\n";
    std::cout << " generation: " << traceable.generation << "\n";
    nodes_.emplace(NodeKey(traceable.person), TreeNode(traceable.person->name(),
                   relationship_.Label(traceable.person), traceable.generation));
  } else {
    std::cout << "Node for " << traceable.person->name() << " (" <<
     traceable.person << ") exists already\n";
  }

  if (traceable.generation <= -options_.upstream_depth) {
    return;
  }

  std::cout << " adding " << traceable.person->name() << "to down-todo\n";
  downstream_to_trace_.emplace_back(traceable.person, traceable.generation);

  const std::list<Person*>& parents = traceable.person->parents();
  if (!parents.empty()) {
    NodeMapKey offspring_key = NodeKey(parents);
    AddTreeEdge(offspring_key, NodeKey(traceable.person));

    // Add an offspring node for these parents if it doesn't aleady exist.
    if (!NodeExists(parents)) {
      std::cout << " adding offspring node\n";
      nodes_.emplace(offspring_key, TreeNode::OffspringNode(traceable.generation - 1));
      for (const Person* parent : parents) {
        AddTreeEdge(NodeKey(parent), offspring_key);
      }
    }

    for (const Person* parent : parents) {
      if (!NodeExists(parent)) {
        std::cout << " adding " << parent->name() << " to up-todo\n";
        upstream_to_trace_.emplace_back(parent, traceable.generation - 1);
        std::cout << " adding " << parent->name() << " to down-todo\n";
        // TODO(nloomis): was traceable.generation + 1
        downstream_to_trace_.emplace_back(parent, traceable.generation - 1);
      }
    }
  } else {
    std::cout << " node " << traceable.person->name() << " has no parents\n";
  }
}

void TreeBuilder::TraceNextDownstream() {
  // Person* person = downstream_to_trace_.top();
  Traceable traceable = downstream_to_trace_.back();
  //  downstream_to_trace_.pop();
  downstream_to_trace_.pop_back();
  std::cout << "Next downstream is " << traceable.person->name() << "\n";
  const std::list<Person*> descendants = traceable.person->descendants();
  std::cout << " and has " << descendants.size() << " descendants\n";
  if (traceable.generation >= options_.downstream_depth) {
    std::cout << " reached downstream depth limit; not adding descendants";
    return;
  }
  if (descendants.empty()) {
    return;
  }
  for (Person* descendant : descendants) {
    if (!NodeExists(descendant)) {
//      upstream_to_trace_.push(descendant);
      std::cout << " adding descendant " << descendant->name() << " to up-todo\n";
      upstream_to_trace_.emplace_back(descendant, traceable.generation + 1);
    }
  }
  std::cout << " exiting TraceNextDownstream()\n";
}

const NodeMapKey TreeBuilder::NodeKey(const Person* person) const {
  return std::make_pair(person, person);
}

const NodeMapKey TreeBuilder::NodeKey(const std::list<Person*>& parents) const {
  if (parents.empty()) {
    return std::make_pair(nullptr, nullptr);
  } else if (parents.size() == 1) {
    return std::make_pair(nullptr, parents.front());
  }
  return std::make_pair(std::min(parents.front(), parents.back()), 
                        std::max(parents.front(), parents.back()));
}

bool TreeBuilder::NodeExists(const Person* person) const {
  return nodes_.find(NodeKey(person)) != nodes_.end();
}

bool TreeBuilder::NodeExists(const std::list<Person*>& parents) const {
  return nodes_.find(NodeKey(parents)) != nodes_.end();
}

void TreeBuilder::AddTreeEdge(const NodeMapKey& node1, const NodeMapKey& node2) {
  edges_.emplace_back(std::make_pair(node1, node2));
}

}  // namespace family_tree
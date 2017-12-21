#include "person.h"

#include <algorithm>

#include "tree_builder.h"

namespace family_tree {

Person::Person(const std::string& name, Person* const parent1,
               Person* const parent2) 
      : name_(name) {
  if (parent1) {
    parents_.push_back(parent1);
    parent1->AddDescendant(this);
  }
  if (parent2) {
    parents_.push_back(parent2);
    parent2->AddDescendant(this);
  }
}

void Person::GetFamilyTree(const GraphEmitter& grapher,
                           std::ostream& output_stream)
 const {
  // TreeBuilder is a factory class, and builds the tree during its
  // construction.
  TreeBuilder tree_builder(this, grapher.TreeOptions());
  grapher.Emit(tree_builder.tree(), output_stream);
}

void Person::AddDescendant(Person* const descendant) {
  if (std::find(descendants_.begin(), descendants_.end(), descendant) ==
      descendants_.end()) {
    descendants_.push_back(descendant);
  }
}

}  // namespace family_tree

#include "person.h"

#include <algorithm>

#include "tree_builder.h"

namespace family_tree {

Person::Person(const std::string& name, Person* const parent1,
               Person* const parent2) 
      : name_(name),
        spouse_(nullptr) {
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

bool Person::Marry(Person* const partner) {
  // Check that both individuals are able to enter into a new spousal relation.
  if (spouse_ || spouse_->spouse()) {
    return false;
  }
  SetSpouse(partner);
  partner->SetSpouse(this);
  return true;
}

void Person::Divorce() {
  if (spouse_) {
    spouse_->SetSpouse(nullptr);
    spouse_ = nullptr;
  }
}

void Person::AddDescendant(Person* const descendant) {
  if (std::find(descendants_.begin(), descendants_.end(), descendant) ==
      descendants_.end()) {
    descendants_.push_back(descendant);
  }
}

}  // namespace family_tree

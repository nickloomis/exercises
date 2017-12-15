#include "person.h"
#include "tree_builder.h"

#include <algorithm>
#include <iostream>

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

void Person::PrintRelations() const {
  std::cout << name() << " has the following relationships: " << std::endl;
  for (const Person* parent : parents_) {
    std::cout << "  parent is " << parent->name() << std::endl;
  }
  for (const Person* descendant : descendants_) {
    std::cout << "  descendant is " << descendant->name() << std::endl;
  }
}

void Person::GetFamilyTree(GraphEmitter* grapher, std::ostream& output_stream) const {
  TreeBuilder tree_builder(this, grapher->TreeOptions());
  grapher->Emit(tree_builder.nodes(), tree_builder.edges(), output_stream);
  // TODO(nloomis): return something useful.
}

void Person::AddDescendant(Person* const descendant) {
  if (std::find(descendants_.begin(), descendants_.end(), descendant) ==
      descendants_.end()) {
    std::cout << "Descendant " << descendant->name() << " being added to " << name_ << "\n";
    descendants_.push_back(descendant);
  } else {
    std::cout << "Descendant " << descendant->name() << " is already listed by " << name_ << "\n";
  }
}

}  // namespace family_tree

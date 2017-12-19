#include "relationship_labeler.h"

#include <algorithm>
#include <iostream>
#include <utility>

namespace family_tree {

RelationshipLabeler::RelationshipLabeler(const Person* person) 
    : parents_of_reference_(person->parents()) {
  // TODO(nloomis): note about why the const_cast is being used, and is OK
  direct_relations_.emplace(std::make_pair(const_cast<Person*>(person), RelationshipType::SELF));

  for (Person* parent : person->parents()) {
    // Record the parents.
    direct_relations_.emplace(std::make_pair(parent, RelationshipType::PARENT));

    // Record the grandparents (parents of parents).
    for (Person* grandparent : parent->parents()) {
      direct_relations_.emplace(std::make_pair(grandparent,
                                               RelationshipType::GRANDPARENT));
    }

    // Record siblings (all descendants of the reference individual's parents).
    for (Person* sibling : parent->descendants()) {
      if (sibling != person) {
        direct_relations_.emplace(std::make_pair(sibling,
                                                 SiblingLabel(sibling)));
      }
    }
  }

  // Record children and grandchildren.
  for (Person* child : person->descendants()) {
    direct_relations_.emplace(std::make_pair(child, RelationshipType::CHILD));
    for (Person* grandchild : child->descendants()) {
      direct_relations_.emplace(std::make_pair(grandchild, RelationshipType::GRANDCHILD));
    }
  }

}

RelationshipType RelationshipLabeler::Label(const Person* person) const {
  auto relation_it = direct_relations_.find(const_cast<Person*>(person));
  if (relation_it != direct_relations_.end()) {
    return relation_it->second;
  }
  return RelationshipType::OTHER;
}

RelationshipType RelationshipLabeler::SiblingLabel(Person* other_person) const {
  int number_of_shared_parents = 0;
  const std::list<Person*> other_parents = other_person->parents();
  // parents_of_reference_ has a length of two or less, and optimized algorithms
  // don't have a benefit over a simple std::find(). For simplicity, just use
  // find() and count the overlaps between the two lists of parents.
  for (Person* other_parent : other_parents) {
    if (std::find(parents_of_reference_.begin(),
                  parents_of_reference_.end(),
                  other_parent) != parents_of_reference_.end()) {
      ++number_of_shared_parents;
    }
  }
  if (number_of_shared_parents == other_parents.size() &&
      other_parents.size() == parents_of_reference_.size()) {
    return RelationshipType::SIBLING;
  }
  return RelationshipType::HALF_SIBLING;
}

}  // namespace family_tree

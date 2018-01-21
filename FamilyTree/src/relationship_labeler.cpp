#include "relationship_labeler.h"

#include <algorithm>
#include <utility>

namespace family_tree {

RelationshipLabeler::RelationshipLabeler(const Person* person) 
    : parents_of_reference_(person->parents()) {
  // The const_cast<> is because the map expects move-copy objects.
  direct_relations_.emplace(std::make_pair(const_cast<Person*>(person),
                                           RelationshipType::SELF));

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
      direct_relations_.emplace(std::make_pair(grandchild,
                                               RelationshipType::GRANDCHILD));
    }
  }

  // Check for any step-siblings. Note that any full or half siblings will have
  // already been identified based on inheritance only. Any additional siblings
  // discovered based on the parents' spousal relationship must then be step
  // siblings.
  std::cout << "Person " << person->name() << " has " << person->parents().size() << " parents\n";
  for (Person* parent : person->parents()) {
    Person* spouse = const_cast<Person*>(parent->spouse());
    if (spouse) {
      // If the spouse is not a biological parent, add them as a step-parent.
      auto it_step = direct_relations_.find(spouse);
      if (it_step == direct_relations_.end()) {
        direct_relations_.emplace(
          std::make_pair(spouse, RelationshipType::STEP_PARENT));
      }

      // Find the children of the parents' spouses.
      for (Person* child : spouse->descendants()) {
        auto it = direct_relations_.find(child);
        if (it == direct_relations_.end()) {
          // Add the relation if it is not already known as a different sibling.
          direct_relations_.emplace(
            std::make_pair(child, RelationshipType::STEP_SIBLING));
        }
      }
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

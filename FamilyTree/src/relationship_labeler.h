#ifndef FAMILY_TREE_RELATIONSHIP_LABELER_H_
#define FAMILY_TREE_RELATIONSHIP_LABELER_H_

#include <unordered_map>
#include <string>

#include "person.h"
#include "relationship_type.h"

namespace family_tree {

class RelationshipLabeler {
 public:
  // Relationships are relative to a reference individual: eg, "parent of...", 
  // "sibling of...", "child of...", etc. The pointers are expected to be const
  // during the lifetime of the RelationshipLabler object. The pointed Persons
  // are also not expected to change their parent or descendant member data
  // during the lifetime of the RelationshipLabeler.
  RelationshipLabeler(const Person* reference_individual);

  // Returns the RelationshipType which describes the relationship between the
  // person and the reference_inidividual set during construction.
  RelationshipType Label(const Person* person) const;

 private:
  // Returns RelationshipType::SIBLING or RelationshipType::HALF_SIBLING. The
  // sibling label is returned if the other_person and the reference_individual
  // (set during construction) share all of the same parents. A half-sibling has
  // only one of the two parents in common. If both people have only one parent,
  // they are considered siblings since half-relations can't be determined.
  // 
  // The function is expected to be called ONLY for other_person's who are known
  // to be some sort of sibling to the reference_individual. (If not, the result
  // is erroneous.) The easiest way to guarantee this condition is to call the
  // function only for the descendants of the reference_individual's parents.
  // The caller should also avoid using the reference_individual as an input to
  // SiblingLabel.
  //
  // Note: the fragile nature of SiblingLabel is OK here because it is called in
  // a tightly controlled manner during object construction. Checks for "self"
  // no shared parents would make it more robust if the function were promoted
  // to public.
  RelationshipType SiblingLabel (Person* other_person) const;

  // Store a map of all known direct relationships to the reference individual.
  std::unordered_map<Person*, RelationshipType> direct_relations_;

  // Parents of the reference individual.
  const std::list<Person*>& parents_of_reference_;
};

}  // namespace family_tree

#endif  // FAMILY_TREE_RELATIONSHIP_LABELER_H_

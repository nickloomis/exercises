#ifndef FAMILY_TREE_RELATIONSHIP_LABELER_H_
#define FAMILY_TREE_RELATIONSHIP_LABELER_H_

#include <unordered_map>
#include <string>

#include "person.h"
#include "relationship_type.h"

namespace family_tree {

class RelationshipLabeler {
 public:
  RelationshipLabeler(const Person* reference_individual);

  RelationshipType Label(const Person* person) const;

  // void PrintNamedRelationships() const;

 private:

// note: only call when other_person is known to be some type of sibling of the
  // reference individual (otherwise, may get wrong results. easy to fix in
  // implementation, though!)
  // "sibling" is used for two shared parents, or if half-sibling can't be determined for sure (eg, only one parent is known)
  RelationshipType SiblingLabel (Person* other_person) const;

  std::unordered_map<Person*, RelationshipType> direct_relations_;
  const std::list<Person*>& parents_of_reference_;
};

}  // namespace family_tree

#endif  // FAMILY_TREE_RELATIONSHIP_LABELER_H_

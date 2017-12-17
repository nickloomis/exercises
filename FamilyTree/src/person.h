#ifndef FAMILY_TREE_PERSON_H_
#define FAMILY_TREE_PERSON_H_

#include <list>
#include <ostream>
#include <string>

#include "graph_emitter.h"

namespace family_tree {

class Person {
 public:
  // The c'tor takes the name of the individual and pointers to the person's
  // biological parents. The pointers are expected to be constant during the
  // lifetime of the Person. One or both pointers may be a nullptr, signifying
  // that the parent is not known or is not important. The Person is added to
  // each parent's list of descendants.
  //
  // Note: the parents could be made mutable. The Person might need to be
  // removed from the outgoing parent's descendants_ list in that case.
  Person(const std::string& name, Person* const parent1, Person* const parent2);

  // TODO(nloomis): debugging.
  void PrintRelations() const;
		
  // Accessors.
  const std::string& name() const { return name_; }
  const std::list<Person*>& parents() const { return parents_; }
  const std::list<Person*>& descendants() const { return descendants_; }

  // Causes a family tree to be built using this Person as the root individual.
  // All relationships and generations are relative to this Person.
  void GetFamilyTree(GraphEmitter* grapher, std::ostream& output_stream) const;

 private:
  // Adds a child to the list of descendants_.
  void AddDescendant(Person* const);

  // Name of the person.
  const std::string name_;

  // All known parents for the person; may have 0, 1, or 2 entries. The pointers
  // are expected to be constant.
  std::list<Person*> parents_;

  // List of this person's children, eg, people claiming this person as their
  // parent. The pointers are expected to be constant.
  std::list<Person*> descendants_;
};

}  // namespace family_tree

#endif  // FAMILY_TREE_PERSON_H_

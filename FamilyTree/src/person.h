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
		
  // Accessors.
  const std::string& name() const { return name_; }
  const std::list<Person*>& parents() const { return parents_; }
  const std::list<Person*>& descendants() const { return descendants_; }
  const Person* spouse() const { return spouse_; }

  // Causes a family tree to be built using this Person as the root individual.
  // All relationships and generations are relative to this Person.
  void GetFamilyTree(const GraphEmitter& grapher,
                     std::ostream& output_stream) const;
  // Note: if there are multiple ways to emit graphs, we have two options:
  //  1) make GraphEmitter a base class, and implement the emission mechanisms
  //     in a derived class, or
  //  2) make GraphEmitter an interface and pass emission mechanisms to its
  //     constructor.
  // Method 2 (via composition) is my preferred approach. 

  // Associates this person and the partner as spouses to each other. If both
  // people are unmarried, returns true. If either is currently married and a
  // new marriage is thus not possible, returns false. Marry() only needs to be
  // called for one person in the spousal relationship.
  bool Marry(Person* const partner);

  // Removes the spousal relationship for this person and the spouse. Divorce()
  // only needs to be called for one person in the spousal relationship.
  void Divorce();

 private:
  // Adds a child to the list of descendants.
  void AddDescendant(Person* const);

  // Assigns the current spouse.
  void SetSpouse(Person* const partner) { spouse_ = partner; }

  // Name of the person.
  const std::string name_;

  // All known parents for the person; may have 0, 1, or 2 entries. The pointers
  // are expected to be constant.
  std::list<Person*> parents_;

  // List of this person's children, eg, people claiming this person as their
  // parent. The pointers are expected to be constant.
  std::list<Person*> descendants_;

  // Pointer to the current spouse. A nullptr signifies that no spouse is known,
  // or that the spousal relationship is not explicitly recorded.
  Person* spouse_ = nullptr;
};

}  // namespace family_tree

#endif  // FAMILY_TREE_PERSON_H_

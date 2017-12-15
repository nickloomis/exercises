#ifndef FAMILY_TREE_PERSON_H_
#define FAMILY_TREE_PERSON_H_

#include <list>
#include <ostream>
#include <string>

#include "graph_emitter.h"

namespace family_tree {

class Person {
 public:
  Person(const std::string& name, Person* const parent1, Person* const parent2);

  void PrintRelations() const;
		
  const std::string& name() const { return name_; }

  const std::list<Person*>& parents() const { return parents_; }

  const std::list<Person*>& descendants() const { return descendants_; }

  void GetFamilyTree(GraphEmitter* grapher, std::ostream& output_stream) const;

	// Adds the spouse and returns true if the person is not already listed;
	// returns false if they have already been listed as a spouse.
	// bool AddSpouse(const Person* spouse);

 private:
  void AddDescendant(Person* const);

  const std::string name_;
  std::list<Person*> parents_;
  // std::forward_list<Person* const> spouses_;
  std::list<Person*> descendants_;
};

}  // namespace family_tree

#endif  // FAMILY_TREE_PERSON_H_

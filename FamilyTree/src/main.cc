#include <iostream>
#include <fstream>

#include "person.h"
#include "graph_emitter.h"

int main() {
	family_tree::Person person_adad("Alice's dad", nullptr, nullptr);
	family_tree::Person person_amom("Alice's mom", nullptr, nullptr);
  family_tree::Person person_a("Alice", &person_adad, &person_amom);
  family_tree::Person person_bdad("Bob's dad", nullptr, nullptr);
  family_tree::Person person_egads("Egads", nullptr, nullptr);
  family_tree::Person person_gertie("Gertie", nullptr, nullptr);
  family_tree::Person person_bgdad("Bob's grandpa", &person_egads, &person_gertie);
  family_tree::Person person_bgmom("Bob's grandma", nullptr, nullptr);
  family_tree::Person person_bmom("Bob's mom", &person_bgmom, &person_bgdad);
  family_tree::Person person_b("Bob", &person_bmom, &person_bdad);
  family_tree::Person person_c("Charlie", &person_a, &person_b);
  family_tree::Person person_csis("Candice", &person_a, &person_b);
  family_tree::Person person_cbro("Chuck", &person_a, &person_b);
  family_tree::Person person_cdad("Carl's dad", nullptr, nullptr);
  family_tree::Person person_carl("Carl", &person_a, &person_cdad);
  family_tree::Person person_c1("David", &person_c, nullptr);
  family_tree::Person person_c2("Erin", &person_c1, nullptr);
  family_tree::Person person_c3("Frank", &person_c2, nullptr);
  family_tree::Person person_c4("Griff", &person_c3, nullptr);
  //std::cout << "Hello world!" << std::endl;
		
/*  person_a.PrintRelations();
  person_b.PrintRelations();
  person_c.PrintRelations();

  RelationshipName relationships(&person_c);
  relationships.PrintNamedRelationships();

  TreeBuilderOptions options;
  options.downstream_depth = 2;
  TreeBuilder tree_builder(&person_c, options);
  tree_builder.Build();
*/

  family_tree::GraphEmitterOptions options;
  options.ancestor_depth = 1;  // TODO(nloomis): debug the depth!
  options.descendant_depth = 3;
  family_tree::GraphEmitter grapher(options);
  std::ofstream graph_file("test_graph.gv");
  person_c.GetFamilyTree(&grapher, graph_file);

  // tree_builder.GraphString();

  return 0;
}

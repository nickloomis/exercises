#include <iostream>
#include <fstream>

#include "person.h"
#include "graph_emitter.h"

int main() {
  // British royal family, from http://www.bbc.com/news/uk-23272491
  family_tree::Person p_qe2("Queen Elizabeth II", nullptr, nullptr);
  family_tree::Person p_philip("Phillip", nullptr, nullptr);
  family_tree::Person p_charles("Prince Charles", &p_qe2, &p_philip);
  family_tree::Person p_diana("Princess Diana", nullptr, nullptr);
  family_tree::Person p_william("William", &p_diana, &p_charles);
  family_tree::Person p_kate("Kate", nullptr, nullptr);
  family_tree::Person p_george("Prince George", &p_william, &p_kate);
  family_tree::Person p_charlotte("Princess Charlotte", &p_william, &p_kate);
  family_tree::Person p_harry("Prince Harry", &p_diana, &p_charles);
  family_tree::Person p_anne("Princess Anne", &p_qe2, &p_philip);
  family_tree::Person p_mark("Mark Phillips", nullptr, nullptr);
  family_tree::Person p_peter("Peter Phillips", &p_anne, &p_mark);
  family_tree::Person p_zara("Zara Tindall", &p_anne, &p_mark);
  family_tree::Person p_autumn("Autumn Phillips", nullptr, nullptr);
  family_tree::Person p_savannah("Savannah", &p_peter, &p_autumn);
  family_tree::Person p_isla("Isla", &p_peter, &p_autumn);
  family_tree::Person p_mike("Mike Tindall", nullptr, nullptr);
  family_tree::Person p_mia("Mia Grace", &p_zara, &p_mike);
  family_tree::Person p_andrew("Andrew", &p_qe2, &p_philip);
  family_tree::Person p_sarah("Sarah", nullptr, nullptr);
  family_tree::Person p_beatrice("Princess Beatrice", &p_andrew, &p_sarah);
  family_tree::Person p_eugenie("Princess Eugenie", &p_andrew, &p_sarah);
  family_tree::Person p_edward("Edward", &p_qe2, &p_philip);
  family_tree::Person p_sophie("Sophie", nullptr, nullptr);
  family_tree::Person p_louise("Louise", &p_edward, &p_sophie);
  family_tree::Person p_james("James", &p_edward, &p_sophie);


/*	family_tree::Person person_adad("Alice's dad", nullptr, nullptr);
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
*/
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
  //options.ancestor_depth = 1;  // TODO(nloomis): debug the depth!
  //options.descendant_depth = 3;
  family_tree::GraphEmitter grapher(options);
  std::ofstream graph_file("qe2_graph.gv");
  //person_c.GetFamilyTree(&grapher, graph_file);

  p_qe2.GetFamilyTree(&grapher, graph_file);

  std::ofstream harry_graph("harry_graph.gv");
  p_harry.GetFamilyTree(&grapher, harry_graph);

  // tree_builder.GraphString();

  return 0;
}

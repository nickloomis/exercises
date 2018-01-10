#include <iostream>
#include <fstream>

#include "person.h"
#include "graph_emitter.h"

int main() {
  /*
  // Create an example family tree for a large family: the British royal family;
  // from http://www.bbc.com/news/uk-23272491 and other sources.
  // Note: these objects are created verbosely as an example. In the real world,
  // they might stem from a file, be dynamically populated (eg, a search query
  // result), or otherwise be input by the user. The one requirement is that the
  // pointers to the objects remain constant during runtime. (Be careful not
  // to store Person objects in a vector, for example, as it may change the
  // pointers to each object as new objects are added.
  family_tree::Person p_george5("George V", nullptr, nullptr);
  family_tree::Person p_mary("Mary", nullptr, nullptr);
  family_tree::Person p_george6("George VI", &p_george5, &p_mary);
  family_tree::Person p_elizabeth1("Elizabeth", nullptr, nullptr);
  family_tree::Person p_qe2("Queen Elizabeth II", &p_george6, &p_elizabeth1);
  family_tree::Person p_philip("Phillip", nullptr, nullptr);
  family_tree::Person p_charles("Prince Charles", &p_qe2, &p_philip);
  family_tree::Person p_diana("Princess Diana", nullptr, nullptr);
  family_tree::Person p_william("Prince William", &p_diana, &p_charles);
  family_tree::Person p_kate("Kate", nullptr, nullptr);
  family_tree::Person p_george("Prince George", &p_william, &p_kate);
  family_tree::Person p_charlotte("Princess Charlotte", &p_william, &p_kate);
  family_tree::Person p_harry("Prince Harry", &p_diana, &p_charles);
  family_tree::Person p_anne("Princess Anne", &p_qe2, &p_philip);
  family_tree::Person p_mark("Mark Phillips", nullptr, nullptr);
  family_tree::Person p_peter("Peter Phillips", &p_anne, &p_mark);
  family_tree::Person p_zara("Zara Tindall", &p_anne, &p_mark);
  family_tree::Person p_autumn("Autumn Phillips", nullptr, nullptr);
  family_tree::Person p_savannah("Savannah Phillips", &p_peter, &p_autumn);
  family_tree::Person p_isla("Isla", &p_peter, &p_autumn);
  family_tree::Person p_mike("Mike Tindall", nullptr, nullptr);
  family_tree::Person p_mia("Mia Grace", &p_zara, &p_mike);
  family_tree::Person p_andrew("Prince Andrew", &p_qe2, &p_philip);
  family_tree::Person p_sarah("Sarah Ferguson", nullptr, nullptr);
  family_tree::Person p_beatrice("Princess Beatrice", &p_andrew, &p_sarah);
  family_tree::Person p_eugenie("Princess Eugenie", &p_andrew, &p_sarah);
  family_tree::Person p_edward("Prince Edward", &p_qe2, &p_philip);
  family_tree::Person p_sophie("Sophie Rhys-Jones", nullptr, nullptr);
  family_tree::Person p_louise("Louise", &p_edward, &p_sophie);
  family_tree::Person p_james("James", &p_edward, &p_sophie);
  family_tree::Person p_margaret("Margaret", &p_george6, &p_elizabeth1);
  family_tree::Person p_anthony("Anthony Armstrong-Jones", nullptr, nullptr);
  family_tree::Person p_david("David Armstrong-Jones", &p_margaret, &p_anthony);
  family_tree::Person p_edward8("Edward VIII", &p_george5, &p_mary);
  family_tree::Person p_princessmary("Princess Mary", &p_george5, &p_mary);
  family_tree::Person p_john("Prince John", &p_george5, &p_mary);
  family_tree::Person p_henry("Prince Henry", &p_george5, &p_mary);
  family_tree::Person p_georgekent("Prince George", &p_george5, &p_mary);
  family_tree::Person p_alice("Alice Montegu", nullptr, nullptr);
  family_tree::Person p_richard("Richard", &p_henry, &p_alice);
  family_tree::Person p_marina("Princess Marina", nullptr, nullptr);
  family_tree::Person p_edwardkent("Edward", &p_georgekent, &p_marina);
  family_tree::Person p_alexandra("Princess Alexandra", &p_georgekent,
                                  &p_marina);
  family_tree::Person p_michael("Prince Michael", &p_georgekent, &p_marina);

  family_tree::GraphEmitterOptions options;
  family_tree::GraphEmitter grapher(options);
  std::ofstream graph_file("qe2_graph.gv");
  p_qe2.GetFamilyTree(grapher, graph_file);

  options.ancestor_depth = 0;
  options.descendant_depth = 3;
  grapher = family_tree::GraphEmitter(options);
  std::ofstream short_graph_file("qe2_short.gv");
  p_qe2.GetFamilyTree(grapher, short_graph_file);

  std::ofstream harry_graph("harry_graph.gv");
  options.ancestor_depth = 2;
  grapher = family_tree::GraphEmitter(options);
  p_harry.GetFamilyTree(grapher, harry_graph);

 */

  // Half- and step-siblings example
  family_tree::Person p_a("A", nullptr, nullptr);
  family_tree::Person p_b("B", nullptr, nullptr);
  family_tree::Person p_c("C", &p_a, &p_b);
  family_tree::Person p_d("D", &p_a, &p_b);
  family_tree::Person p_f("F", nullptr, nullptr);
  family_tree::Person p_g("G", &p_a, &p_f);
  family_tree::Person p_h("H", &p_a, &p_f);
  family_tree::Person p_l("L", nullptr, nullptr);
  family_tree::Person p_m("M", &p_f, &p_l);

  family_tree::GraphEmitter grapher(family_tree::GraphEmitterOptions());
  std::ofstream step_file("step_siblings.gv");
  p_g.GetFamilyTree(grapher, step_file);

  return 0;
}

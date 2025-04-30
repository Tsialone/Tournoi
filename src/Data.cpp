#include "Data.hpp"
#include "Input.hpp"
#include "Groupe.hpp"

std::vector<Input *> Data::curent_inputs = {};
std::vector<Groupe> Data::current_groupe = {};
std::vector<wxStaticText *> Data::current_trie_phase = {};

int Data::idPhase = 1;

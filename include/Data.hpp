#ifndef DATA_HPP
#define DATA_HPP

#include <vector>
#include "Input.hpp"
#include "Groupe.hpp"


class Data {
public:
    static std::vector<Input*> curent_inputs;
    static int idPhase ;
    static std::vector<Groupe>  current_groupe;
    static std::vector<wxStaticText*>  current_trie_phase;
};

#endif

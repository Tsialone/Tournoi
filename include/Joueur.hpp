#ifndef Joueur_HPP
#define Joueur_HPP

#include <string>
#include <vector>
#include <json.hpp>

// Déclaration de la classe Joueur
class Joueur {
public:
    // Constructeur
    Joueur(int id = 0, const std::string& name = "");

    int getId() const;
    std::string getName() const;

    static std::vector<Joueur> getAll(); 
    static  Joueur getById(int id); 
    void del(); 
    void save();
    void update(); 

private:
    int id_;
    std::string name_;
};

#endif

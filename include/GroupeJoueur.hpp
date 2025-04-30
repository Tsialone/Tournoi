
#ifndef GroupeJoueur_HPP
#define GroupeJoueur_HPP

#include <string>
#include <vector>
#include <json.hpp>

class GroupeJoueur {
public:
    // Constructeur
    GroupeJoueur(int id , int idJoueur , int idGroupe);

    int getId() const;
    int getIdJoueur() const;
    int getIdGroupe() const;
    
    static std::vector<GroupeJoueur> getAll(); 
    static  GroupeJoueur getById(int id); 
    void del(); 
    void save();
    void update(); 

private:
    int id_;
    int idJoueur_;
    int idGroupe_;
};

#endif

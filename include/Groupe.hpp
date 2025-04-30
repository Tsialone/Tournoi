#ifndef Groupe_HPP
#define Groupe_HPP

#include <string>
#include <vector>
#include "json.hpp"
#include "Joueur.hpp"


// Déclaration de la classe Groupe
class Joueur;
class Groupe {
public:
    // Constructeur
    Groupe(int id,int idVoisin , std::string name);

    int getId() const;
    int getIdVoisin() const;
    std::string getName() const;
    int *  getIdPhase () ;
    
    static std::vector<Groupe> getAll(); 
    static  Groupe getById(int id); 

    std::vector<Joueur> getTwoBest (int idPhase);
    std::vector<Joueur> getBest (int idPhase);


    void setIdVoisin(int idVoisin);

    void del(); 
    void save();
    void update(); 
    Groupe * miteraka (int phaseId);
    Groupe * getVoisin();
    Groupe * getFinaliste();

    std::vector<Joueur> getJoueurs ();

    

private:
    int id_;
    int idVoisin_;
    std::string name_;
};

#endif

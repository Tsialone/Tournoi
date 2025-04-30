#ifndef PhaseGroupe_HPP
#define PhaseGroupe_HPP

#include <string>
#include <vector>
#include <json.hpp>

class PhaseGroupe  {
public:
    // Constructeur
    PhaseGroupe (int id ,int idPhase ,  int idGroupe );

    int getId() const;
    int getIdJoueur() const;
    int getIdPhase() const;
    int getIdGroupe() const;
    
    static std::vector<PhaseGroupe > getAll(); 
    static  PhaseGroupe  getById(int id); 
    void del(); 
    void save();
    void update(); 

private:
    int id_;
    int idPhase_;
    int idGroupe_;
};

#endif

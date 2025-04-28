#ifndef PhaseJoueur_HPP
#define PhaseJoueur_HPP

#include <string>
#include <vector>
#include <json.hpp>

class PhaseJoueur  {
public:
    // Constructeur
    PhaseJoueur (int id , int idJoueur  , int idPhase, std::string temps);

    int getId() const;
    int getIdJoueur() const;
    int getIdPhase() const;
    std::string getTemps() const;
    
    static std::vector<PhaseJoueur > getAll(); 
    static  PhaseJoueur  getById(int id); 
    void del(); 
    void save();
    void update(); 

private:
    int id_;
    int idJoueur_;
    int idPhase_;
    std::string temps_;
};

#endif

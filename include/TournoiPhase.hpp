#ifndef TournoiPhase_HPP
#define TournoiPhase_HPP

#include <string>
#include <vector>
#include <json.hpp>

class TournoiPhase {
public:
    // Constructeur
    TournoiPhase(int id , int idTournoi  , int idPhase);

    int getId() const;
    int getIdTournoi() const;
    int getIdPhase() const;
    
    static std::vector<TournoiPhase> getAll(); 
    static  TournoiPhase getById(int id); 
    void del(); 
    void save();
    void update(); 

private:
    int id_;
    int idTournoi_;
    int idPhase_;
};

#endif

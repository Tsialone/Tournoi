#ifndef JoueurCourse_HPP
#define JoueurCourse_HPP

#include <string>
#include <vector>
#include <json.hpp>

class JoueurCourse  {
public:
    // Constructeur
    JoueurCourse (int id ,int idJoueur ,  int idCourse, int idPhase ,  std::string temps);

    int getId() const;
    int getIdJoueur() const;
    int getIdCourse() const;
    int getIdPhase() const;
    std::string getTemps(); 
    
    static std::vector<JoueurCourse > getAll(); 
    static  JoueurCourse  getById(int id); 
    void del(); 
    void save();
    void update(); 

private:
    int id_;
    int idJoueur_;
    int idCourse_;
    std::string temps_;
    int idPhase_;
};

#endif

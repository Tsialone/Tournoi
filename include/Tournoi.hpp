#ifndef TOURNOIS_HPP
#define TOURNOIS_HPP

#include <string>
#include <vector>
#include <json.hpp>

class Tournoi {
public:
    // Constructeur
    Tournoi(int id = 0, const std::string& name = "");

    int getId() const;
    std::string getName() const;

    static std::vector<Tournoi> getAll(); 
    static  Tournoi getById(int id); 
    void del(); 
    void save();
    void update(); 

private:
    int id_;
    std::string name_;
};

#endif

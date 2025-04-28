#ifndef DEPT_HPP
#define DEPT_HPP

#include <string>
#include <vector>
#include <json.hpp>

// Déclaration de la classe Dept
class Dept {
public:
    // Constructeur
    Dept(int id = 0, const std::string& name = "");

    int getId() const;
    std::string getName() const;

    static std::vector<Dept> getAll(); 
    static  Dept getById(int id); 
    void del(); 
    void save();
    void update(); 

private:
    int id_;
    std::string name_;
};

#endif

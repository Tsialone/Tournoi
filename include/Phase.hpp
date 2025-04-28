#ifndef Phase_HPP
#define Phase_HPP

#include <string>
#include <vector>
#include <json.hpp>

class Phase {
public:
    // Constructeur
    Phase(int id = 0, const std::string& name = "");

    int getId() const;
    std::string getName() const;

    static std::vector<Phase> getAll(); 
    static  Phase getById(int id); 
    void del(); 
    void save();
    void update(); 

private:
    int id_;
    std::string name_;
};

#endif

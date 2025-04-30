#ifndef COURSE_HPP
#define COURSE_HPP

#include <string>
#include <vector>
#include <json.hpp>

// Déclaration de la classe Dept
class Course {
public:
    // Constructeur
    Course(int id = 0, const std::string& name = "");

    int getId() const;
    std::string getName() const;

    static std::vector<Course> getAll(); 
    static  Course getById(int id); 
    void del(); 
    void save();
    void update(); 

private:
    int id_;
    std::string name_;
};

#endif

#include "Course.hpp"
#include <iostream>
#include "UtilDb.hpp"
using namespace std;

// Constructeur
Course::Course(int id, const std::string& name) : id_(id), name_(name) {}

// Getter pour l'id
int Course::getId() const {
    return id_;
}

std::string Course::getName() const {
    return name_;
}

std::vector<Course> Course::getAll() {
    std::vector<Course> departments;

    nlohmann::json data = UtilDb::getData("models");

    if (data.is_array()) {
        for (const auto& CourseData : data[0]["Course"]) {
            int id = CourseData["id"];
            std::string name = CourseData["name"];
            departments.push_back(Course(id, name));
        }
    }

    return departments;
}

Course  Course::getById(int id) {
    nlohmann::json data = UtilDb::getData("models");
    for (const auto& CourseData : data[0]["Course"]) {
        if (CourseData["id"] == id) {
            return Course(CourseData["id"], CourseData["name"]);
        }
    }

    return Course(0, "Not Found");
}

void Course::del() {
    nlohmann::json data = UtilDb::getData("models");

    if (!data.is_array()) {
        std::cerr << "Erreur: Les données ne sont pas un tableau JSON." << std::endl;
        return;
    }

    auto& CourseArray = data[0]["Course"];

    if (!CourseArray.is_array()) {
        std::cerr << "Erreur: 'Course' n'est pas un tableau JSON." << std::endl;
        return;
    }

    auto it = std::remove_if(CourseArray.begin(), CourseArray.end(), [this](const nlohmann::json& Course) {
        return Course["id"] == this->id_;
    });

    if (it != CourseArray.end()) {
        CourseArray.erase(it, CourseArray.end());

        UtilDb::saveData(data);

        std::cout << "Département avec ID " << this->id_ << " supprimé." << std::endl;
    } else {
        std::cerr << "Département avec ID " << this->id_ << " non trouvé !" << std::endl;
    }
}


void Course::save() {
    nlohmann::json data = UtilDb::getData("models");

    nlohmann::json CourseJson = {
        {"id", this->id_},
        {"name", this->name_}
    };
    data[0]["Course"].push_back(CourseJson);
    UtilDb::saveData(data);
}
// Méthode pour mettre à jour un département
void Course::update() {
    nlohmann::json data = UtilDb::getData("models");

    bool updated = false;
    // cout << "taille : " << data.size() << endl;
    for (auto& CourseData : data[0]["Course"]) {
        if (CourseData["id"] == id_) { 
            CourseData["name"] = name_; 
            updated = true;
            break; 
        }
    }

    if (updated) {
        UtilDb::saveData(data );
        std::cout << "Le département a été mis à jour." << std::endl;
    } else {
        std::cout << "Aucun département trouvé avec l'ID : " << id_ << std::endl;
    }
}




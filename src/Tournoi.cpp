#include "Tournoi.hpp"
#include <iostream>
#include "UtilDb.hpp"
using namespace std;

// Constructeur
Tournoi::Tournoi(int id, const std::string& name) : id_(id), name_(name) {}

// Getter pour l'id
int Tournoi::getId() const {
    return id_;
}

std::string Tournoi::getName() const {
    return name_;
}

std::vector<Tournoi> Tournoi::getAll() {
    std::vector<Tournoi> departments;

    nlohmann::json data = UtilDb::getData("models");

    if (data.is_array()) {
        for (const auto& deptData : data[0]["Tournoi"]) {
            int id = deptData["id"];
            std::string name = deptData["name"];
            departments.push_back(Tournoi(id, name));
        }
    }

    return departments;
}

Tournoi  Tournoi::getById(int id) {
    nlohmann::json data = UtilDb::getData("models");
    for (const auto& deptData : data[0]["Tournoi"]) {
        if (deptData["id"] == id) {
            return Tournoi(deptData["id"], deptData["name"]);
        }
    }

    return Tournoi(0, "Not Found");
}

void Tournoi::del() {
    nlohmann::json data = UtilDb::getData("models");

    if (!data.is_array()) {
        std::cerr << "Erreur: Les données ne sont pas un tableau JSON." << std::endl;
        return;
    }

    auto& deptArray = data[0]["Tournoi"];

    if (!deptArray.is_array()) {
        std::cerr << "Erreur: 'dept' n'est pas un tableau JSON." << std::endl;
        return;
    }

    auto it = std::remove_if(deptArray.begin(), deptArray.end(), [this](const nlohmann::json& dept) {
        return dept["id"] == this->id_;
    });

    if (it != deptArray.end()) {
        deptArray.erase(it, deptArray.end());

        UtilDb::saveData(data);

        std::cout << "Département avec ID " << this->id_ << " supprimé." << std::endl;
    } else {
        std::cerr << "Département avec ID " << this->id_ << " non trouvé !" << std::endl;
    }
}


void Tournoi::save() {
    nlohmann::json data = UtilDb::getData("models");

    nlohmann::json deptJson = {
        {"id", this->id_},
        {"name", this->name_}
    };
    data[0]["Tournoi"].push_back(deptJson);
    UtilDb::saveData(data);
}
// Méthode pour mettre à jour un département
void Tournoi::update() {
    nlohmann::json data = UtilDb::getData("models");

    bool updated = false;
    // cout << "taille : " << data.size() << endl;
    for (auto& deptData : data[0]["Tournoi"]) {
        if (deptData["id"] == id_) { 
            deptData["name"] = name_; 
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




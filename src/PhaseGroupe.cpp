#include "PhaseGroupe.hpp"
#include <iostream>
#include "UtilDb.hpp"
using namespace std;

// Constructeur
PhaseGroupe::PhaseGroupe(int id, int idPhase , int idGroupe ) : id_(id), idPhase_(idPhase) , idGroupe_ (idGroupe)  {}

// Getter pour l'id
int PhaseGroupe::getId() const {
    return id_;
}
int PhaseGroupe::getIdGroupe() const {
    return idGroupe_;
}
int PhaseGroupe::getIdPhase() const {
    return idPhase_;
}



std::vector<PhaseGroupe> PhaseGroupe::getAll() {
    std::vector<PhaseGroupe> departments;

    nlohmann::json data = UtilDb::getData("models");

    if (data.is_array()) {
        for (const auto& deptData : data[0]["PhaseGroupe"]) {
            int id = deptData["id"];
            int idPhase = deptData["idPhase"];
            int idGroupe = deptData["idGroupe"];
            departments.push_back(PhaseGroupe(id,   idPhase , idGroupe));
        }
    }

    return departments;
}

PhaseGroupe  PhaseGroupe::getById(int id) {
    nlohmann::json data = UtilDb::getData("models");
    for (const auto& deptData : data[0]["PhaseGroupe"]) {
        if (deptData["id"] == id) {
            int id = deptData["id"];
            int idPhase = deptData["idPhase"];
            int idGroupe = deptData["idGroupe"];
            return PhaseGroupe(id,   idPhase , idGroupe);
        }
    }
    return PhaseGroupe(0, 0 , 0 );
}

void PhaseGroupe::del() {
    nlohmann::json data = UtilDb::getData("models");

    if (!data.is_array()) {
        std::cerr << "Erreur: Les données ne sont pas un tableau JSON." << std::endl;
        return;
    }

    auto& deptArray = data[0]["PhaseGroupe"];

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


void PhaseGroupe::save() {
    nlohmann::json data = UtilDb::getData("models");

    nlohmann::json deptJson = {
        {"id", this->id_},
        {"idPhase", this->idPhase_},
        {"idGroupe", this->idGroupe_}
    };
    data[0]["PhaseGroupe"].push_back(deptJson);
    UtilDb::saveData(data);
}
// Méthode pour mettre à jour un département
void PhaseGroupe::update() {
    nlohmann::json data = UtilDb::getData("models");

    bool updated = false;
    // cout << "taille : " << data.size() << endl;
    for (auto& deptData : data[0]["PhaseGroupe"]) {
        if (deptData["id"] == id_) { 
            deptData["idPhase"] = idPhase_; 
            deptData["idGroupe"] = idGroupe_; 
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




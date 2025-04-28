#include "PhaseJoueur.hpp"
#include <iostream>
#include "UtilDb.hpp"
using namespace std;

// Constructeur
PhaseJoueur::PhaseJoueur(int id, int idJoueur , int idPhase , string temps ) : id_(id), idJoueur_(idJoueur) , idPhase_(idPhase) , temps_ (temps)  {}

// Getter pour l'id
int PhaseJoueur::getId() const {
    return id_;
}
int PhaseJoueur::getIdJoueur() const {
    return idJoueur_;
}
int PhaseJoueur::getIdPhase() const {
    return idPhase_;
}
string PhaseJoueur::getTemps() const {
    return temps_;
}



std::vector<PhaseJoueur> PhaseJoueur::getAll() {
    std::vector<PhaseJoueur> departments;

    nlohmann::json data = UtilDb::getData("models");

    if (data.is_array()) {
        for (const auto& deptData : data[0]["PhaseJoueur"]) {
            int id = deptData["id"];
            int idJoueur = deptData["idJoueur"];
            int idPhase = deptData["idPhase"];
            string temps = deptData["temps"];
            departments.push_back(PhaseJoueur(id, idJoueur , idPhase , temps));
        }
    }

    return departments;
}

PhaseJoueur  PhaseJoueur::getById(int id) {
    nlohmann::json data = UtilDb::getData("models");
    for (const auto& deptData : data[0]["PhaseJoueur"]) {
        if (deptData["id"] == id) {
            int id = deptData["id"];
            int idJoueur = deptData["idJoueur"];
            int idPhase = deptData["idPhase"];
            string temps = deptData["temps"];
            return PhaseJoueur(id, idJoueur , idPhase , temps);
        }
    }
    return PhaseJoueur(0, 0 , 0 , "00:00:00:00");
}

void PhaseJoueur::del() {
    nlohmann::json data = UtilDb::getData("models");

    if (!data.is_array()) {
        std::cerr << "Erreur: Les données ne sont pas un tableau JSON." << std::endl;
        return;
    }

    auto& deptArray = data[0]["PhaseJoueur"];

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


void PhaseJoueur::save() {
    nlohmann::json data = UtilDb::getData("models");

    nlohmann::json deptJson = {
        {"id", this->id_},
        {"idJoueur", this->idJoueur_},
        {"idPhase", this->idPhase_},
    };
    data[0]["PhaseJoueur"].push_back(deptJson);
    UtilDb::saveData(data);
}
// Méthode pour mettre à jour un département
void PhaseJoueur::update() {
    nlohmann::json data = UtilDb::getData("models");

    bool updated = false;
    cout << "taille : " << data.size() << endl;
    for (auto& deptData : data[0]["PhaseJoueur"]) {
        if (deptData["id"] == id_) { 
            deptData["idJoueur"] = idJoueur_;
            deptData["idPhase"] = idPhase_; 
            deptData["temps"] = temps_; 
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




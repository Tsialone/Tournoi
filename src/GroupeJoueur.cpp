#include "GroupeJoueur.hpp"
#include <iostream>
#include "UtilDb.hpp"
using namespace std;

// Constructeur
GroupeJoueur::GroupeJoueur(int id, int idJoueur , int idGroupe ) : id_(id), idJoueur_(idJoueur) , idGroupe_(idGroupe)  {}

// Getter pour l'id
int GroupeJoueur::getId() const {
    return id_;
}
int GroupeJoueur::getIdJoueur() const {
    return idJoueur_;
}
int GroupeJoueur::getIdGroupe() const {
    return idGroupe_;
}



std::vector<GroupeJoueur> GroupeJoueur::getAll() {
    std::vector<GroupeJoueur> departments;

    nlohmann::json data = UtilDb::getData("models");

    if (data.is_array()) {
        for (const auto& deptData : data[0]["GroupeJoueur"]) {
            int id = deptData["id"];
            int idJoueur = deptData["idJoueur"];
            int idGroupe = deptData["idGroupe"];
            departments.push_back(GroupeJoueur(id, idJoueur , idGroupe ));
        }
    }

    return departments;
}

GroupeJoueur  GroupeJoueur::getById(int id) {
    nlohmann::json data = UtilDb::getData("models");
    for (const auto& deptData : data[0]["GroupeJoueur"]) {
        if (deptData["id"] == id) {
            int id = deptData["id"];
            int idJoueur = deptData["idJoueur"];
            int idGroupe = deptData["idGroupe"];
            return GroupeJoueur(id, idJoueur , idGroupe );
        }
    }
    return GroupeJoueur(0, 0 , 0 );
}

void GroupeJoueur::del() {
    nlohmann::json data = UtilDb::getData("models");

    if (!data.is_array()) {
        std::cerr << "Erreur: Les données ne sont pas un tableau JSON." << std::endl;
        return;
    }

    auto& deptArray = data[0]["GroupeJoueur"];

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


void GroupeJoueur::save() {
    nlohmann::json data = UtilDb::getData("models");

    nlohmann::json deptJson = {
        {"id", this->id_},
        {"idJoueur", this->idJoueur_},
        {"idGroupe", this->idGroupe_},
    };
    data[0]["GroupeJoueur"].push_back(deptJson);
    UtilDb::saveData(data);
}
// Méthode pour mettre à jour un département
void GroupeJoueur::update() {
    nlohmann::json data = UtilDb::getData("models");

    bool updated = false;
    // cout << "taille : " << data.size() << endl;
    for (auto& deptData : data[0]["GroupeJoueur"]) {
        if (deptData["id"] == id_) { 
            deptData["idJoueur"] = idJoueur_;
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




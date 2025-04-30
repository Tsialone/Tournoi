#include "TournoiPhase.hpp"
#include <iostream>
#include "UtilDb.hpp"
using namespace std;

// Constructeur
TournoiPhase::TournoiPhase(int id, int idTournoi , int idPhase ) : id_(id), idTournoi_(idTournoi) , idPhase_(idPhase) {}

// Getter pour l'id
int TournoiPhase::getId() const {
    return id_;
}
int TournoiPhase::getIdTournoi() const {
    return idTournoi_;
}
int TournoiPhase::getIdPhase() const {
    return idPhase_;
}



std::vector<TournoiPhase> TournoiPhase::getAll() {
    std::vector<TournoiPhase> departments;

    nlohmann::json data = UtilDb::getData("models");

    if (data.is_array()) {
        for (const auto& deptData : data[0]["TournoiPhase"]) {
            int id = deptData["id"];
            int idTournoi = deptData["idTournoi"];
            int idPhase = deptData["idPhase"];
            departments.push_back(TournoiPhase(id, idTournoi , idPhase));
        }
    }

    return departments;
}

TournoiPhase  TournoiPhase::getById(int id) {
    nlohmann::json data = UtilDb::getData("models");
    for (const auto& deptData : data[0]["TournoiPhase"]) {
        if (deptData["id"] == id) {
            int id = deptData["id"];
            int idTournoi = deptData["idTournoi"];
            int idPhase = deptData["idPhase"];
            return TournoiPhase(id, idTournoi , idPhase);
        }
    }
    return TournoiPhase(0, 0 , 0);
}

void TournoiPhase::del() {
    nlohmann::json data = UtilDb::getData("models");

    if (!data.is_array()) {
        std::cerr << "Erreur: Les données ne sont pas un tableau JSON." << std::endl;
        return;
    }

    auto& deptArray = data[0]["TournoiPhase"];

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


void TournoiPhase::save() {
    nlohmann::json data = UtilDb::getData("models");

    nlohmann::json deptJson = {
        {"id", this->id_},
        {"idTournoi", this->idTournoi_},
        {"idPhase", this->idPhase_},
    };
    data[0]["TournoiPhase"].push_back(deptJson);
    UtilDb::saveData(data);
}
// Méthode pour mettre à jour un département
void TournoiPhase::update() {
    nlohmann::json data = UtilDb::getData("models");

    bool updated = false;
    // cout << "taille : " << data.size() << endl;
    for (auto& deptData : data[0]["TournoiPhase"]) {
        if (deptData["id"] == id_) { 
            deptData["idTournoi"] = idTournoi_;
            deptData["idPhase"] = idPhase_; 
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




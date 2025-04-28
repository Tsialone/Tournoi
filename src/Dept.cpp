#include "Dept.hpp"
#include <iostream>
#include "UtilDb.hpp"
using namespace std;

// Constructeur
Dept::Dept(int id, const std::string& name) : id_(id), name_(name) {}

// Getter pour l'id
int Dept::getId() const {
    return id_;
}

// Getter pour le nom
std::string Dept::getName() const {
    return name_;
}

// Méthode pour récupérer toutes les données des départements
std::vector<Dept> Dept::getAll() {
    std::vector<Dept> departments;

    // Charger les données JSON depuis UtilDb
    nlohmann::json data = UtilDb::getData("dept");

    // Vérifier si des départements existent dans les données
    if (data.is_array()) {
        for (const auto& deptData : data) {
            int id = deptData["id"];
            std::string name = deptData["name"];
            departments.push_back(Dept(id, name));
        }
    }

    return departments;
}

// Méthode pour récupérer un département par ID
Dept  Dept::getById(int id) {
    nlohmann::json data = UtilDb::getData("models");
    for (const auto& deptData : data[0]["dept"]) {
        if (deptData["id"] == id) {
            return Dept(deptData["id"], deptData["name"]);
        }
    }

    return Dept(0, "Not Found");
}

void Dept::del() {
    nlohmann::json data = UtilDb::getData("models");

    // Vérifier que c'est un tableau
    if (!data.is_array()) {
        std::cerr << "Erreur: Les données ne sont pas un tableau JSON." << std::endl;
        return;
    }

    // Accéder à la liste des départements
    auto& deptArray = data[0]["dept"];

    // Vérifier que deptArray est bien un tableau
    if (!deptArray.is_array()) {
        std::cerr << "Erreur: 'dept' n'est pas un tableau JSON." << std::endl;
        return;
    }

    // Supprimer l'élément avec l'ID de cet objet
    auto it = std::remove_if(deptArray.begin(), deptArray.end(), [this](const nlohmann::json& dept) {
        return dept["id"] == this->id_;
    });

    if (it != deptArray.end()) {
        deptArray.erase(it, deptArray.end());

        // Sauvegarder les données mises à jour
        UtilDb::saveData(data);

        std::cout << "Département avec ID " << this->id_ << " supprimé." << std::endl;
    } else {
        std::cerr << "Département avec ID " << this->id_ << " non trouvé !" << std::endl;
    }
}


// Méthode pour ajouter un département
void Dept::save() {
    // Récupérer les données du fichier sous la clé "dept"
    nlohmann::json data = UtilDb::getData("models");

    nlohmann::json deptJson = {
        {"id", this->id_},
        {"name", this->name_}
    };
    data[0]["dept"].push_back(deptJson);
    // cout << "list: " << data[0]["phase"].dump(4) << endl;

    // Sauvegarder les données mises à jour dans le fichier sous la clé "dept"
    // nlohmann::json finalData = { {"dept", data} }; // Réintégrer les données sous la clé "dept"
    UtilDb::saveData(data);
}

// Méthode pour mettre à jour un département
void Dept::update() {
    // Obtenir les données du fichier JSON sous la clé "dept"
    nlohmann::json data = UtilDb::getData("models");

    bool updated = false;

    // Parcourir les départements pour trouver celui avec le bon ID
    cout << "taille : " << data.size() << endl;
    for (auto& deptData : data[0]["dept"]) {
        if (deptData["id"] == id_) {  // Comparer l'ID pour trouver le bon département
            deptData["name"] = name_;  // Mettre à jour le nom du département
            updated = true;
            break;  // Sortir de la boucle dès qu'on a trouvé et mis à jour le département
        }
    }

    if (updated) {
        // Sauvegarder les données mises à jour dans le fichier JSON
        UtilDb::saveData(data );
        std::cout << "Le département a été mis à jour." << std::endl;
    } else {
        std::cout << "Aucun département trouvé avec l'ID : " << id_ << std::endl;
    }
}




#include "JoueurCourse.hpp"
#include <iostream>
#include "UtilDb.hpp"
using namespace std;

// Constructeur
JoueurCourse::JoueurCourse(int id, int idJoueur, int idCourse, int idPhase, string temps) : id_(id), idJoueur_(idJoueur), idCourse_(idCourse), idPhase_(idPhase), temps_(temps) {}

// Getter pour l'id
int JoueurCourse::getId() const
{
    return id_;
}
int JoueurCourse::getIdPhase() const
{
    return idPhase_;
}
int JoueurCourse::getIdJoueur() const
{
    return idJoueur_;
}
int JoueurCourse::getIdCourse() const
{
    return idCourse_;
}
string JoueurCourse::getTemps() {
    return temps_;
}

std::vector<JoueurCourse> JoueurCourse::getAll()
{
    std::vector<JoueurCourse> departments;

    nlohmann::json data = UtilDb::getData("models");

    if (data.is_array())
    {
        for (const auto &deptData : data[0]["JoueurCourse"])
        {
            int id = deptData["id"];
            int idCourse = deptData["idCourse"];
            int idJoueur = deptData["idJoueur"];
            int idPhase = deptData["idPhase"];

            string temps = deptData["temps"];

            departments.push_back(JoueurCourse(id, idJoueur, idCourse, idPhase, temps));
        }
    }

    return departments;
}

JoueurCourse JoueurCourse::getById(int id)
{
    nlohmann::json data = UtilDb::getData("models");
    for (const auto &deptData : data[0]["JoueurCourse"])
    {
        if (deptData["id"] == id)
        {
            int id = deptData["id"];
            int idCourse = deptData["idCourse"];
            int idJoueur = deptData["idJoueur"];
            int idPhase = deptData["idPhase"];
            string temps = deptData["temps"];

            return JoueurCourse(id, idJoueur, idCourse, idPhase, temps);
        }
    }
    return JoueurCourse(0, 0, 0, 0, "00:00:00:00");
}

void JoueurCourse::del()
{
    nlohmann::json data = UtilDb::getData("models");

    if (!data.is_array())
    {
        std::cerr << "Erreur: Les données ne sont pas un tableau JSON." << std::endl;
        return;
    }

    auto &deptArray = data[0]["JoueurCourse"];

    if (!deptArray.is_array())
    {
        std::cerr << "Erreur: 'dept' n'est pas un tableau JSON." << std::endl;
        return;
    }

    auto it = std::remove_if(deptArray.begin(), deptArray.end(), [this](const nlohmann::json &dept)
                             { return dept["id"] == this->id_; });

    if (it != deptArray.end())
    {
        deptArray.erase(it, deptArray.end());

        UtilDb::saveData(data);

        std::cout << "Département avec ID " << this->id_ << " supprimé." << std::endl;
    }
    else
    {
        std::cerr << "Département avec ID " << this->id_ << " non trouvé !" << std::endl;
    }
}

void JoueurCourse::save()
{
    nlohmann::json data = UtilDb::getData("models");

    nlohmann::json deptJson = {
        {"id", this->id_},
        {"idJoueur", this->idJoueur_},
        {"idCourse", this->idCourse_},
        {"idPhase", this->idPhase_},
        {"temps", this->temps_}};
    data[0]["JoueurCourse"].push_back(deptJson);
    UtilDb::saveData(data);
}
// Méthode pour mettre à jour un département
void JoueurCourse::update()
{
    nlohmann::json data = UtilDb::getData("models");

    bool updated = false;
    cout << "taille : " << data.size() << endl;
    for (auto &deptData : data[0]["JoueurCourse"])
    {
        if (deptData["id"] == id_)
        {
            deptData["idJoueur"] = idJoueur_;
            deptData["idCourse"] = idCourse_;
            deptData["temps"] = temps_;
            updated = true;
            break;
        }
    }

    if (updated)
    {
        UtilDb::saveData(data);
        std::cout << "Le département a été mis à jour." << std::endl;
    }
    else
    {
        std::cout << "Aucun département trouvé avec l'ID : " << id_ << std::endl;
    }
}

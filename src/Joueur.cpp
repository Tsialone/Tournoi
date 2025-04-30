#include "Joueur.hpp"
#include <iostream>
#include "UtilDb.hpp"
#include "JoueurCourse.hpp"
#include "GroupeJoueur.hpp"


using namespace std;

// Constructeur
Joueur::Joueur(int id, const std::string &name) : id_(id), name_(name) {}

// Getter pour l'id
int Joueur::getId() const
{
    return id_;
}

std::string Joueur::getName() const
{
    return name_;
}

std::vector<Joueur> Joueur::getAll()
{
    std::vector<Joueur> departments;

    nlohmann::json data = UtilDb::getData("models");

    if (data.is_array())
    {
        for (const auto &JoueurData : data[0]["Joueur"])
        {
            int id = JoueurData["id"];
            std::string name = JoueurData["name"];
            departments.push_back(Joueur(id, name));
        }
    }

    return departments;
}

int Joueur::getIdGroupe()
{
    vector<GroupeJoueur> all_gj = GroupeJoueur::getAll();
    for (GroupeJoueur gj : all_gj)
    {
        if (gj.getIdJoueur() == this->getId())
        {
            return gj.getIdGroupe();
        }
    }
    return 0;
}

Joueur Joueur::getById(int id)
{
    nlohmann::json data = UtilDb::getData("models");
    for (const auto &JoueurData : data[0]["Joueur"])
    {
        if (JoueurData["id"] == id)
        {
            return Joueur(JoueurData["id"], JoueurData["name"]);
        }
    }

    return Joueur(0, "Not Found");
}

void Joueur::del()
{
    nlohmann::json data = UtilDb::getData("models");

    if (!data.is_array())
    {
        std::cerr << "Erreur: Les données ne sont pas un tableau JSON." << std::endl;
        return;
    }

    auto &JoueurArray = data[0]["Joueur"];

    if (!JoueurArray.is_array())
    {
        std::cerr << "Erreur: 'Joueur' n'est pas un tableau JSON." << std::endl;
        return;
    }

    auto it = std::remove_if(JoueurArray.begin(), JoueurArray.end(), [this](const nlohmann::json &Joueur)
                             { return Joueur["id"] == this->id_; });

    if (it != JoueurArray.end())
    {
        JoueurArray.erase(it, JoueurArray.end());

        UtilDb::saveData(data);

        std::cout << "Département avec ID " << this->id_ << " supprimé." << std::endl;
    }
    else
    {
        std::cerr << "Département avec ID " << this->id_ << " non trouvé !" << std::endl;
    }
}

void Joueur::save()
{
    nlohmann::json data = UtilDb::getData("models");

    nlohmann::json JoueurJson = {
        {"id", this->id_},
        {"name", this->name_}};
    data[0]["Joueur"].push_back(JoueurJson);
    UtilDb::saveData(data);
}
// Méthode pour mettre à jour un département
void Joueur::update()
{
    nlohmann::json data = UtilDb::getData("models");

    bool updated = false;
    // cout << "taille : " << data.size() << endl;
    for (auto &JoueurData : data[0]["Joueur"])
    {
        if (JoueurData["id"] == id_)
        {
            JoueurData["name"] = name_;
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

string *Joueur::getTempsByPhase(int idPhase)
{   
    vector<JoueurCourse> all_jc = JoueurCourse::getAll();
    for (JoueurCourse jc : all_jc)
    {
        if (jc.getIdJoueur() == this->getId()  &&  jc.getIdPhase() == idPhase)
        {   
            std::string* temp = new std::string(jc.getTemps());
            return   temp;
        }
    }
    std::string* temp = new std::string("00:00:00:00");
    return temp;
}

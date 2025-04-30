#include "Phase.hpp"
#include <iostream>
#include "UtilDb.hpp"
#include "Data.hpp"
#include "JoueurCourse.hpp"
#include "FormPanel.hpp"
#include "Fonction.hpp"

using namespace std;

// Constructeur
Phase::Phase(int id, const std::string &name) : id_(id), name_(name) {}

// Getter pour l'id
int Phase::getId() const
{
    return id_;
}

std::string Phase::getName() const
{
    return name_;
}

std::vector<Phase> Phase::getAll()
{
    std::vector<Phase> departments;

    nlohmann::json data = UtilDb::getData("models");

    if (data.is_array())
    {
        for (const auto &deptData : data[0]["Phase"])
        {
            int id = deptData["id"];
            std::string name = deptData["name"];
            departments.push_back(Phase(id, name));
        }
    }

    return departments;
}

Phase Phase::getById(int id)
{
    nlohmann::json data = UtilDb::getData("models");
    for (const auto &deptData : data[0]["Phase"])
    {
        if (deptData["id"] == id)
        {
            return Phase(deptData["id"], deptData["name"]);
        }
    }

    return Phase(0, "Not Found");
}

void Phase::del()
{
    nlohmann::json data = UtilDb::getData("models");

    if (!data.is_array())
    {
        std::cerr << "Erreur: Les données ne sont pas un tableau JSON." << std::endl;
        return;
    }

    auto &deptArray = data[0]["Phase"];

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

void Phase::save()
{
    nlohmann::json data = UtilDb::getData("models");

    nlohmann::json deptJson = {
        {"id", this->id_},
        {"name", this->name_}};
    data[0]["Phase"].push_back(deptJson);
    UtilDb::saveData(data);
}
// Méthode pour mettre à jour un département
void Phase::update()
{
    nlohmann::json data = UtilDb::getData("models");

    bool updated = false;
    // cout << "taille : " << data.size() << endl;
    for (auto &deptData : data[0]["Phase"])
    {
        if (deptData["id"] == id_)
        {
            deptData["name"] = name_;
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

void Phase::initListStat(FormPanel *form)
{
    this->deleteListStat();
    double margin_y = 40;
    double y = 60;

    vector<string> resp = {};
    vector<double> temp_temps = {};
    vector<JoueurCourse> all_jc = JoueurCourse::getAll();
    cout << "ito ilay phase: " << this->getId() << "sa taille: "  <<endl;
    for (JoueurCourse jc : all_jc)
    {
        if (jc.getIdPhase() == this->getId())
        {
            // resp.push_back(jc.getTemps());
            temp_temps.push_back(Fonction::tempsToString(jc.getTemps()));
            // resp.push_back(txt);
        }
    }
    Fonction::trieTemps(temp_temps);
    for (double t : temp_temps)
    {
        for (JoueurCourse jc : all_jc)
        {
            if (jc.getIdPhase() == this->getId())
            {
                double sec = Fonction::tempsToString(jc.getTemps());
                if (sec == t  ) {
                    Joueur j = Joueur::getById(jc.getIdJoueur());
                    string txt  =  j.getName() + "        |        " + (jc.getTemps()) ;
                    resp.push_back(txt);
                }
            }
        }

    }

    for (int i = 0; i < resp.size(); i++)
    {
        wxStaticText *titre_groupe = new wxStaticText(form, wxID_ANY, resp[i] + to_string(this->getId()), wxDefaultPosition, wxSize(400, -1));
        titre_groupe->SetPosition(wxPoint(650, y));
        Data::current_trie_phase.push_back(titre_groupe);
        y += margin_y;
    }
}
void Phase::deleteListStat()
{
    for (wxStaticText *input : Data::current_trie_phase)
    {
        input->Destroy();
    }
    Data::current_trie_phase.clear();
}

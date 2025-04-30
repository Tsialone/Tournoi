#include "Groupe.hpp"
#include <iostream>
#include "UtilDb.hpp"
#include "Joueur.hpp"
#include "GroupeJoueur.hpp"
#include "Fonction.hpp"
#include "PhaseGroupe.hpp"

using namespace std;

// Constructeur
Groupe::Groupe(int id, int idvoisin, std::string name) : id_(id), idVoisin_(idvoisin), name_(name) {}

// Getter pour l'id
int Groupe::getId() const
{
    return id_;
}
void Groupe::setIdVoisin(int idVoisin)
{
    idVoisin_ = idVoisin;
}
int Groupe::getIdVoisin() const
{
    return idVoisin_;
}

std::string Groupe::getName() const
{
    return name_;
}

std::vector<Groupe> Groupe::getAll()
{
    std::vector<Groupe> departments;

    nlohmann::json data = UtilDb::getData("models");

    if (data.is_array())
    {
        for (const auto &GroupeData : data[0]["Groupe"])
        {
            int id = GroupeData["id"];
            int idVoisin = GroupeData["idVoisin"];
            std::string name = GroupeData["name"];
            departments.push_back(Groupe(id, idVoisin, name));
        }
    }

    return departments;
}

Groupe Groupe::getById(int id)
{
    nlohmann::json data = UtilDb::getData("models");
    for (const auto &GroupeData : data[0]["Groupe"])
    {
        if (GroupeData["id"] == id)
        {
            return Groupe(GroupeData["id"], GroupeData["idVoisin"], GroupeData["name"]);
        }
    }

    return Groupe(0, 1, "Not Found");
}

void Groupe::del()
{
    nlohmann::json data = UtilDb::getData("models");

    if (!data.is_array())
    {
        std::cerr << "Erreur: Les données ne sont pas un tableau JSON." << std::endl;
        return;
    }

    auto &GroupeArray = data[0]["Groupe"];

    if (!GroupeArray.is_array())
    {
        std::cerr << "Erreur: 'Groupe' n'est pas un tableau JSON." << std::endl;
        return;
    }

    auto it = std::remove_if(GroupeArray.begin(), GroupeArray.end(), [this](const nlohmann::json &Groupe)
                             { return Groupe["id"] == this->id_; });

    if (it != GroupeArray.end())
    {
        GroupeArray.erase(it, GroupeArray.end());

        UtilDb::saveData(data);

        std::cout << "Département avec ID " << this->id_ << " supprimé." << std::endl;
    }
    else
    {
        std::cerr << "Département avec ID " << this->id_ << " non trouvé !" << std::endl;
    }
}

void Groupe::save()
{
    nlohmann::json data = UtilDb::getData("models");

    nlohmann::json GroupeJson = {
        {"id", this->id_},
        {"idVoisin", this->idVoisin_},
        {"name", this->name_}};
    data[0]["Groupe"].push_back(GroupeJson);
    UtilDb::saveData(data);
}
// Méthode pour mettre à jour un département
void Groupe::update()
{
    nlohmann::json data = UtilDb::getData("models");

    bool updated = false;
    // cout << "taille : " << data.size() << endl;
    for (auto &GroupeData : data[0]["Groupe"])
    {
        if (GroupeData["id"] == id_)
        {
            GroupeData["name"] = name_;
            GroupeData["idVoisin"] = idVoisin_;
            updated = true;
            break;
        }
    }

    if (updated)
    {
        UtilDb::saveData(data);
        std::cout << "Model a été mis à jour." << std::endl;
    }
    else
    {
        std::cout << "Aucun model trouvé avec l'ID : " << id_ << std::endl;
    }
}

int *Groupe::getIdPhase()
{
    vector<PhaseGroupe> all_phase = PhaseGroupe::getAll();
    for (PhaseGroupe phase : all_phase)
    {
        if (phase.getIdGroupe() == this->getId())
        {
            int valeur = phase.getIdPhase();
            int *id = &valeur;
            // cout << "idPhase: " << valeur << endl;
            return id;
        }
    }
    // cout << "hummm" << endl;
    return nullptr;
}
Groupe *Groupe::getVoisin()
{
    vector<Groupe> all_groupe = this->getAll();
    for (Groupe groupe : all_groupe)
    {
        if (groupe.getIdVoisin() == this->getIdVoisin() and this->getId() != groupe.getId())
        {
            Groupe *gp = new Groupe(groupe.getId(), groupe.getIdVoisin(), groupe.getName());
            return gp;
        }
    }
    return nullptr;
}
Groupe *Groupe::getFinaliste()
{
    vector<Groupe> all_groupe = this->getAll();
    for (Groupe groupe : all_groupe)
    {
        if ((groupe.getIdVoisin() == 42 || groupe.getIdVoisin() == 41) and this->getId() != groupe.getId() and groupe.getJoueurs().size() > 0)
        {
            Groupe *gp = new Groupe(groupe.getId(), groupe.getIdVoisin(), groupe.getName());
            return gp;
        }
    }
    return nullptr;
}
std::vector<Joueur> Groupe::getJoueurs()
{
    vector<GroupeJoueur> all_gj = GroupeJoueur::getAll();
    vector<Joueur> all_j = {};
    for (GroupeJoueur gj : all_gj)
    {
        if (gj.getIdGroupe() == this->getId())
        {
            all_j.push_back(Joueur::getById(gj.getIdJoueur()));
        }
    }
    return all_j;
}

vector<Joueur> Groupe::getTwoBest(int idPhase)
{
    vector<Joueur> his_joueur = this->getJoueurs();
    vector<Joueur> his_joueur_trie = {};

    vector<double> temps_joueur = {};
    for (Joueur j : his_joueur)
    {

        int h, m, s, ms;
        if (Fonction::parserTemps(*j.getTempsByPhase(idPhase), h, m, s, ms))
        {
            temps_joueur.push_back(Fonction::toSeconde(h, m, s, ms));
        }
    }

    Fonction::trieTemps(temps_joueur);
    for (double t : temps_joueur)
    {
        for (Joueur j : his_joueur)
        {
            int h, m, s, ms;
            if (Fonction::parserTemps(*j.getTempsByPhase(idPhase), h, m, s, ms))
            {
                if (t == Fonction::toSeconde(h, m, s, ms))
                {
                    his_joueur_trie.push_back(j);
                    // cout << "idJoueur: " << j.getId() << endl;
                }
            }
        }
        // cout << "temps: " << t << endl;
    }
    return his_joueur_trie;
};
vector<Joueur> Groupe::getBest(int idPhase)
{
    vector<Joueur> his_joueur = this->getJoueurs();
    vector<Joueur> his_joueur_trie = {};

    vector<double> temps_joueur = {};
    for (Joueur j : his_joueur)
    {

        int h, m, s, ms;
        if (Fonction::parserTemps(*j.getTempsByPhase(idPhase), h, m, s, ms))
        {
            temps_joueur.push_back(Fonction::toSeconde(h, m, s, ms));
        }
    }

    Fonction::trieTemps(temps_joueur);
    for (double t : temps_joueur)
    {
        for (Joueur j : his_joueur)
        {
            int h, m, s, ms;
            if (Fonction::parserTemps(*j.getTempsByPhase(idPhase), h, m, s, ms))
            {
                if (t == Fonction::toSeconde(h, m, s, ms))
                {
                    his_joueur_trie.push_back(j);
                    // cout << "idJoueur: " << j.getId() << endl;
                }
            }
        }
        // cout << "temps: " << t << endl;
    }
    vector<Joueur> resp = {};
    if (his_joueur_trie.size() > 0)
    {
        resp.push_back(his_joueur_trie[0]);
    }
    return resp;
};
Groupe *Groupe::miteraka(int idPhase)
{
    vector<Groupe> resp = {};
    // eliminatoire
    if (idPhase == 1)
    {
        vector<Joueur> his_joueur = this->getJoueurs();
        vector<Joueur> his_joueur_trie = this->getTwoBest(idPhase);
        Groupe *zanaka = new Groupe(Fonction::getLastId("Groupe"), 0, this->getName() + "'");
        zanaka->save();
        PhaseGroupe temp = PhaseGroupe(Fonction::getLastId("PhaseGroupe"), idPhase, zanaka->getId());
        temp.save();
        // cout << "phase1: " << this->getName() << endl;
        // for (Joueur jj : his_joueur)
        // {
        //     cout << "idJoueur: " << jj.getId() << " temps: " <<   Fonction::tempsToString(*jj.getTempsByPhase(idPhase))    << endl;

        // }

        for (int i = 0; i < his_joueur_trie.size() - 2; i++)
        {
            GroupeJoueur *gj = new GroupeJoueur(Fonction::getLastId("GroupeJoueur"), his_joueur_trie[i].getId(), zanaka->getId());
            gj->save();
        }
        return zanaka;
    }
    // 1/4
    else if (idPhase == 2)
    {

        // cout << "pahse 2 xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" << endl;
        vector<Joueur> his_joueur = this->getJoueurs();
        vector<Joueur> his_joueur_trie = this->getTwoBest(idPhase);

        Groupe *voisin = this->getVoisin();
        vector<Joueur> voisin_joueur_trie = voisin->getTwoBest(idPhase);

        vector<Joueur> newJ = {};
        newJ.push_back(his_joueur_trie[0]);
        newJ.push_back(voisin_joueur_trie[1]);
        // newJ.insert(his_joueur_trie.begin(), voisin_joueur_trie.begin(), voisin_joueur_trie.end());
        // cout << "zanaka vao2 ny " << this->getName() << endl;
        // for (Joueur jj : newJ)
        // {
        //     cout << "idZanaka: " << jj.getId() << " temps: " <<   Fonction::tempsToString(*jj.getTempsByPhase(idPhase))    << endl;
        // }
        Groupe *zanaka = new Groupe(Fonction::getLastId("Groupe"), 0, this->getName() + "'");
        zanaka->save();
        PhaseGroupe temp = PhaseGroupe(Fonction::getLastId("PhaseGroupe"), idPhase, zanaka->getId());
        temp.save();

        // cout << "phase2: " << this->getName() << endl;
        // for (Joueur jj : newJ)
        // {
        //     cout << "idJoueur: " << jj.getId() << " temps: " <<   Fonction::tempsToString(*jj.getTempsByPhase(idPhase))    << endl;
        // }

        for (int i = 0; i < newJ.size(); i++)
        {
            GroupeJoueur *gj = new GroupeJoueur(Fonction::getLastId("GroupeJoueur"), newJ[i].getId(), zanaka->getId());
            gj->save();
        }
        return zanaka;
    }

    // miditra 1/2
    else if (idPhase == 3)
    {
        vector<Joueur> his_joueur = this->getJoueurs();
        vector<Joueur> his_joueur_trie = this->getBest(idPhase);

        Groupe *voisin = this->getVoisin();
        vector<Joueur> voisin_joueur_trie = voisin->getTwoBest(idPhase);

        vector<Joueur> newJ = {};
        newJ.push_back(his_joueur_trie[0]);
        // newJ.push_back(voisin_joueur_trie[1]);
        // newJ.insert(his_joueur_trie.begin(), voisin_joueur_trie.begin(), voisin_joueur_trie.end());
        // cout << "zanaka vao2 ny " << this->getName() << endl;
        // for (Joueur jj : newJ)
        // {
        //     cout << "idZanaka: " << jj.getId() << " temps: " <<   Fonction::tempsToString(*jj.getTempsByPhase(idPhase))    << endl;
        // }
        Groupe *zanaka = new Groupe(Fonction::getLastId("Groupe"), 0, this->getName() + "'");
        zanaka->save();
        PhaseGroupe temp = PhaseGroupe(Fonction::getLastId("PhaseGroupe"), idPhase, zanaka->getId());
        temp.save();

        // cout << "phase2: " << this->getName() << endl;
        // for (Joueur jj : newJ)
        // {
        //     cout << "idJoueur: " << jj.getId() << " temps: " <<   Fonction::tempsToString(*jj.getTempsByPhase(idPhase))    << endl;
        // }

        for (int i = 0; i < newJ.size(); i++)
        {
            GroupeJoueur *gj = new GroupeJoueur(Fonction::getLastId("GroupeJoueur"), newJ[i].getId(), zanaka->getId());
            gj->save();
        }
        return zanaka;
    }
    else if (idPhase == 4)
    {
        vector<Joueur> his_joueur = this->getJoueurs();
        vector<Joueur> his_joueur_trie = this->getBest(idPhase);

        Groupe *voisin = this->getVoisin();
        vector<Joueur> voisin_joueur_trie = voisin->getTwoBest(idPhase);

        vector<Joueur> newJ = {};
        double his_joueur_trie_temps = Fonction::tempsToString(*his_joueur_trie[0].getTempsByPhase(idPhase));
        double voisin_joueur_trie_temps = Fonction::tempsToString(*voisin_joueur_trie[0].getTempsByPhase(idPhase));
        if (his_joueur_trie_temps < voisin_joueur_trie_temps)
        {
            newJ.push_back(his_joueur_trie[0]);
        }
        Groupe *zanaka = new Groupe(Fonction::getLastId("Groupe"), 0, this->getName() + "'");
        zanaka->save();
        PhaseGroupe temp = PhaseGroupe(Fonction::getLastId("PhaseGroupe"), idPhase, zanaka->getId());
        temp.save();

        // cout << "phase2: " << this->getName() << endl;
        // for (Joueur jj : newJ)
        // {
        //     cout << "idJoueur: " << jj.getId() << " temps: " <<   Fonction::tempsToString(*jj.getTempsByPhase(idPhase))    << endl;
        // }

        for (int i = 0; i < newJ.size(); i++)
        {
            GroupeJoueur *gj = new GroupeJoueur(Fonction::getLastId("GroupeJoueur"), newJ[i].getId(), zanaka->getId());
            gj->save();
        }
        return zanaka;
    }
    else if (idPhase == 5)
    {
        vector<Joueur> his_joueur = this->getJoueurs();
        vector<Joueur> his_joueur_trie = this->getBest(idPhase);
        
        vector<Groupe> all = this->getAll();
        Groupe *voisin = this->getFinaliste();
        cout << "tonga ny finale xxxxxxxxxxxxxxxxxxxxxx "    << " ilay antony " << this->getName() << "son voisin: " << voisin->getName() << endl;
        

        vector<Joueur> voisin_joueur_trie = voisin->getBest(idPhase);

        vector<Joueur> newJ = {};
        double his_joueur_trie_temps = 0.0;
        double voisin_joueur_trie_temps = 0.0;
        if (his_joueur_trie.size() > 0)
        {
            his_joueur_trie_temps = Fonction::tempsToString(*his_joueur_trie[0].getTempsByPhase(idPhase));
        }
        if (voisin_joueur_trie.size() > 0)
        {
            voisin_joueur_trie_temps = Fonction::tempsToString(*voisin_joueur_trie[0].getTempsByPhase(idPhase));
        }

        if ( his_joueur_trie_temps < voisin_joueur_trie_temps)
        {
            if (his_joueur_trie.size() > 0)
            {
                newJ.push_back(his_joueur_trie[0]);

            }
        }
        Groupe *zanaka = new Groupe(Fonction::getLastId("Groupe"), 0, this->getName() + "'");
        zanaka->save();
        PhaseGroupe temp = PhaseGroupe(Fonction::getLastId("PhaseGroupe"), idPhase, zanaka->getId());
        temp.save();

        for (int i = 0; i < newJ.size(); i++)
        {
            GroupeJoueur *gj = new GroupeJoueur(Fonction::getLastId("GroupeJoueur"), newJ[i].getId(), zanaka->getId());
            gj->save();
        }
        return zanaka;
    }

    return nullptr;
}

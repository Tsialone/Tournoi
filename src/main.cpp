#include <iostream>
#include "UtilDb.hpp"
#include "MainFrame.hpp"
#include <wx/wx.h>

#include "Dept.hpp"
#include "Tournoi.hpp"
#include "Phase.hpp"
#include "TournoiPhase.hpp"
#include "PhaseGroupe.hpp"
#include "Joueur.hpp"
#include "Groupe.hpp"
#include "GroupeJoueur.hpp"
#include "Course.hpp"
#include "JoueurCourse.hpp"
#include "Data.hpp"


using namespace nlohmann;
using namespace std;
class MyApp : public wxApp {
    public:
        virtual bool OnInit() {
            UtilDb::init("database/data.json");
            Data::current_groupe = Groupe::getAll();

            MainFrame* frame = new MainFrame("Fenêtre principale avec formulaire");
            frame->Show(true);
            return true;
        }
    };
    
    wxIMPLEMENT_APP(MyApp);
// int main()
// {
//     // Initialiser la connexion avec le fichier JSON
//     UtilDb::init("database/data.json");
    
//     // vector<string> lettre = {"A", "B", "C", "D"};
//     // vector<string> phase_name = {"eleminatoir", "1/4", "1/2", "Finale"};

//     // // creation tournoi
//     // Tournoi tour(1, "t1");
//     // tour.save();

//     // // creation des joueurs
//     // for (int i = 0; i < 16; i++)
//     // {
//     //     Joueur temp(i + 1, "J" + to_string(i + 1));
//     //     temp.save();
//     // }

//     // // creation des groupes
//     // int voisin = 0;
//     // for (int i = 0; i < 4; i++)
//     // {
//     //     if ((i) % 2 == 0 ){
//     //         voisin++;
//     //     }
//     //     Groupe temp(i + 1, voisin  ,lettre[i]);
//     //     temp.save();
//     // }

//     // // inclusion des joueur dans chaque groupe
//     // int index_groupe = 0;
//     // vector<Joueur> all_joueur = Joueur::getAll();
//     // cout << "taille: " << all_joueur.capacity() << endl;
//     // for (int j = 0; j < all_joueur.capacity(); j++)
//     // {
//     //     GroupeJoueur temp(j + 1, all_joueur[j].getId(), index_groupe + 1);
//     //     temp.save();
//     //     if ((j+ 1)  % 4 == 0){
//     //         index_groupe++;
//     //     }
//     // }

//     // //initialisation des phases
//     // for (int j = 0; j < 4; j++)
//     // {
//     //     Phase temp(j + 1,  phase_name[j] );
//     //     temp.save();
//     // }

//     // //initialisation des courses de chaque joueur phase 1
//     // for (int j = 0; j < all_joueur.capacity(); j++)
//     // {
//     //     Course temp(j + 1, "C" +   to_string(all_joueur[j].getId())  + "P1");
//     //     temp.save();
//     //     JoueurCourse temp2  (j+ 1 ,  all_joueur[j].getId() , temp.getId() , 1  ,  "00:00:00:00");
//     //     temp2.save();
//     // }

//     // voir les joueurs dun groupe
//     // Groupe gg = Groupe::getById(1);
  
//     // Groupe * voisin = gg.getVoisin();
//     // cout << "groupe: " << voisin->getName() << endl;



//     // //eliminatoire
//     // int k = 0;
//     // int index_voisinage = 10;
//     // for (Groupe g : gg.getAll())
//     // {
//     //     if (k % 2 == 0)
//     //     {
//     //         index_voisinage++;
//     //     }
//     //     cout << "groupe: " << g.getName() << endl;
//     //     Groupe *fils = g.miteraka(1);
//     //     fils->setIdVoisin(index_voisinage);
//     //     fils->update();
//     //     cout << "getIdVoisin: " << fils->getIdVoisin() << endl;
//     //     cout << "getId: " << fils->getId() << endl;
//     //     // cout << "fils: " << fils->getName() << endl;
//     //     cout << "fils_joueur_phase: " << *fils->getIdPhase() << endl;
//     //     for (Joueur j : fils->getJoueurs())
//     //     {
//     //         cout << "j: " << j.getName() << endl;
//     //     }
//     //     k++;
//     // }

//     // getVoisin
//     //  Groupe  gp1 =  Groupe::getById(4);
//     //  Groupe  * v = gp1.getVoisin();
//     //  cout << v->getName() << endl;

//     // Dept test(45 , "kiko");
//     // Phase tour (1 , "hello") ;
//     // TournoiPhase tourPhase(1 , 1000 , 1);
//     // tourPhase.save();

//     // test.save();
//     // vector<Dept> depts = test.getAll();
//     // tourPhase.update();
//     // test.del();
//     // Dept  byId = Dept::getById(45);
//     // cout << "ID: " << byId.getId() << ", Name: " << byId.getName() << endl;

//     // // Récupérer les données du fichier JSON
//     // json data = UtilDb::getData();

//     // // Afficher les données récupérées (si présentes)
//     // cout << "Données actuelles dans le fichier JSON : " << endl;
//     // cout << data.dump(4) << endl;  // Affichage formaté avec 4 espaces d'indentation

//     // // Mettre à jour les données (exemple)
//     // data["joueurs"] = { "Alice", "Bob", "Charlie", "David" };  // Ajouter une liste de joueurs

//     // // Sauvegarder les nouvelles données dans le fichier JSON
//     // UtilDb::saveData(data);

//     // // Vérifier que les nouvelles données sont bien sauvegardées
//     // cout << "Données après mise à jour et sauvegarde : " << endl;
//     // cout << data.dump(4) << endl;

//     return 0;
// }

#include <iostream>
#include "UtilDb.hpp" 

#include "Dept.hpp" 
#include "Tournoi.hpp" 
#include "Phase.hpp" 
#include "TournoiPhase.hpp" 
#include "PhaseJoueur.hpp" 




using namespace nlohmann;
using namespace std;
int main() {
    // Initialiser la connexion avec le fichier JSON
    UtilDb::init("database/data.json");
    Dept test(45 , "kiko");
    Phase tour (1 , "hello") ;
    TournoiPhase tourPhase(1 , 1000 , 1);
    PhaseJoueur phaseJoueur(1 , 1000 , 1 , "00:00:00:00");
    // tourPhase.save();
    phaseJoueur.save();

    // test.save();
    // vector<Dept> depts = test.getAll();
    // tourPhase.update();
    // test.del();
    // Dept  byId = Dept::getById(45);
    // cout << "ID: " << byId.getId() << ", Name: " << byId.getName() << endl;




    // // Récupérer les données du fichier JSON
    // json data = UtilDb::getData();
    
    // // Afficher les données récupérées (si présentes)
    // cout << "Données actuelles dans le fichier JSON : " << endl;
    // cout << data.dump(4) << endl;  // Affichage formaté avec 4 espaces d'indentation

    // // Mettre à jour les données (exemple)
    // data["joueurs"] = { "Alice", "Bob", "Charlie", "David" };  // Ajouter une liste de joueurs

    // // Sauvegarder les nouvelles données dans le fichier JSON
    // UtilDb::saveData(data);

    // // Vérifier que les nouvelles données sont bien sauvegardées
    // cout << "Données après mise à jour et sauvegarde : " << endl;
    // cout << data.dump(4) << endl;

    return 0;
}

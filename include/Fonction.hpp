#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm> 
#include <json.hpp>
#include "UtilDb.hpp"

class Fonction
{
public:
    static bool parserTemps(const std::string &temps, int &heures, int &minutes, int &secondes, int &millisecondes)
    {
        std::istringstream stream(temps);
        char delimiter;

        if (stream >> heures >> delimiter >> minutes >> delimiter >> secondes >> delimiter >> millisecondes)
        {
            if (delimiter == ':' && heures >= 0 && minutes >= 0 && minutes < 60 && secondes >= 0 && secondes < 60 && millisecondes >= 0 && millisecondes < 1000)
            {
                return true;
            }
        }
        return false;
    }
    static double tempsToString (const std::string &temps)
    {
        int heures, minutes, secondes, millisecondes;
        if (parserTemps(temps, heures, minutes, secondes, millisecondes))
        {
            return  toSeconde(heures, minutes, secondes, millisecondes)  ;
        }
        return 0.0; 
    }
    static double toSeconde(int &heures, int &minutes, int &secondes, int &millisecondes)
    {
        double total_seconds = heures * 3600 + minutes * 60 + secondes + millisecondes / 1000.0;
        return total_seconds;
    }
    static void trieTemps (std::vector<double> &temps_joueur){
        std::sort(temps_joueur.begin(), temps_joueur.end());
    }
    static int getLastId (std::string tableName){
        nlohmann::json data = UtilDb::getData("models");
        int lastId = 0;
        for (const auto &item : data[0][tableName])
        {
            if (item["id"] > lastId)
            {
                lastId = item["id"];
            }
        }
        return lastId+1;

    }
};

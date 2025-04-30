#include "UtilDb.hpp"
#include <fstream>
#include <json.hpp>

std::string UtilDb::jsonPath_ ;  
nlohmann::json UtilDb::data_; 

void UtilDb::init(const std::string& path) {
    if (!path.empty()) {
        jsonPath_ = path; 
    }

    std::ifstream inputFile(jsonPath_);
    if (inputFile.is_open()) {
        inputFile >> data_;
        inputFile.close();
    }
}

nlohmann::json UtilDb::getData(const std::string& objectname) {
    std::ifstream file(jsonPath_);
    nlohmann::json data;
    
    if (file.peek() == std::ifstream::traits_type::eof()) {
        data = { {objectname, nlohmann::json::array()} }; 
    } else {
        file >> data; 
    }
    if (data.contains(objectname)) {
        return data[objectname];
    } else {
        return nlohmann::json::array();
    }
}


void UtilDb::saveData(const nlohmann::json& data) {
    nlohmann::json finalData;
    finalData["models"] = data;  // Remettre sous "models"
    std::ofstream file(jsonPath_);
    file << finalData.dump(4);
}


#pragma once
#include <json.hpp>
#include <string>

class UtilDb {
public:
    static void init(const std::string& path); 
    static nlohmann::json getData(const std::string& path);
    static void saveData(const nlohmann::json& data);

    static std::string getJsonPath() { return jsonPath_; }
    static void setJsonPath(const std::string& path) { jsonPath_ = path; }

private:
    static std::string jsonPath_;  
    static nlohmann::json data_; 
};

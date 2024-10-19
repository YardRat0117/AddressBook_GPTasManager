#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include "json.hpp"
#include "IModule.hpp"

using json = nlohmann::json;

class dataTransfer {
public:
    void registerModule(const int moduleCode, IModule* module) {
        if (modules.find(moduleCode) == modules.end()) {
            modules[moduleCode] = module;
            module->setDataTransfer(this);
        } else {
            std::cerr << "Error: Module with code " << moduleCode << " is already registered." << std::endl;
        }
    }

    void retrieveData(const json& dataPackage) {
        try {
            int targetModuleCode = dataPackage.at("targetModuleCode");
            this->sendData(targetModuleCode, dataPackage);
        } catch (json::exception& e) {
            std::cerr << "Error: Missing targetModuleCode in dataPackage. " << e.what() << std::endl;
        }
    }

    void sendData(const int& targetModuleCode, const json& dataPackage) {
        auto it = modules.find(targetModuleCode);
        if (it != modules.end()) {
            it->second->retrieveData(dataPackage);
        } else {
            std::cerr << "Error: Target module with code " << targetModuleCode << " not found." << std::endl;
        }
    }

private:
    std::unordered_map<int, IModule*> modules;
};

#pragma once

#include <iostream>
#include <fstream>
#include "json.hpp"
#include "IModule.hpp"

using json = nlohmann::json;

class dataStorage : public IModule {
public:
    dataStorage() {
        this->moduleCode = 3;
        this->dt = nullptr;
    }

    void retrieveData(const json& dataPackage) override {
        int requestCode = dataPackage.value("requestCode", -1);
        switch (requestCode) {
            case 1:
                saveToFile(dataPackage);
                break;
            case 2:
                loadFromFile();
                break;
            default:
                std::cerr << "Invalid request code received: " << requestCode << std::endl;
        }
    }

    void sendData(const int& targetModuleCode, const json& dataPackage) override {
        std::cout << "dataStorage sending data to module " << targetModuleCode << std::endl;
        dt->retrieveData(dataPackage);
    }

    void setDataTransfer(dataTransfer* dt) override {
            this->dt = dt;
    }

private:
    std::string filename = "contacts.json";

    void saveToFile(const json& data) {
        std::ofstream outFile(filename);
        if (outFile.is_open()) {
            outFile << data.dump();
            outFile.close();
            sendFeedback("Data saved successfully.");
        } else {
            sendFeedback("Failed to save data.");
        }
    }

    void loadFromFile() {
        std::ifstream inFile(filename);
        if (inFile.is_open()) {
            json data;
            inFile >> data;
            inFile.close();
            sendData(2, data); // Send data to AddressBook (module 2)
            sendFeedback("Data loaded successfully.");
        } else {
            sendFeedback("Failed to load data.");
        }
    }

    void sendFeedback(const std::string& feedbackMessage) {
        json responsePackage = {
            {"feedback", feedbackMessage}
        };
        sendData(1, responsePackage); // Send response to user interface (module 1)
    }
};

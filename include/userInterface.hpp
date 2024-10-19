#pragma once

#include <iostream>
#include <string>
#include "json.hpp"
#include "IModule.hpp"
#include "dataTransfer.hpp"

using json = nlohmann::json;

class userInterface : public IModule {
public:
    userInterface() {
        this->moduleCode = 1;
    }

    void retrieveData(const json& dataPackage) override {
        std::cout << "UserInterface received data: " << dataPackage.dump() << std::endl;
        handleResponse(dataPackage);
    }

    void sendData(const int& targetModuleCode, const json& dataPackage) override {
        std::cout << "UserInterface sending data to module " << targetModuleCode << std::endl;

        dt->retrieveData(dataPackage);
    }
    
    void setDataTransfer(dataTransfer* dt) override {
            this->dt = dt;
    }
    
    void showMenu() {
        int userRequest = -1;

        std::cout << "=== Address Book Management System ===" << std::endl;
        std::cout << "1. Initialize Contacts" << std::endl;
        std::cout << "2. Display Contacts" << std::endl;
        std::cout << "3. Edit Contact" << std::endl;
        std::cout << "4. Remove Contact" << std::endl;
        std::cout << "5. Exit" << std::endl;
        std::cout << "Please select your option (1-5): ";
        std::cin >> userRequest;

        if (userRequest != 5) {
            json commandPackage = {
                {"sourceModuleCode", 1},
                {"targetModuleCode", 2},
                {"requestCode", userRequest}
            };
            sendData(2, commandPackage);
        } else {
            std::cout << "Exiting..." << std::endl;
        }
    }

private:
    dataTransfer* dt;

    void handleResponse(const json& responsePackage) {
        std::string feedback = responsePackage.value("feedback", "No feedback");
        std::cout << "Response from module: " << feedback << std::endl;
        showMenu();
    }
};

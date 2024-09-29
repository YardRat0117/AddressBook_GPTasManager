#pragma once

#include <iostream>
#include <string>
#include "json.hpp"
#include "Interface.hpp"
#include "dataTransfer.hpp"

using json = nlohmann::json;

/*
Request Code
feedbackDisplayer   ->  0
*/

class userInterface : public IUserInterface {
    protected:
        // request
        void requestHandler(const json& requestPackage) override {
            int requestCode = requestPackage["requestCode"];
            switch (requestCode) {
            case 0:
                feedbackDisplayer(requestPackage["ABFeedback"]);
                break;
            
            default:
                break;
            }
        }

        // function
        void userRequestHandler() override {
            int userRequest = -1;

            // interact with user
            showMenu();
            std::cin >> userRequest;

            // transcript request
            int requestCode;
            switch (userRequest) {
            case 1:
                // Add New Contact
                break;
             
            case 2:
                // Delete Contact
                break;

            case 3:
                // Search for Contact
                break;

            case 4:
                // Display All Contacts
                break;
                
            default:
                break;
            }
            
            // detect whether exit
            if(userRequest != 5) {
                // pack command package
                json commandPackage = this->requestWrapper(this->moduleCode, 1, requestCode);

                // send package
                this->sendData(commandPackage);
            }
        }

        void feedbackDisplayer(const std::string ABFeedback) override {
            std::cout << ABFeedback << std::endl;
            this->userRequestHandler();
        }

        void showMenu() {
            std::cout << "=== Contact Management System ===" << std::endl;
            std::cout << "1. Add New Contact" << std::endl;
            std::cout << "2. Delete Contact" << std::endl;
            std::cout << "3. Search for Contact" << std::endl;
            std::cout << "4. Display All Contacts" << std::endl;
            std::cout << "5. Exit" << std::endl;
            std::cout << "==================================" << std::endl;
            std::cout << "Please enter your choice (1-5): ";
        }

};
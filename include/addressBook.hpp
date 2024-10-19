#pragma once

#include <iostream>
#include <unordered_map>
#include "json.hpp"
#include "IModule.hpp"
#include "dataTransfer.hpp"

using json = nlohmann::json;

class addressBook : public IModule {
public:
    addressBook() {
        this->moduleCode = 2;
    }

    // Handle incoming requests
    void retrieveData(const json& dataPackage) override {
        int requestCode = dataPackage.value("requestCode", -1);

        switch (requestCode) {
            case 1:
                initializeContacts();
                break;
            case 2:
                displayContacts();
                break;
            case 3:
                editContact();
                break;
            case 4:
                removeContact();
                break;
            default:
                std::cerr << "Unknown request code received." << std::endl;
        }
    }

    // Send data to target module
    void sendData(const int& targetModuleCode, const json& dataPackage) override {
        if (dt) {
            dt->retrieveData(dataPackage);
        } else {
            std::cerr << "Error: No dataTransfer module set." << std::endl;
        }
    }

    void setDataTransfer(dataTransfer* dt) override {
            this->dt = dt;
    }

    // Initialize some dummy contacts
    void initializeContacts() {
        contacts = {
            {1, {"John Doe", "123456789"}},
            {2, {"Jane Smith", "987654321"}},
            {3, {"Alice Brown", "555444333"}}
        };

        json response = {
            {"feedback", "Contacts initialized successfully."}
        };
        sendData(1, response); // Send feedback to userInterface
    }

    // Display all contacts
    void displayContacts() {
        json response;
        if (contacts.empty()) {
            response["feedback"] = "No contacts available.";
        } else {
            for (const auto& contact : contacts) {
                response["contacts"].push_back({
                    {"id", contact.first},
                    {"name", contact.second.first},
                    {"phone", contact.second.second}
                });
            }
            response["feedback"] = "Contacts displayed successfully.";
        }
        sendData(1, response); // Send contact list to userInterface
    }

    // Edit a contact
    void editContact() {
        int id;
        std::cout << "Enter contact ID to edit: ";
        std::cin >> id;

        if (contacts.find(id) != contacts.end()) {
            std::string newName, newPhone;
            std::cout << "Enter new name: ";
            std::cin >> newName;
            std::cout << "Enter new phone number: ";
            std::cin >> newPhone;

            contacts[id] = {newName, newPhone};
            json response = {
                {"feedback", "Contact edited successfully."}
            };
            sendData(1, response);
        } else {
            json response = {
                {"feedback", "Contact not found."}
            };
            sendData(1, response);
        }
    }

    // Remove a contact
    void removeContact() {
        int id;
        std::cout << "Enter contact ID to remove: ";
        std::cin >> id;

        if (contacts.erase(id) > 0) {
            json response = {
                {"feedback", "Contact removed successfully."}
            };
            sendData(1, response);
        } else {
            json response = {
                {"feedback", "Contact not found."}
            };
            sendData(1, response);
        }
    }

private:
    dataTransfer* dt;
    std::unordered_map<int, std::pair<std::string, std::string>> contacts; // ID -> (name, phone)
};

#pragma once

#include <iostream>
#include "json.hpp"
#include "Interface.hpp"
#include "dataTransfer.hpp"

using json = nlohmann::json;

class userInterface : public IUserInterface {
    public:
        // input
        void retrieveData(const json& dataPackage) override {
            // unpack the data package
            // allocate specific data to specific retrieve pipe
        }

    protected:
        // output
        void sendData() override {
            // pack the data package
            // notify the target module for the dataTransfer module
            // call the dataTransfer module's input
        }
};
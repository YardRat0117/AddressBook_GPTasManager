#pragma once

#include <iostream>
#include "json.hpp"
#include "Interface.hpp"

const int MAX_MODULES = 5;

using json = nlohmann::json;

class dataTransfer : public IDataTransfer {
    public:
        // constructor
        dataTransfer(IModule* ui, IModule* ab, IModule* qe, IModule* c, IModule* s) {
            this->moduleArray[0] = ui;
            this->moduleArray[1] = ab;
            this->moduleArray[2] = qe;
            this->moduleArray[3] = c;
            this->moduleArray[4] = s;
        }
        // input
        void retrieveData(const json& dataPackage) override {
            int targetModuleCode = dataPackage["targetModuleCode"];
            this->sendData(targetModuleCode, dataPackage);
        }

        // deconstructor
        ~dataTransfer() override { /* there's nothing to do so far */ }

    protected:
        // attribute
        IModule* moduleArray[MAX_MODULES];

        // output
        void sendData(const int& targetModuleCode, const json& dataPackage) override {
            this->moduleArray[targetModuleCode]->retrieveData(dataPackage);
        }
};
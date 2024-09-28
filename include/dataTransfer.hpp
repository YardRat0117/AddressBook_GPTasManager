#pragma once

#include <iostream>
#include "json.hpp"
#include "Interface.hpp"

#define MAX_MODULES 4

using json = nlohmann::json;

class dataTransfer : public IDataTransfer {
    public:
        // constructor
        dataTransfer(const IModule* ui, const IModule* ab, const IModule* qe, const IModule* s) {
            this->moduleArray[0] = ui;
            this->moduleArray[1] = ab;
            this->moduleArray[2] = qe;
            this->moduleArray[3] = s;
        }
        // input
        void retrieveData(const json& dataPackage) override {
            int targetModuleCode = dataPackage["targetModuleCode"];
            this-sendData(targetModuleCode, dataPackage);
        }

        // deconstructor
        ~dataTransfer() override { /* there's nothing to do so far */ }

    protected:
        // attribute
        const IModule* moduleArray[MAX_MODULES];

        // output
        void sendData(const int& targetModuleCode, const json& dataPackage) override {
            this->moduleArray[targetModuleCode]->retrieveData(dataPackage);
        }
};
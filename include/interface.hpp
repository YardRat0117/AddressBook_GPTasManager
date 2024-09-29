#pragma once

#include <iostream>
#include "json.hpp"

using json = nlohmann::json;

/*
Module Code
Contact         ->  -1
User Interface  ->  0
Address Book    ->  1
Query Engine    ->  2
Contact         ->  3
Storage         ->  4

Data Package Format
dataPackage {
    "sourceModuleCode" : int,   // Code of the module sending the data
    "targetModuleCode" : int,   // Code of the module receiving the data
    "requestCode" : int,        // Request code referring to specific action of the target module
    // additional fields as needed
}
*/


class IDataTransfer {
    public:
        // input
        virtual void retrieveData(const json& dataPackage) = 0;

        // deconstructor
        virtual ~IDataTransfer() {}

    protected:
        // output
        virtual void sendData(const int& targetModuleCode, const json& dataPackage) = 0;
};


class IModule{
    public:
        // input
        void retrieveData(const json& dataPackage) {
            this->requestHandler(dataPackage);
        }

        // initialization
        void initialize(IDataTransfer* dt, int moduleCode) {
            this->dt = dt;
            this->moduleCode = moduleCode;
        }

        // deconstructor
        virtual ~IModule() {}

    protected:
        // attribute
        IDataTransfer* dt = nullptr;
        int moduleCode;

        // request
        virtual void requestHandler(const json& requestPackage) = 0;

        json requestWrapper(const int sourceModuleCode, const int targetModuleCode, const int requestCode) {
            json requestPackage;
            requestPackage["sourceModuleCode"] = sourceModuleCode;
            requestPackage["targetModuleCode"] = targetModuleCode;
            requestPackage["requestCode"] = requestCode;
            return requestPackage;
        }

        // output
        void sendData(const json& dataPackage) {
            this->dt->retrieveData(dataPackage);
        }

};

class IUserInterface : public IModule {
    public:
        // deconstructor
        virtual ~IUserInterface() {}

    protected:
        // function
        virtual void userRequestHandler() = 0;
        virtual void feedbackDisplayer(const std::string ABFeedback) = 0;
        virtual void showMenu() = 0;
};

class IAddressBook : public IModule {
    public:
        // deconstructor
        virtual ~IAddressBook() {}

    protected:
        // function
        virtual void contactInitialization() = 0;
        virtual void contactPresentation() = 0;
        virtual void contactEditing() = 0;
        virtual void contactRemoval() = 0;
};

class IQueryEngine : public IModule {
    public:
        // deconstructor
        virtual ~IQueryEngine() {}

    protected:
        // function
        virtual void contactQuery() = 0;
        virtual void contactTargating() = 0;
};

class IContact : public IModule{
    public:
        // deconstructor
        virtual ~IContact() {}

    protected:
        // function
        virtual void infoEntry() = 0;
        virtual void infoRetrieval() = 0;
        virtual void infoEditing() = 0;
};

class IStorage : public IModule{
    public:
        // deconstructor
        virtual ~IStorage() {}
        
    protected:
        // function
        virtual void dataArchiving() = 0;
        virtual void dataIngestion() = 0;
};
#pragma once

#include <iostream>
#include "json.hpp"

using json = nlohmann::json;

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

/*
Module Code
Data Transfer   ->      -1
User Interface  ->      0
Address Book    ->      1
Query Engine    ->      2
Storage         ->      3
*/

class IModule{
    public:
        // input
        virtual void retrieveData(const json& data) = 0;

        // deconstructor
        virtual ~IModule() {}

    protected:
        // output
        virtual void sendData() = 0;

};

class IUserInterface : public IModule {
    public:
        // deconstructor
        virtual ~IUserInterface() {}

    protected:
        // input
        virtual void retrieveRequest() = 0;
        virtual void retrieveABFeedback() = 0;

        // output
        virtual void sendCommand() = 0;
        virtual void sendQueryRequest() = 0;

        // function
        virtual void requestHanlder() = 0;
        virtual void feedbackDisplayer() = 0;
};

class IAddressBook : public IModule {
    public:
        // deconstructor
        virtual ~IAddressBook() {}

    protected:
        // input
        virtual void retrieveCommand() = 0;
        virtual void retrieveTarget() = 0;
        virtual void retrieveCFeedback() = 0;

        // output
        virtual void sendABFeedback() = 0;
        virtual void sendOperation() = 0;

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
        // input
        virtual void retrieveQueryRequest() = 0;
        virtual void retrieveQueryResult() = 0;

        // output
        virtual void sendTarget() = 0;
        virtual void sendQueryInfo() = 0;

        // function
        virtual void contactQuery() = 0;
        virtual void contactTargating() = 0;
};

class IContact : public IModule{
    public:
        // deconstructor
        virtual ~IContact() {}

    protected:
        // input
        virtual void retirveOperation() = 0;
        virtual void retriveContactLoading() = 0;

        // output
        virtual void sendCFeedback() = 0;
        virtual void sendContactVariation() = 0;

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
        // input
        virtual void retriveContactVariation() = 0;
        virtual void retriveQueryInfo() = 0;
        
        // output
        virtual void sendContactLoading() = 0;
        virtual void sendQueryResult() = 0;
        
        // function
        virtual void dataArchiving() = 0;
        virtual void dataIngestion() = 0;
};
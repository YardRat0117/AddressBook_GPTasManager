#pragma once

#include "json.hpp"

class dataTransfer;

class IModule {
public:
    virtual ~IModule() = default;

    virtual void retrieveData(const nlohmann::json& dataPackage) = 0;
    virtual void sendData(const int& targetModuleCode, const nlohmann::json& dataPackage) = 0;

    virtual void setDataTransfer(dataTransfer* dt) = 0;

protected:
    int moduleCode;
    dataTransfer* dt = nullptr; // 默认初始化为 nullptr
};

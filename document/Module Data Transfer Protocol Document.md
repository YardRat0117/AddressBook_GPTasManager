# Module Data Transfer Protocol Document

## 1. Purpose
This protocol defines the communication method between different modules in the system. Each module communicates by sending and receiving data packets through the `dataTransfer` class, which acts as a central data relay.

## 2. Data Packet Format
Data packets are structured in JSON format and contain the following fields:

```json
{
    "sourceModuleCode": int,  // Identifier of the sending module
    "targetModuleCode": int,  // Identifier of the receiving module
    "requestCode": int,       // Type of request (e.g., initialization, update, query)
    "payload": { /* specific data */ }  // Module-specific data
}
```

### Field Descriptions
- **sourceModuleCode**: Identifies the module sending the data.
- **targetModuleCode**: Identifies the module receiving the data.
- **requestCode**: Specifies the operation being requested (e.g., initialization, query, update).
- **payload**: Contains additional information specific to the request, such as contact data or query results.

## 3. IModule Interface
The `IModule` interface defines the following core functions for all modules:

- **retrieveData(const json& dataPackage)**: This method processes data received from another module via the `dataTransfer`. It handles incoming data packets and performs module-specific operations based on the `requestCode`.

- **sendData(const json& dataPackage)**: This method sends data packets to other modules. It does not send the data directly but delegates the operation to the central `dataTransfer` instance, which manages the routing between modules.

## 4. dataTransfer Class
The `dataTransfer` class plays a central role in inter-module communication. It is responsible for routing data between modules and ensuring the correct delivery of data packets.

### Key Functions
- **retrieveData(const json& dataPackage)**: Receives data from a module and routes it to the appropriate target module, based on the `targetModuleCode`.

- **sendData(const int& targetModuleCode, const json& dataPackage)**: This method is used by all modules to send data. The module calls this function, and `dataTransfer` handles the routing to the target module.

### Implementation
1. **All communication is handled by `dataTransfer`**: Modules do not communicate with each other directly. Instead, they use `dataTransfer` to send and receive data.
2. **Module Routing**: The `dataTransfer` class determines the target module using the `targetModuleCode` in the data packet and invokes the `retrieveData` method of the target module.

## 5. Data Transfer Example
Below is an example of a module (e.g., `userInterface`) sending a data packet:

```cpp
json commandPackage = {
    {"sourceModuleCode", this->moduleCode},
    {"targetModuleCode", 1}, // Targeting addressBook module
    {"requestCode", 1}, // Request for initialization
    {"payload", /* specific data */ }
};
this->sendData(commandPackage);  // Call sendData to initiate communication
```

In this example, `userInterface` sends the packet to the `dataTransfer`, which routes the data to the `addressBook` module for processing.

## 6. Exception Handling
The following exceptions should be handled during data communication:
- Invalid `targetModuleCode`: Ensure that the target module is valid and can process the data.
- Failed data processing: Implement fallback mechanisms if a module cannot handle a request.

## 7. Version Control
- **Version**: 1.0
- **Date**: 2024-10-19
- **Author**: YardRat

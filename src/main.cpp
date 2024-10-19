#include "dataTransfer.hpp"
#include "userInterface.hpp"
#include "addressBook.hpp"
#include "dataStorage.hpp"

int main() {
    dataTransfer dt;

    userInterface ui;
    addressBook ab;
    dataStorage ds;

    // Register modules
    dt.registerModule(1, &ui);
    dt.registerModule(2, &ab);
    dt.registerModule(3, &ds);

    // Set data transfer references
    ui.setDataTransfer(&dt);
    ab.setDataTransfer(&dt);
    ds.setDataTransfer(&dt);

    // Start the user interface
    ui.showMenu();

    return 0;
}

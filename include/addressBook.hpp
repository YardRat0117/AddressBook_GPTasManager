#pragma once

#include <iostream>
#include <string>
#include "json.hpp"
#include "interface.hpp"
#include "dataTransfer.hpp"

using json = nlohmann::json;

/*
Request Code
feedbackDisplayer       ->      0
contactInitialization   ->      1
contactPresentation     ->      2
contactEditing          ->      3
contactRemoval          ->      4
*/

class addressBook : public IAddressBook {
    protected:
        // function
        void contactInitialization() {
            // TODO
        }

        void contactPresentation() {
            // TODO
        }

        void contactEditing() {
            // TODO
        }

        void contactRemoval() {
            // TODO
        }
};
#include "form.h"

form::form(crud crud_operation) {
    this->crud_operation = crud_operation;
    this->tree = nullptr;
}

std::string toString(crud c) {
    switch (c) {
        case CRUD_INSERT:
            return "+";
        case CRUD_DELETE:
            return "-";
        case CRUD_FIND:
            return "?";
        case CRUD_UPDATE:
            return "=";
    }
}

form::form() = default;

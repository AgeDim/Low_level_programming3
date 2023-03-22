#include "list_element.h"

list_element::list_element(std::string id) {
    this->next = nullptr;
    this->element = id;
}


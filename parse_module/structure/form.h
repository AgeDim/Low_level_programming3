#ifndef LOW_LEVEL_PROGRAMMING2_FORM_H
#define LOW_LEVEL_PROGRAMMING2_FORM_H

#include <cstdint>
#include <string>
#include "field.h"

enum crud {
    CRUD_INSERT = '+',
    CRUD_DELETE = '-',
    CRUD_FIND = '?',
    CRUD_UPDATE = '='
};
std::string toString(crud c);

struct form {
    enum crud crud_operation;
    struct list_level *tree;

    explicit form(crud crud_operation);
    form();
};
#endif //LOW_LEVEL_PROGRAMMING2_FORM_H

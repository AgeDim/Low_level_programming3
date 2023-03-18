#ifndef LOW_LEVEL_PROGRAMMING2_FORM_H
#define LOW_LEVEL_PROGRAMMING2_FORM_H

#include <cstdint>
#include "field.h"

enum crud {
    CRUD_INSERT = '+',
    CRUD_DELETE = '-',
    CRUD_FIND = '?',
    CRUD_UPDATE = '=',
};


struct form {
private:
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & crud_operation;
        ar & tree;
    }

public:
    enum crud crud_operation;
    struct list_level *tree;

    explicit form(crud crud_operation);
    form();
};
#endif //LOW_LEVEL_PROGRAMMING2_FORM_H

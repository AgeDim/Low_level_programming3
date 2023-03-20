#include "response_filling.h"
#include "../parse_module/structure/list_level.h"


static std::string getOp(op *op) {
    std::string result;
    switch (op->type) {
        case INTEGER_TYPE:
            result = std::to_string(op->value.integer);
            break;
        case FLOAT_TYPE:
            result = std::to_string(op->value.real);
            break;
        case BOOLEAN_TYPE:
            result = std::to_string(op->value.boolean);
            break;
        case STRING_TYPE:
            char *tmp = op->value.string->value;
            for (int i = 0; i < op->value.string->size; i++) result += tmp[i];
            break;
    }
    return result;
}


view_t fill_response(form *form) {
    view_t response = view_t(toString(form->crud_operation));
    struct list_level *list_level = form->tree;
    struct filter_list *list_filter;
    struct comparator_list *comparator_list;
    int levels = 1;
    while (list_level != nullptr) {
        int any = 0;
        int id = 0;
        std::string relation;
        int lvl_negative = 0;
        switch (list_level->place) {
            case P_FREE:
                relation = "FREE RELATION";
                break;
            case P_ROOT:
                relation = "ROOT RELATION";
                break;
            case P_RELATIVE:
                relation = "CHILD RELATION";
                break;
            default:
                relation = "UNKNOWN RELATION";
                break;
        }
        if (list_level->any == 1) {
            any = 1;
        } else {
            id = list_level->value.element;
        }
        lvl_negative = list_level->negative;
        level t = level(levels, relation, lvl_negative, id, any);
        list_filter = list_level->filters;
        while (list_filter != nullptr) {
            int filters_id = 1;
            int filter_negative = list_filter->value->negative;
            filter_t filters = filter_t(filters_id, filter_negative);
            comparator_list = list_filter->value->comparators;
            while (comparator_list != nullptr) {
                int comparator_id = 1;
                int negative_comparator = 0;
                int field1 = comparator_list->value->op1->field;
                int field2 = comparator_list->value->op2->field;
                std::string oper1;
                std::string oper2;
                std::string operation;
                operator_t op1 = operator_t(oper1, field1);
                operator_t op2 = operator_t(oper2, field2);
                comparator_t comp = comparator_t(comparator_id, negative_comparator, op1, operation, op2);
                negative_comparator = comparator_list->value->negative;
                operation = comparator_list->value->operation;
                oper1 = getOp(comparator_list->value->op1);
                oper2 = getOp(comparator_list->value->op2);
                op1 = operator_t(oper1, field1);
                op2 = operator_t(oper2, field2);
                comp = comparator_t(comparator_id, negative_comparator, op1, operation, op2);
                filters.comparator().push_back(comp);
                comparator_list = comparator_list->next;
            }
            t.filter().push_back(filters);
            comparator_list = list_filter->value->comparators;
            list_filter = list_filter->next;
            filters_id++;
            response.level().push_back(t);
        }
        list_level = list_level->next;
        levels++;

    }

    return response;
}

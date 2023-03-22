#ifndef LAB1_DATABASE_H
#define LAB1_DATABASE_H

#include <utility>
#include <vector>
#include <cassert>

#include "m_data.h"
#include "node.h"
#include "util.h"

using namespace std;

struct database {
    string file;
    m_data meta_data;

    explicit database(const string &file);

    void create();

    void open();

    void save();

    void add_node(const vector<string> &par, node node);

    void update_node(vector<string> &p, const node &node);

    node find_node(const vector<string> &p);

    void delete_node(const vector<string> &p);

private:
    void del_node(int32_t pos);

    void add_data(const vector<string> &p, int32_t pos);

    void delete_data(int32_t pos);

    void add_valid(const vector<string> &par, const node &node);

    void update_valid(const vector<string> &par, const node &node);

    void find_valid(const vector<string> &p);

    void delete_valid(const vector<string> &p);

    static vector<string> parent(const vector<string> &p);

    static vector<string> child(const vector<string> &p, const string &name);
};

#endif

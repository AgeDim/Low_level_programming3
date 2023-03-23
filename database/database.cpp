#include "database.h"

using namespace std;

database::database(const string& file) {
    this->file = file;
}

void database::create() {
    meta_data.serialize(file, BIN);
}

void database::open() {
    meta_data.deserialize(file);
}

void database::save() {
    meta_data.serialize(file, BOI);
}

void database::add_data(const vector<string>& p, int64_t pos) {
    string key = path(p);
    meta_data.pos[key] = pos;
    meta_data.path[pos] = key;
    int32_t par = meta_data.pos[path(parent(p))];
    meta_data.child[par].insert(pos);
    meta_data.child[pos] = unordered_set<int64_t>();
}

void database::add_valid(const vector<string>& par, const node& node) {
    assert(!par.empty());
    assert(meta_data.pos.find(path(par)) != meta_data.pos.end());
    assert(meta_data.pos.find(path(child(par, node.name))) == meta_data.pos.end());
}

void database::add_node(const vector<string>& parent, node node) {
    add_valid(parent, node);

    node.id = ++meta_data.count;
    node.add("id", node.id);
    if (!meta_data.free.empty()) {
        node.id = meta_data.free.back();
        meta_data.free.pop_back();
    }

    node.serialize(file, node.id);
    add_data(child(parent, node.name), node.id);
}

void database::find_valid(const vector<string>& p) {
    assert(p.size() > 1);
    assert(meta_data.pos.find(path(p)) != meta_data.pos.end());
}

node database::find_node(const vector<string>& p) {
    find_valid(p);

    node n;
    n.deserialize(file, meta_data.pos[path(p)]);
    return n;
}

void database::delete_data(int64_t pos) {
    meta_data.count--;
    meta_data.free.push_back(pos);
    meta_data.child.erase(pos);
    meta_data.pos.erase(meta_data.path[pos]);
    meta_data.path.erase(pos);
}

void database::del_node(int64_t pos) {
    ofstream fout(file, BOI);
    cereal::BinaryOutputArchive obin(fout);

    vector<int32_t> v;
    v.push_back(pos);
    while (!v.empty()) {
        int32_t cur = v.back();
        v.pop_back();
        fout.seekp(META + KB4 * cur, ofstream::beg);

        for (int32_t c: meta_data.child[cur]) v.push_back(c);
        delete_data(cur);
    }
    fout.close();
}

void database::delete_valid(const vector<string>& p) {
    assert(p.size() > 1);
    assert(meta_data.pos.find(path(p)) != meta_data.pos.end());
}

void database::delete_node(const vector<string>& p) {
    delete_valid(p);

    int32_t pos = meta_data.pos[path(p)];
    int32_t par = meta_data.pos[path(parent(p))];
    meta_data.child[par].erase(pos);

    del_node(pos);
}

void database::update_valid(const vector<string>& p, const node& node) {
    assert(p.size() > 1);
    assert(meta_data.pos.find(path(p)) != meta_data.pos.end());
}

void database::update_node(vector<string>& p, const node& node) {
    update_valid(p, node);
    delete_node(p);
    p.pop_back();
    add_node(p, node);
}

vector<string> database::parent(const vector<string>& p) {
    vector<string> parent_path = p;
    parent_path.pop_back();
    return parent_path;
}

vector<string> database::child(const vector<string>& p, const string& name) {
    vector<string> new_path = p;
    new_path.emplace_back(name);
    return new_path;
}


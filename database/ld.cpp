#include "ld.h"

using namespace std;

void quick_ld(const string& file, size_t n) {
    database db(file);
    db.create();

    ofstream fout(file, BOI);
    cereal::BinaryOutputArchive obin(fout);

    for (int i = 0; i < n; i++) {
        fout.seekp(META + KB4 * i);
        string name = "load" + to_string(i);

        obin(++db.meta_data.count);
        obin(name);
        obin(unordered_map<string, attributes>());

        db.meta_data.child[0].insert(i + 1);
        db.meta_data.pos[name] = i + 1;
        db.meta_data.path[i + 1] = name;
    }

    fout.seekp(0);
    obin(db.meta_data.count);
    obin(db.meta_data.child);
    obin(db.meta_data.free);
    obin(db.meta_data.pos);
    obin(db.meta_data.path);

    fout.close();
}

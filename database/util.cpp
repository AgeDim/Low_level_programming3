#include "util.h"

using namespace std;

string path(const vector<string>& path) {
    string ret;
    for (const string& s : path) {
        ret += "/";
        ret += s;
    }
    return ret;
}

vector<string> to_vector(const string& path){
    vector<string> result;
    std::istringstream ss(path);
    std::string token;
    while (std::getline(ss, token, '/')) {
        result.push_back(token);
    }
    result.erase(result.begin());

    return result;
}
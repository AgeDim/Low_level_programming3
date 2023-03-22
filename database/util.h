#ifndef LAB1_UTIL_H
#define LAB1_UTIL_H
#include <fstream>
#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>

#define KB4 (4 * 1024)
#define META (256 * 1024 * 1024)
#define BOI (ios::binary | ios::out | ios::in)
#define BIN ios::binary

using namespace std;

string path(const vector<string>& path);

vector<string> to_vector(const string& path);
#endif

#pragma once
#include <vector>

using std::vector;

const vector<int> FULL_SET;
vector<vector<int>> v;
bool search(const int num, const vector<int> *vec);
void both(vector<int> *first, const vector<int> *other);
void invert(vector<int> *vec);
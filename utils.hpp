#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <iostream>

#include "proc.hpp"

using namespace std;

void DrawProcessesTree(process *proc);
string getStringArray(vector<int> arr);
void DumpProccessInfo(process *proc);
string colorfyString(string code, string str);

#endif /** UTILS_HPP */
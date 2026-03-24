#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <windows.h>
#include <vector>

struct ThreadData {
    std::vector<int>& vctr;
    int& min_idx;
    int& max_idx;
    double& avg;
    int n;
};

DWORD WINAPI min_max(LPVOID lpParam);
DWORD WINAPI average(LPVOID lpParam);

#endif

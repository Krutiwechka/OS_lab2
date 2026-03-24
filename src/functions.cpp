#include "functions.h"
#include <iostream>

DWORD WINAPI min_max(LPVOID lpParam) {
    ThreadData* data = static_cast<ThreadData*>(lpParam);
    data->min_idx = 0;
    data->max_idx = 0;

    for (int i = 1; i < data->n; ++i) {
        if (data->vctr[i] < data->vctr[data->min_idx]) {
            data->min_idx = i;
        }
        Sleep(7); 
        
        if (data->vctr[i] > data->vctr[data->max_idx]) {
            data->max_idx = i;
        }
        Sleep(7);
    }

    std::cout << "[min_max] Min value: " << data->vctr[data->min_idx] 
              << ", Max value: " << data->vctr[data->max_idx] << std::endl;
    return 0;
}

DWORD WINAPI average(LPVOID lpParam) {
    ThreadData* data = static_cast<ThreadData*>(lpParam);
    double sum = 0;

    for (int i = 0; i < data->n; ++i) {
        sum += data->vctr[i];
        Sleep(12);
    }

    data->avg = sum  / (data->n);
    std::cout << "[average] Arithmetic mean: " << data->avg << std::endl;
    return 0;
}

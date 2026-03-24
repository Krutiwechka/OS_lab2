#include "functions.h"
#include <iostream>
#include <vector>

int main() {
    int n;
    std::cout << "Enter array size (n)... ";
    std::cin >> n;
    
    if (n <= 0) {
        std::cerr << "n must be positive\n";
        return 1;
    }

    std::vector<int> vctr(n);
    std::cout << "Enter " << n << " elements... ";

    for (int i = 0; i < n; ++i)
        std::cin >> vctr[i];

    int min_idx = 0, max_idx = 0;
    double avg = 0.0;

    ThreadData data = {vctr, min_idx, max_idx, avg, n};

    HANDLE hMinMax = CreateThread(NULL, 0, min_max, &data, 0, NULL);
    HANDLE hAverage = CreateThread(NULL, 0, average, &data, 0, NULL);

    WaitForSingleObject(hMinMax, INFINITE);
    WaitForSingleObject(hAverage, INFINITE);

    vctr[min_idx] = static_cast<int>(avg);
    vctr[max_idx] = static_cast<int>(avg);

    std::cout << "Final array: ";
    for (int val : vctr)
        std::cout << val << ' ';
    std::cout << '\n';

    CloseHandle(hMinMax);
    CloseHandle(hAverage);

    system("pause");
    return 0;
}

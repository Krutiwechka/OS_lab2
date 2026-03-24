#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../doctest/doctest.h"
#include "../include/functions.h"
#include <windows.h>
#include <vector>

TEST_CASE("min_max: базовый поиск в неупорядоченном массиве")
{
    std::vector<int> numbers = {100, -50, 0, 45, -100, 200};
    int min_idx = 0, max_idx = 0;
    double avg = 0.0;
    ThreadData data = {numbers, min_idx, max_idx, avg, static_cast<int>(numbers.size())};

    min_max(&data);

    CHECK(data.min_idx == 4);
    CHECK(data.max_idx == 5);
    CHECK(numbers[data.min_idx] == -100);
    CHECK(numbers[data.max_idx] == 200);
}

TEST_CASE("min_max: массив из одинаковых элементов")
{
    std::vector<int> numbers = {7, 7, 7, 7};
    int min_idx = -1, max_idx = -1;
    double avg = 0.0;
    ThreadData data = {numbers, min_idx, max_idx, avg, 4};

    min_max(&data);
    CHECK(data.min_idx == 0);
    CHECK(data.max_idx == 0);
}

TEST_CASE("average: расчет для дробного результата")
{
    std::vector<int> numbers = {1, 2, 4};
    int min_idx, max_idx;
    double avg = 0.0;
    ThreadData data = {numbers, min_idx, max_idx, avg, 3};

    average(&data);

    CHECK(data.avg == doctest::Approx(2.33333).epsilon(0.001));
}

TEST_CASE("average: большие числа (проверка на точность)")
{
    std::vector<int> numbers = {1000000, 2000000, 3000000};
    int min_idx, max_idx;
    double avg = 0.0;
    ThreadData data = {numbers, min_idx, max_idx, avg, 3};
    average(&data);
    CHECK(data.avg == doctest::Approx(2000000.0));
}

TEST_CASE("Интеграция: работа через Win32 API с проверкой WaitForMultipleObjects")
{
    std::vector<int> numbers = {12, 44, 2, 18, 99, 33};
    int min_idx = 0, max_idx = 0;
    double avg = 0.0;
    ThreadData data = {numbers, min_idx, max_idx, avg, static_cast<int>(numbers.size())};

    HANDLE threads[2];
    threads[0] = CreateThread(NULL, 0, min_max, &data, 0, NULL);
    threads[1] = CreateThread(NULL, 0, average, &data, 0, NULL);

    REQUIRE(threads[0] != NULL);
    REQUIRE(threads[1] != NULL);

    DWORD wait = WaitForMultipleObjects(2, threads, TRUE, 5000); 
    CHECK(wait != WAIT_TIMEOUT);
    CHECK(wait != WAIT_FAILED);

    CHECK(numbers[data.min_idx] == 2);
    CHECK(numbers[data.max_idx] == 99);
    CHECK(data.avg == doctest::Approx(34.6666).epsilon(0.001));
    CloseHandle(threads[0]);
    CloseHandle(threads[1]);
}

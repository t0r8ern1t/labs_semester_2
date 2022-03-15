//сортировка подсчетом

#include <iostream>
#include <ctime>
#include <chrono>
#include "timer.hpp"

using namespace std;
using namespace chrono_literals;

void CountSort(int* arr, int n, int a) {
    int* counts = new int[a];
    for (int i = 0; i < a; ++i) { //создаем массив нулей
        counts[i] = 0;
    }
    for (int i = 0; i < n; ++i) { //увеличиваем те нули, позиция которых совпадает с элементами arr
        ++counts[arr[i]];
    }
    int k = 0;
    for (int i = 0; i < a; ++i) { // подменяем элементы arr на ненулевые элементы counts
        if (counts[i] != 0) {
            while (counts[i] != 0) {
                arr[k] = i;
                ++k;
                --counts[i];
            }
        }
    }
    delete[] counts;
}

void PrintArray(int* arr, int n) {
    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

void RandomElements(int* arr, int n, int a) {
    for (int i = 0; i < n; ++i) {
        arr[i] = rand() % a;
    }
    //PrintArray(arr, n);
}

int main()
{
    srand(time(0));
    int a = 100000; //разброс
    int n = 100000;   //количество элементов
    int* arr = new int[n];
    RandomElements(arr, n, a);
    ssh::Timer timer;
    CountSort(arr, n, a);
    cout << timer.elapsed() << endl;
    std::cout << std::endl;
    //PrintArray(arr, n);
    delete[] arr;

    return 0;
}
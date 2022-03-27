#include <iostream>
#include <ctime>
#include <chrono>
#include "timer.hpp"

using namespace std;
using namespace literals::chrono_literals;

void QuickSort(int* mas, int a, int b) {
    if (a >= b) {
        return;
    }
    int m = rand() % (b - a + 1) + a;
    int k = mas[m];
    int l = a - 1;
    int r = b + 1;
    while (true)
    {
        do {
            ++l;
        } while (mas[l] < k);

        do {
            --r;
        } while (mas[r] > k);

        if (l >= r)
            break;

        std::swap(mas[l], mas[r]);
    }
    r = l;
    l = l - 1;
    QuickSort(mas, a, l);
    QuickSort(mas, r, b);
}

int BinarySearch(int* arr, int left, int right, int key)
{
    int middle = 0;
    while (left < right)
    {
        middle = (left + right) / 2;
        if (key < arr[middle])
            right = middle - 1;
        else if (key > arr[middle])
            left = middle + 1;
        else
            return middle;
    }
    return -1;
}

int CycleSearch(int* arr, int n, int key) {
    for (int i = 0; i < n; ++i) {
        if (arr[i] == key) return i;
    }
    return -1;
}

void PrintArray(int* arr, int n) {
    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

void RandomElements(int* arr, int n) {
    for (int i = 0; i < n; ++i) {
        arr[i] = rand();
    }
}

int main()
{
    srand(time(0));
    int n = 100000;
    int m = 10000;

    int* arr = new int[n];
    RandomElements(arr, n);
    //PrintArray(arr, n);

    int* requests = new int[m];
    RandomElements(requests, m);
    QuickSort(arr, 0, n - 1);

    ssh::Timer timer;
    for (int i = 0; i < m; ++i) {
        int res = BinarySearch(arr, 0, n, requests[i]);
        //if (res == -1) cout << requests[i] << " " << "not found" << endl;
        //else cout << requests[i] << " " << res + 1 << endl;
    }
    cout << timer.elapsed() << endl << endl;

    timer.reset();

    for (int i = 0; i < m; ++i) {
        int res = CycleSearch(arr, n, requests[i]);
        //if (res == -1) cout << requests[i] << " " << "not found" << endl;
        //else cout << requests[i] << " " << res + 1 << endl;
    }
    cout << timer.elapsed() << endl;

    delete[] arr;
    delete[] requests;
    return 0;
}
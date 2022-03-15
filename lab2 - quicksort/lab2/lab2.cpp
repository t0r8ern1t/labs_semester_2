#include <iostream>
#include <ctime>
#include <chrono>
#include "timer.hpp"

using namespace std;
using namespace chrono_literals;

void QuickSort(int* mas, int a, int b) {
    if (a >= b) {
        return;
    }
    int m = rand() % (b - a + 1) + a;
    int k = mas[m];
    int l = a - 1;
    int r = b + 1;
    while(true)
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

void BubbleSort(int* mas, int n)
{
    for (int i = 1; i < n; i++)
    {
        if (mas[i] >= mas[i - 1])
        {
            continue;
        }
        int j = i - 1;
        while (j >= 0 && mas[j] > mas[j + 1])
        {
            std::swap(mas[j], mas[j + 1]);
            j = j - 1;
        }
    }
}

void RandomElements(int* mas, int n) {
    for (int i = 0; i < n; ++i) {
        mas[i] = rand();
        //cout << mas[i] << " ";
    }
}

int main()
{
    srand(time(0));
    int n = 10000;
    int* mas = new int[n];

    RandomElements(mas, n);
    ssh::Timer timer;
    QuickSort(mas, 0, n-1);
    cout << timer.elapsed() << endl;

    RandomElements(mas, n);
    timer.reset();
    BubbleSort(mas, n); // при 100 000 ~70 секунд
    cout << timer.elapsed() << endl;
    
    delete[] mas;
}
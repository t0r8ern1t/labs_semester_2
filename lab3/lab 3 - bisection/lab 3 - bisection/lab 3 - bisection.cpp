// f(x) = x - 10

#include <iostream>
#include <ctime>
#include <chrono>
#include <math.h>
#include "timer.hpp"

using namespace std;
using namespace chrono_literals;

using namespace std;

double F(double x) {
    return x - 10;
}

double FindSolution(double left, long double right, double eps) {
    double middle = 1;
    while (abs(right - left) / 2 > eps) {
        middle = (left + right) / 2;
        //cout << middle << " " << F(middle) << endl;
        if (F(middle) * F(left) < 0) right = middle;
        else if (F(middle) * F(right) < 0) left = middle;
        if (F(middle) == 0) break;
    }
    return middle;
}

int main()
{
    double max = pow(10, 308);
    double eps = pow(10, -4);
    ssh::Timer timer;
    cout << FindSolution(0, max, eps) << endl;
    cout << "time " << timer.elapsed() << endl;
    return 0;
}
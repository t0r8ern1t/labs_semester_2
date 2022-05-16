#define _USE_MATH_DEFINES
#include <BMP.hpp>
#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    try
    {
        mt::images::BMP test_bmp(200, 200);
        test_bmp.Open("in.bmp");
        test_bmp.Rotate(M_PI / 4);
        test_bmp.Save("before.bmp");
        test_bmp.Artefacts();
        test_bmp.Save("after.bmp");
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    try
    {
        mt::images::BMP square(200, 200);
        square.Open("in2.bmp");
        square.Rotate(M_PI / 4);
        square.Save("before2.bmp");
        square.Artefacts();
        square.Save("after2.bmp");
    }
    catch (const exception& e)
    {
        cerr << e.what() << endl;
    }

    return 0;
}


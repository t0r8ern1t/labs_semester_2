#include <iostream>
#include <fstream>
#include "bmp.hpp"

using namespace ssh;
using namespace std;

int main()
{  
    BMP test(200, 200);
    test.Read("in.bmp");
    test.Colors();
    test.Write("test.bmp");
    
    return 0;
}
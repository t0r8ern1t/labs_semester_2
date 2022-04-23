#include <iostream>
#include <fstream>
#include "bmp.hpp"

using namespace ssh;
using namespace std;

int main()
{  
    BMP test(200, 200);
    test.Read("in.bmp");
    test.Decrypt();
    test.Write("test.bmp");
    test.Read("test.bmp");
    test.Encrypt();
    test.Write("test2.bmp");
    
    return 0;
}
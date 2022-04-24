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
    test.Write("decrypted.bmp");
    test.Read("decrypted.bmp");
    test.Encrypt();
    test.Write("encrypted.bmp");
    
    return 0;
}
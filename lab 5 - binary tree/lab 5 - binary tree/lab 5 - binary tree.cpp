#include <iostream>
#include <fstream>
#include <string>
#include "methods.hpp"

using namespace std;
using namespace ssh;

int main()
{
    Elem* root = nullptr;
    ifstream in("input.txt");
    int x = stoi("1");
    while (!in.eof()) {
        string command;
        in >> command;
        if (command[0] == '+') 
        {
            command.erase(0, 1);
            ADD(stoi(command), root);
        }
        else if (command[0] == '-')
        {
            command.erase(0, 1);
            DELETE(stoi(command), root);
        }
        else if (command[0] == '?') 
        {
            int x = 0;
            command.erase(0, 1);
            int result = NUMSEARCH(stoi(command), root, x);
            if (result != -1)
            {
                cout << command << " " << result << endl;
            }
            else cout << command  << " " << "n" << endl;
        }
    }

    CLEAR(root);
    delete root;

    return 0;
}

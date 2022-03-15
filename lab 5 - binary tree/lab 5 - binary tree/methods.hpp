#pragma once

namespace ssh {

    struct Elem
    {
        int data;
        Elem* left;
        Elem* right;
        Elem* parent;
    };

    Elem* MAKE(int data, Elem* p);

    void ADD(int data, Elem*& root);

    int NUMSEARCH(int data, Elem* v, int &index);

    Elem* SEARCH(int data, Elem* v);

    void DELETE(int data, Elem*& root);

    void PRINT(Elem* v);

    void CLEAR(Elem*& v);
}
#include <iostream>
#include "methods.hpp"

namespace ssh 
{

    Elem* MAKE(int data, Elem* p)
    {
        Elem* q = new Elem;
        q->data = data;
        q->left = nullptr;
        q->right = nullptr;
        q->parent = p;
        return q;
    }

    void ADD(int data, Elem*& root)
    {
        if (root == nullptr) {
            root = MAKE(data, nullptr);
            return;
        }
        Elem* v = root;
        while ((data < v->data && v->left != nullptr) || (data > v->data && v->right != nullptr))
            if (data < v->data)
                v = v->left;
            else
                v = v->right;
        if (data == v->data)
            return;
        Elem* u = MAKE(data, v);
        if (data < v->data)
            v->left = u;
        else
            v->right = u;
    }

    int NUMSEARCH(int data, Elem* v, int &index)
    {
        ++index;
        if (v == nullptr)
            return -1;
        if (v->data == data)
            return index;
        if (data < v->data)
            return NUMSEARCH(data, v->left, index);
        else
            return NUMSEARCH(data, v->right, index);
    }

    Elem* SEARCH(int data, Elem* v)    
    {
        if (v == nullptr)
            return v;
        if (v->data == data)
            return v;
        if (data < v->data)
            return SEARCH(data, v->left);
        else
            return SEARCH(data, v->right);
    }


    void DELETE(int data, Elem*& root)
    {
        Elem* u = SEARCH(data, root);
        if (u == nullptr)
            return;

        if (u->left == nullptr && u->right == nullptr && u == root)
        {
            delete root;
            root = nullptr;
            return;
        }

        if (u->left == nullptr && u->right != nullptr && u == root)
        {
            Elem* t = u->right;
            while (t->left != nullptr)
                t = t->left;
            u->data = t->data;
            u = t;
        }

        if (u->left != nullptr && u->right == nullptr && u == root)
        {
            Elem* t = u->left;
            while (t->right != nullptr)
                t = t->right;
            u->data = t->data;
            u = t;
        }

        if (u->left != nullptr && u->right != nullptr)
        {
            Elem* t = u->right;
            while (t->left != nullptr)
                t = t->left;
            u->data = t->data;
            u = t;
        }
        Elem* t;
        if (u->left == nullptr)
            t = u->right;
        else
            t = u->left;
        if (u->parent->left == u)
            u->parent->left = t;
        else
            u->parent->right = t;
        if (t != nullptr)
            t->parent = u->parent;
        delete u;
    }



    void PRINT(Elem* v)
    {
        if (v == nullptr)
            return;
        PRINT(v->left);
        std::cout << v->data << std::endl;
        PRINT(v->right);
    }


    void CLEAR(Elem*& v)
    {
        if (v == nullptr)
            return;
        CLEAR(v->left);
        CLEAR(v->right);

        delete v;
        v = nullptr;
    }
}
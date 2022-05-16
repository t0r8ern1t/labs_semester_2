#include <iostream>

class Foo
{
public:
    Foo() { i = nullptr; }
    Foo(int j) { i = new int[j]; }
    virtual ~Foo() { delete i; }
private:
    int* i;
};

class Bar : public Foo
{
public:
    Bar(int j) { i = new char[j]; }
    ~Bar() { delete i; }
private:
    char* i;
};


void main()
{
    Foo* f = new Foo(100);
    Foo* b = new Bar(200);
    *f = *b;
    std::cout << f;
    delete f;
    delete b;
}

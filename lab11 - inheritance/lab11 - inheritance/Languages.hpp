#pragma once
#include <iostream>
#include <string>
#include <vector>

class Languages {
protected:
    std::string m_extension;
public:
    Languages() {
        std::cout << "Base class: CONSTRUCTOR" << std::endl;
    };
    virtual ~Languages() {
        std::cout << "Base class: DESTRUCTOR" << std::endl;
    };

    virtual std::string someCodeRelatedThing() = 0;

};
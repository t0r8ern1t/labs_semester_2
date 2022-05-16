#pragma once
#include "Languages.hpp"

class PHP : public Languages {
private:
public:
    PHP() : Languages() {

        std::cout << "PHP constructor" << std::endl;
        m_extension = "php";
    };
    virtual ~PHP() {
        std::cout << "PHP class: destructor" << std::endl;
    };
    std::string someCodeRelatedThing() override {
        std::cout << "PHP class: someCodeRelatedThing function" << std::endl;
        std::string code = "php_code." + m_extension;
        return code;
    }
};
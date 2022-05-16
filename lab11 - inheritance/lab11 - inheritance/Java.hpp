#pragma once
#include "Languages.hpp"

class Java : public Languages {
private:
public:
    Java() : Languages() {

        std::cout << "Java constructor" << std::endl;
        m_extension = "java";
    };
    virtual ~Java() {
        std::cout << "Java class: destructor" << std::endl;
    };
    std::string someCodeRelatedThing() override {
        std::cout << "Java class: someCodeRelatedThing function" << std::endl;
        std::string code = "java_code." + m_extension;
        return code;
    }
};

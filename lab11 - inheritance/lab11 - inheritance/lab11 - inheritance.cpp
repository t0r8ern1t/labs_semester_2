#include "CodeGenerator.hpp"

int main() {
    std::string input;
    std::cin >> input;
    try {
        std::string code = generateCode(input);
        std::cout << code << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Caught: " << e.what() << std::endl;
        std::cerr << "Type: " << typeid(e).name() << std::endl;
    }
    return 0;
}
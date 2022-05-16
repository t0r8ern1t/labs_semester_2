#include <iostream>
#include <map>
#include "Teacher.hpp"

int main() {
    auto John{ std::make_shared<Student>("John") };
    auto Ben{ std::make_shared<Student>("Ben") };
    auto MrSmith{ std::make_shared<Teacher>("Mr.Smith") };

    MrSmith->addStudent(John);
    MrSmith->addStudent(Ben);
    MrSmith->getStudents();
    Ben->getTeacher();

    return 0;
}
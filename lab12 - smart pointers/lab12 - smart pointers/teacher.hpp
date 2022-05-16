#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "student.hpp"

class Teacher {
    std::string m_name;
    std::vector<std::shared_ptr<Student>> m_students;
public:
    Teacher(const std::string& name) {
        m_name = name;
        std::cout << m_name << " created" << std::endl;
    }
    ~Teacher() {
        std::cout << m_name << " destroyed" << std::endl;
    }

    std::string getName() {
        return m_name;
    }

    void addStudent(const std::shared_ptr<Student>& student) {
        if (!student) {
            std::cout << "empty student" << std::endl;
        }
        else {
            m_students.emplace_back(student);
            std::cout << "new student!" << std::endl;
        }
    }

    void getStudents() {
        std::cout << "m_name" << "'s students: " << std::endl;
        for (auto i : m_students) {
            std::cout << i.get()->getName() << " ";
        }
        std::cout << std::endl;
    }
};
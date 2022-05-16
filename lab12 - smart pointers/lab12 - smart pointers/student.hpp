#pragma once
#include <iostream>
#include <memory>
#include <string>
#include "teacher.hpp"

class Student {
    std::string m_name;
    std::weak_ptr<Teacher> m_teacher;
public:

    Student(const std::string& name) {
        m_name = name;
        std::cout << m_name << " created" << std::endl;
    }

    ~Student() {
        std::cout << m_name << " destroyed" << std::endl;
    }

    std::string getName() {
        return m_name;
    }

    void getTeacher() {
        std::shared_ptr<Teacher> t = m_teacher.lock();
        auto p = t.get();
        std::cout << p->getName() << " ";
    }
};
#ifndef CLASS_H_
#define CLASS_H_

#include "Student.h"
#include <string>
#include <utility>
#include <vector>

class Class {
private:
    std::vector<StudentWrapper> students;

public:
    const std::string name;
    const int point;
    Class(std::string name, const int point)
        : name(std::move(name)), point(point) { }

    void addStudent(const Student &st);
    StudentWrapper &getStudentWrapper(const std::string &studentId);
    double getAvgScore();
};

#endif // CLASS_H_

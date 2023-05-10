#include "Class.h"
#include <string>
#include "Student.h"

void Class::addStudent(const Student &st)
{
    StudentWrapper sw(st.id, st);
    students.push_back(sw);
}

StudentWrapper &Class::getStudentWrapper(const std::string &studentId)
{
    for (StudentWrapper& student : students) {
        if (student.id == studentId)
            return student;
    }
}

double Class::getAvgScore()
{
    // TODO: implement getAvgScore.
    double total = 0;
    int num = 0;
    for (const StudentWrapper& it : students) {
        num++;
        total += it.getScore();
    }
    return total / num;
}

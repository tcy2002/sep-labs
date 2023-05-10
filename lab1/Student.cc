#include "Student.h"
#include <string>
#include <sstream>
#include "Class.h"

std::string Student::toString() const
{
    // TODO: uncomment the following code after implementing class Student.
    std::ostringstream oss;
    oss << "Student Information:"
        << "\n\tid: " << id
        << "\n\tname: " << name
        << "\n\tenrollment year: " << year
        << "\n\tdegree: " << (degree == graduate ? "graduate" : "undergraduate")
        << std::endl;
    return oss.str();
}

// TODO: implement functions which are declared in Student.h.
void Student::addClass(Class* c)
{
    classes.push_back(c);
}

double Graduate::getGrade()
{
    double total = 0;
    int points = 0;
    double g, p;

    for (Class* it : classes) {
        points += it->point;
        g = it->getStudentWrapper(id).getScore();
        if (g >= 90)
            p = 4.0;
        else if (g >= 80)
            p = 3.5;
        else if (g >= 70)
            p = 3.0;
        else if (g >= 60)
            p = 2.5;
        else
            p = 2.0;
        total += p * it->point;
    }

    return total / points;
}

double Undergraduate::getGrade()
{
    double total = 0;
    int points = 0;
    double g;

    for (Class* it : classes) {
        points += it->point;
        g = it->getStudentWrapper(id).getScore();
        total += g / 20 * it->point;
    }

    return total / points;
}



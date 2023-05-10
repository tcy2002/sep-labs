#ifndef STUDENT_H_
#define STUDENT_H_

#include <string>
#include <utility>
#include <vector>

class Class;

enum Degree {
    undergraduate,
    graduate
};

class Student {
    // TODO: implement class Student.
private:
    std::string name;
    std::string year;
    Degree degree;
protected:
    std::vector<Class*> classes;
public:
    const std::string id;
    std::string toString() const;
    void addClass(Class* c);
    virtual double getGrade()=0;
    explicit Student(std::string id, std::string n, std::string y, Degree d) : id(std::move(id)), name(std::move(n)), year(std::move(y)), degree(d){}
    ~Student()= default;
};

// TODO: implement class Graduate.
class Graduate : public Student {
public:
    double getGrade() override;
    Graduate(std::string id, std::string n, std::string y) : Student(std::move(id), std::move(n), std::move(y), graduate) {}
};

// TODO: implement class Undergraduate.
class Undergraduate : public Student {
public:
    double getGrade() override;
    Undergraduate(std::string id, std::string n, std::string y) : Student(std::move(id), std::move(n), std::move(y), undergraduate) {}
};

class StudentWrapper {
private:
    const Student &student;
    double score = 0.0;
public:
    const std::string id;
    // TODO: fix error
    StudentWrapper(std::string id, const Student &student) : student(student), id(std::move(id)) {}

    void setScore(double s)
    {
        this->score = s;
    }

    double getScore() const
    {
        return this->score;
    }

    std::string toString() const
    {
        return student.toString();
    }
};

#endif // STUDENT_H_

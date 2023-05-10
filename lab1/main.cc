#include <vector>
#include <iostream>
#include <fstream>
#include "Class.h"
#include "Student.h"

using namespace std;

class AppX {
private:
    vector<Student *> studentVec;
    vector<Class *> classVec;

    void loadFiles();
    void inputScore();
    void printAvgScore();
    void printGpa();

public:
    AppX();
    ~AppX();
    int run();
};

AppX::~AppX()
{
    // You can use the traditional loop, which is more clear.
    for (Class* it : classVec) {
        delete it;
    }
    // You can use modern and simpler loops only if you know what it is doing.
    for (Student* s: studentVec) {
        delete (s);
    }
}

AppX::AppX()
{
    loadFiles();
}

void AppX::loadFiles()
{
    string line;
    size_t pos1, pos2;
    vector<string> bufv;
    Student *st;
    string clsname;
    int point;
    Class *cl;

    // Open a file as a input stream.
    // use ../Students.txt instead of ./Students.txt because the working directory is under cmake-build-debug
    ifstream stfile("../Students.txt");

    while (getline(stfile, line)) {
        if (line.empty()) // It's an empty line.
            continue;
        if (line[0] == '#') // It's a comment line.
            continue;

        // The bufv vector stores each columnes in the line.
        bufv.clear();
        // Split the line into columes.
        //   pos1: begining the the column.
        //   pos2: end of the column.
        pos1 = 0;
        while (true) {
            pos2 = line.find(';', pos1 + 1);
            if (pos2 == string::npos) { // No more columns.
                // Save the last column (pos1 ~ eol).
                bufv.push_back(line.substr(pos1, string::npos));
                break;
            } else {
                // Save the column (pos1 ~ pos2).
                bufv.push_back(line.substr(pos1, pos2 - pos1));
            }
            pos1 = pos2 + 1;
        }

        // TODO: uncomment next lines after implementing class Undergraduate
        // and Graduate.
        if (bufv[3] == "U")
            st = new Undergraduate(bufv[0], bufv[1], bufv[2]);
        else
            st = new Graduate(bufv[0], bufv[1], bufv[2]);

        studentVec.push_back(st);
    }
    stfile.close();

    // TODO: load data from ./Classes.txt and push objects to the vector.
    // Hint: how is student information read?
    ifstream clfile("../Classes.txt");
    while (true) {
        if (!getline(clfile, line)) {
            classVec.push_back(cl);
            break;
        }
        if (line.empty()) {
            classVec.push_back(cl);
            continue;
        }
        if (line[0] == '#')
            continue;

        pos1 = line.find(':', 1);
        if (line[0] == 'C')
            clsname = line.substr(pos1 + 1);
        else if (line[0] == 'P') {
            point = line[pos1 + 1] - '0';
            cl = new Class(clsname, point);
        }
        else
            for (Student *it : studentVec)
                if (it->id == line) {
                    cl->addStudent(*it);
                    it->addClass(cl);
                }
    }

    clfile.close();
}

void AppX::inputScore()
{
    // TODO: implement inputScore.
    // Hint: Take a look at printAvgScore().
    string sbuf;
    Class *cl;
    double score;

    while (true) {
        cout << "Please input the class name (or input q to quit): ";
        cin >> sbuf;
        if (sbuf == "q")
            break;

        cl = nullptr;
        for (Class *it : classVec) {
            if (it->name == sbuf) {
                cl = it;
                break;
            }
        }
        if (cl == nullptr) {
            cout << "No match class!" << endl;
            continue;
        }

        while (true) {
            cout << "Please input the student id (or input q to quit): ";
            cin >> sbuf;
            if (sbuf == "q")
                break;

            bool flag = false;
            for (Student* it : studentVec)
                if (it->id == sbuf) {
                    flag = true;
                }
            if (!flag) {
                cout << "No match student!" << endl;
                continue;
            }

            StudentWrapper &st = cl->getStudentWrapper(sbuf);
            cout << st.toString();
            cout << "Please input the score (or input q to quit): ";
            cin >> score;
            if (score < 0 || score > 100) {
                cout << "Wrong score!" << endl;
                continue;
            }
            st.setScore(score);
        }
    }
}

void AppX::printAvgScore()
{
    string sbuf;
    Class *cl;
    double avg;

    while (true) {
        cout << "Please input the class name (or input q to quit): ";
        cin >> sbuf;
        if (sbuf == "q")
            break;

        cl = nullptr;
        for (Class* it : classVec) {
            if (it->name == sbuf) {
                cl = it;
                break;
            }
        }
        if (cl == nullptr) {
            cout << "No match class!" << endl;
            continue;
        }

        avg = cl->getAvgScore();
        printf("The average score is: %.2f\n", avg);
    }
}

void AppX::printGpa()
{
    // TODO: implement printGpa.
    // Hint: Take a look at printAvgScore().
    string sbuf;
    Student *st;
    double gpa;

    while (true) {
        cout << "Please input the student id (or input q to quit): ";
        cin >> sbuf;
        if (sbuf == "q")
            break;

        st = nullptr;
        for (Student* it : studentVec)
            if (it->id == sbuf) {
                st = it;
                break;
            }
        if (st == nullptr) {
            cout << "No match student!" << endl;
            continue;
        }

        gpa = st->getGrade();
        cout << st->toString();
        printf("GPA = %.2f\n", gpa);
    }
}

int AppX::run()
{
    char cmd;
    while (true) {
        cout << "Command menu:\n"
            << "\ti: Input score\n"
            << "\ta: Compute average score of a class\n"
            << "\tg: Compute grade of a student\n"
            << "\tq: Quit\n"
            << "Please input the command: ";
        cin >> cmd;
        if (cmd == 'i') {
            inputScore();
        } else if (cmd == 'a') {
            printAvgScore();
        } else if (cmd == 'g') {
            printGpa();
        } else if (cmd == 'q') {
            break;
        } else {
            cout << "Invalid command!\n" << endl;
        }
    }
    return 0;
}

int main()
{
    AppX app;
    return app.run();
}

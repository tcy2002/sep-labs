#include <iostream>
#include <sstream>
#include "Editor.h"

#define INT_MIN -2147483647

using namespace std;

Editor::Editor()
{
    buffer = new Buffer();
}

Editor::~Editor()
{
    // TODO: Implement destructor
    delete buffer;
}

void Editor::run()
{
    string cmd;
    while (true)
    {
        cout << "cmd> ";
        cout.flush();
        getline(cin, cmd);
        if (cmd == "Q")
            break;
        try {
            dispatchCmd(cmd);
        } catch (const char *e) {
            cout << "? " << e << endl;
        } catch (const out_of_range &oor) {
            cout << "? " << oor.what() << endl;
        } catch (const range_error &re) {
            cout << "? " << re.what() << endl;
        }
    }
}
void Editor::cmdAppend()
{
    cout << "It's input mode now. Quit with a line with a single dot(.)" << endl;
    // TODO: finish cmdAppend.
    while (true)
    {
        string text;
        getline(cin, text);
        if (text == ".")
            break;
        buffer->appendLine(text);
    }
}

void Editor::cmdInsert()
{
    cout << "It's input mode now. Quit with a line with a single dot(.)" << endl;
    bool firstLine = true;
    while (true)
    {
        string text;
        getline(cin, text);
        if (text == ".")
            break;
        if (firstLine) {
            buffer->insertLine(text);
            firstLine = false;
        }  else {
            buffer->appendLine(text);
        }
    }
}

void Editor::cmdDelete(int start, int end)
{
    buffer->deleteLines(start, end);
}

void Editor::cmdNull(int line)
{
    cout << buffer->moveToLine(line) << endl;
}

void Editor::cmdNumber(int start, int end)
{
    buffer->showLines(start, end);
}

void Editor::cmdWrite(const string &filename)
{
    buffer->writeToFile(filename);
}

void Editor::dispatchCmd(const string &cmd)
{
    if (cmd == "a") {
        cmdAppend();
        return;
    }
    if (cmd == "i") {
        cmdInsert();
        return;
    }
    if (cmd[0] == 'w' && cmd[1] == ' ') {
        // TODO: call cmdWrite with proper arguments
        string str;
        char tmp;
        stringstream ss(cmd);
        ss >> tmp >> str;
        if (str.empty()) throw "Filename not specified";
        cmdWrite(str);
        return;
    }
    // TODO: handle special case "1,$n".
    int start = INT_MIN, end;
    char comma, type = ' ', flag;
    stringstream ss(cmd);
    stringstream ss1;
    ss >> start;
    if (start == INT_MIN) return;
    if (ss.eof()) {
        if (start < 1 || start > buffer->getLength()) throw "Line number out of range";
        cmdNull(start);
        return;
    }
    ss >> comma >> flag;
    if (flag == '$') {
        end = buffer->getLength();
        ss >> type;
        if (type == 'd') throw "Bad/Unknown command";
    } else {
        ss1.str("");
        if (!(flag >= '0' && flag <= '9')) throw "Bad/Unknown command";
        ss1 << flag;
        while (ss >> type)
            if (type != 'n' && type != 'd') {
                ss1 << type;
                if (!(type >= '0' && type <= '9')) throw "Bad/Unknown command";
            }
            else break;
        ss1 >> end;
    }
    flag = '\0';
    ss >> flag;
    if (flag == '\0') {
        if (type == 'n') {
            if (end < start) throw "Number range error";
            if (start < 1 || end > buffer->getLength()) throw "Line number out of range";
            cmdNumber(start, end);
            return;
        } else if (type == 'd') {
            if (end < start) throw "Delete range error";
            if (start < 1 || end > buffer->getLength()) throw "Line number out of range";
            cmdDelete(start, end);
            return;
        }
    }
    throw "Bad/Unknown command";
}

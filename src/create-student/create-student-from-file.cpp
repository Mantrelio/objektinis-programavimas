#include "student-vector.h"
#include "parse-student-line.h"

#include <fstream>
#include <sstream>
#include <utility>

using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::move;
using std::string;
using std::vector;

bool parseStudentLine(const string& line, Student& out, string& error) {
    istringstream iss(line);
    string name, surname;

    if (!(iss >> name >> surname)) {
        error = "missing name/surname";
        return false;
    }

    vector<int> grades;
    string token;
    
    while (iss >> token) {
        istringstream ts(token);
        int grade;

        if (!(ts >> grade) || !ts.eof()) {
            error = "non-integer grade token: " + token;
            return false;
        }

        if (grade < 1 || grade > 10) {
            error = "grade out of [1;10] range";
            return false;
        }

        grades.push_back(grade);
    }

    if (grades.size() < 2) {
        error = "need at least 1 homework + 1 exam grade";
        return false;
    }

    out.name = name;
    out.surname = surname;
    out.examGrade = grades.back();
    grades.pop_back();
    out.homeworkGrades = move(grades);
    return true;
}

vector<Student> createStudentsFromFile(const string& filename) {
    vector<Student> studentsFromFile;
    ifstream in(filename);

    if (!in) {
        cout << "Failed to open file: " << filename << endl;
        return studentsFromFile;
    }

    string headerLine;
    getline(in, headerLine);

    string line;
    int lineNumber = 1;

    while(getline(in, line)) {
        ++lineNumber;

        if (line.empty()) {
            continue;
        }

        Student student;
        string error;

        if (parseStudentLine(line, student, error)) {
            studentsFromFile.push_back(move(student));
        } else {
            cout << "Skipping line " << lineNumber << ": " << error << endl;
        }
    }

    return studentsFromFile;
}

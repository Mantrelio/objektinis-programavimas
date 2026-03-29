#include "student-create.h"

#include "input-utils.h"
#include "student-grading.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>

namespace {

std::string trim_copy(const std::string& s) {
    const auto start = s.find_first_not_of(" \t\r\f\v");
    if (start == std::string::npos) {
        return "";
    }
    const auto end = s.find_last_not_of(" \t\r\f\v");
    return s.substr(start, end - start + 1);
}

bool is_single_word(const std::string& s) {
    const std::string t = trim_copy(s);
    return !t.empty() && t.find_first_of(" \t\r\f\v") == std::string::npos;
}

void promptNameAndSurname(Student& student) {
    while (true) {
        student.name = read_required_line(cin, cout, "Enter student name: ");
        if (is_single_word(student.name)) {
            student.name = trim_copy(student.name);
            break;
        }
        cout << "Name must be a single word (no spaces).\n";
    }
    while (true) {
        student.surname = read_required_line(cin, cout, "Enter student surname: ");
        if (is_single_word(student.surname)) {
            student.surname = trim_copy(student.surname);
            break;
        }
        cout << "Surname must be a single word (no spaces).\n";
    }
}

void readHomeworkGradesInteractive(Student& student) {
    char continueHomework = 'y';
    int homeworkNumber = 1;

    while (continueHomework == 'y' || continueHomework == 'Y') {
        const int grade = read_int_in_range(cin, cout,
            "Enter homework grade " + std::to_string(homeworkNumber) + ": ", 1, 10);
        student.homeworkGrades.push_back(grade);
        homeworkNumber++;

        cout << "Add another homework grade? (y/n): ";
        cin >> continueHomework;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

int randomHomeworkCount() {
    return randomGrade(3, 10);
}

void fillRandomHomeworkGrades(Student& student, int count) {
    student.homeworkGrades.clear();
    student.homeworkGrades.reserve(static_cast<std::size_t>(count));
    for (int i = 0; i < count; i++) {
        student.homeworkGrades.push_back(randomGrade());
    }
}

void printHomeworkGradesList(const Student& student) {
    const int n = static_cast<int>(student.homeworkGrades.size());
    for (int i = 0; i < n; i++) {
        cout << student.homeworkGrades[static_cast<std::size_t>(i)];
        if (i < n - 1) {
            cout << ", ";
        }
    }
}

bool parseStudentFromLine(const string& line, Student& student) {
    if (line.empty()) {
        return false;
    }

    std::istringstream iss(line);
    student.homeworkGrades.clear();

    if (!(iss >> student.name >> student.surname)) {
        return false;
    }

    vector<int> allGrades;
    int grade = 0;
    while (iss >> grade) {
        allGrades.push_back(grade);
    }

    if (allGrades.empty()) {
        return false;
    }

    student.examGrade = allGrades.back();
    allGrades.pop_back();
    student.homeworkGrades = std::move(allGrades);
    return true;
}

}  // namespace

string randomName() {
    const string names[] = {"Jonas", "Petras", "Antanas", "Marija", "Ona", "Jurate", "Tomas", "Mindaugas", "Ruta", "Greta"};
    return names[rand() % 10];
}

string randomSurname() {
    const string surnames[] = {"Jonaitis", "Petraitis", "Antanaitis", "Kazlauskas", "Zukauskas", "Jankauskas", "Paulauskas", "Stankevicius", "Vasiliauskas", "Baranauskas"};
    return surnames[rand() % 10];
}

Student createStudentManual() {
    Student student;

    promptNameAndSurname(student);

    student.examGrade = read_int_in_range(cin, cout, "Enter exam grade: ", 1, 10);

    readHomeworkGradesInteractive(student);
    return student;
}

Student createStudentRandomGrades() {
    Student student;

    promptNameAndSurname(student);

    student.examGrade = randomGrade();
    cout << "Generated exam grade: " << student.examGrade << endl;

    const int homeworkCount = randomHomeworkCount();
    fillRandomHomeworkGrades(student, homeworkCount);

    cout << "Generated " << homeworkCount << " homework grades: ";
    printHomeworkGradesList(student);
    cout << endl;

    return student;
}

Student createStudentFullyRandom() {
    Student student;

    student.name = randomName();
    student.surname = randomSurname();
    student.examGrade = randomGrade();

    const int homeworkCount = randomHomeworkCount();
    fillRandomHomeworkGrades(student, homeworkCount);

    cout << "Generated student: " << student.name << " " << student.surname << endl;

    return student;
}

vector<Student> createStudentsFromFile(const string& filename) {
    std::ifstream in(filename);

    if (!in) {
        throw std::runtime_error("could not open file for reading (missing path or no permission)");
    }

    vector<Student> studentsFromFile;
    string headerLine;
    std::getline(in, headerLine);

    string line;
    while (std::getline(in, line)) {
        Student student;
        if (parseStudentFromLine(line, student)) {
            studentsFromFile.push_back(std::move(student));
        }
    }

    return studentsFromFile;
}


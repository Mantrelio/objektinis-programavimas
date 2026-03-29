#include "student-create.h"

#include "student-grading.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

namespace {

void promptNameAndSurname(Student& student) {
    cout << "Enter student name: ";
    cin >> student.name;

    cout << "Enter student surname: ";
    cin >> student.surname;
}

void readHomeworkGradesInteractive(Student& student) {
    char continueHomework = 'y';
    int homeworkNumber = 1;

    while (continueHomework == 'y' || continueHomework == 'Y') {
        cout << "Enter homework grade " << homeworkNumber << ": ";
        int grade = 0;
        cin >> grade;
        student.homeworkGrades.push_back(grade);
        homeworkNumber++;

        cout << "Add another homework grade? (y/n): ";
        cin >> continueHomework;
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

    cout << "Enter exam grade: ";
    cin >> student.examGrade;

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
    vector<Student> studentsFromFile;
    std::ifstream in(filename);

    if (!in) {
        cout << "Failed to open file: " << filename << endl;
        return studentsFromFile;
    }

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

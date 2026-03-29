#include "student-create.h"

#include "student-grading.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

string randomName() {
    const string names[] = {"Jonas", "Petras", "Antanas", "Marija", "Ona", "Jurate", "Tomas", "Mindaugas", "Ruta", "Greta"};
    return names[rand() % 10];
}

string randomSurname() {
    const string surnames[] = {"Jonaitis", "Petraitis", "Antanaitis", "Kazlauskas", "Zukauskas", "Jankauskas", "Paulauskas", "Stankevicius", "Vasiliauskas", "Baranauskas"};
    return surnames[rand() % 10];
}

Student createStudentManual() {
    Student student = Student();

    cout << "Enter student name: ";
    cin >> student.name;

    cout << "Enter student surname: ";
    cin >> student.surname;

    cout << "Enter exam grade: ";
    cin >> student.examGrade;

    char continueHomework = 'y';
    int homeworkNumber = 1;

    while (continueHomework == 'y' || continueHomework == 'Y') {
        cout << "Enter homework grade " << homeworkNumber << ": ";
        int grade;
        cin >> grade;
        student.homeworkGrades.push_back(grade);
        homeworkNumber++;

        cout << "Add another homework grade? (y/n): ";
        cin >> continueHomework;
    }

    return student;
}

Student createStudentRandomGrades() {
    Student student = Student();

    cout << "Enter student name: ";
    cin >> student.name;

    cout << "Enter student surname: ";
    cin >> student.surname;

    student.examGrade = randomGrade();
    cout << "Generated exam grade: " << student.examGrade << endl;

    int homeworkCount = randomGrade(3, 10);

    cout << "Generated " << homeworkCount << " homework grades: ";
    for (int i = 0; i < homeworkCount; i++) {
        int grade = randomGrade();
        student.homeworkGrades.push_back(grade);
        cout << grade;
        if (i < homeworkCount - 1) cout << ", ";
    }
    cout << endl;

    return student;
}

Student createStudentFullyRandom() {
    Student student = Student();

    student.name = randomName();
    student.surname = randomSurname();
    student.examGrade = randomGrade();

    int homeworkCount = randomGrade(3, 10);

    for (int i = 0; i < homeworkCount; i++) {
        student.homeworkGrades.push_back(randomGrade());
    }

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
        if (line.empty()) continue;

        std::istringstream iss(line);
        Student student;
        student.homeworkGrades.clear();

        if (!(iss >> student.name >> student.surname)) {
            continue;
        }

        int grade;
        vector<int> allGrades;
        while (iss >> grade) {
            allGrades.push_back(grade);
        }

        if (allGrades.empty()) {
            continue;
        }

        student.examGrade = allGrades.back();
        allGrades.pop_back();
        student.homeworkGrades = allGrades;

        studentsFromFile.push_back(student);
    }

    return studentsFromFile;
}

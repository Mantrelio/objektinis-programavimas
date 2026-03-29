#include "student-app.h"

#include "student-create.h"
#include "student-grading.h"

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>

void printResults(const vector<Student>& students, std::ostream& out) {
    out << "\n" << string(70, '=') << endl;
    out << left << setw(20) << "Name"
        << left << setw(20) << "Surname"
        << right << setw(15) << "Final (Avg.)"
        << right << setw(15) << "Final (Med.)" << endl;
    out << string(70, '-') << endl;

    for (const Student& s : students) {
        double finalAvg = calculateFinalGradeAverage(s.homeworkGrades, s.examGrade);
        double finalMed = calculateFinalGradeMedian(s.homeworkGrades, s.examGrade);

        out << left << setw(20) << s.name
            << left << setw(20) << s.surname
            << right << std::fixed << std::setprecision(2) << setw(15) << finalAvg
            << right << std::fixed << std::setprecision(2) << setw(15) << finalMed << endl;
    }
    out << string(70, '=') << endl;
}

void showMainMenu() {
    cout << "\n=== MENU ===" << endl;
    cout << "1 - Manual input (enter all values)" << endl;
    cout << "2 - Enter name/surname, generate grades" << endl;
    cout << "3 - Generate all data randomly" << endl;
    cout << "4 - Read students from file" << endl;
    cout << "5 - Exit and show results" << endl;
    cout << "Choose option: ";
}

void handleMenuChoice(int choice, vector<Student>& students) {
    switch (choice) {
        case 1:
            cout << "\n--- Student " << (students.size() + 1) << " ---" << endl;
            students.push_back(createStudentManual());
            break;
        case 2:
            cout << "\n--- Student " << (students.size() + 1) << " ---" << endl;
            students.push_back(createStudentRandomGrades());
            break;
        case 3:
            cout << "\n--- Student " << (students.size() + 1) << " ---" << endl;
            students.push_back(createStudentFullyRandom());
            break;
        case 4: {
            string filename;
            cout << "Enter file name (e.g. data.txt): ";
            cin >> filename;
            vector<Student> fileStudents = createStudentsFromFile(filename);
            cout << "Loaded " << fileStudents.size() << " students from file." << endl;
            students.insert(students.end(), fileStudents.begin(), fileStudents.end());
            break;
        }
    }
}

void collectStudents(vector<Student>& students) {
    int choice = 0;

    while (choice != 5) {
        showMainMenu();
        cin >> choice;

        if (choice == 5) break;

        if (choice < 1 || choice > 5) {
            cout << "Invalid option. Please try again." << endl;
            continue;
        }

        handleMenuChoice(choice, students);
    }
}

vector<Student> chooseSorting(const vector<Student>& students) {
    int sortChoice = 0;
    cout << "\nChoose sorting option:" << endl;
    cout << "0 - Unsorted (original order)" << endl;
    cout << "1 - By name" << endl;
    cout << "2 - By surname" << endl;
    cout << "3 - By final average" << endl;
    cout << "4 - By final median" << endl;
    cout << "Choice: ";
    cin >> sortChoice;

    vector<Student> resultStudents = students;

    if (sortChoice == 0) {
        cout << "Showing unsorted results (original order)." << endl;
    } else if (sortChoice >= 1 && sortChoice <= 4) {
        std::sort(resultStudents.begin(), resultStudents.end(),
            [sortChoice](const Student& a, const Student& b) {
                switch (sortChoice) {
                    case 1:
                        if (a.name == b.name) return a.surname < b.surname;
                        return a.name < b.name;
                    case 2:
                        if (a.surname == b.surname) return a.name < b.name;
                        return a.surname < b.surname;
                    case 3: {
                        double fa = calculateFinalGradeAverage(a.homeworkGrades, a.examGrade);
                        double fb = calculateFinalGradeAverage(b.homeworkGrades, b.examGrade);
                        return fa < fb;
                    }
                    case 4: {
                        double fa = calculateFinalGradeMedian(a.homeworkGrades, a.examGrade);
                        double fb = calculateFinalGradeMedian(b.homeworkGrades, b.examGrade);
                        return fa < fb;
                    }
                    default:
                        return a.name < b.name;
                }
            }
        );
    } else {
        cout << "Invalid sorting option. Showing unsorted results (original order)." << endl;
    }

    return resultStudents;
}

void outputResults(const vector<Student>& students) {
    const vector<Student>& resultStudents = students;

    int outputChoice = 0;
    cout << "\nChoose output method:" << endl;
    cout << "1 - Show results in console" << endl;
    cout << "2 - Save results to text file" << endl;
    cout << "Choice: ";
    cin >> outputChoice;

    if (outputChoice == 2) {
        string outFilename;
        cout << "Enter output filename (e.g. results.txt): ";
        cin >> outFilename;

        std::ofstream outFile(outFilename);
        if (!outFile) {
            cout << "Failed to open output file. Showing results in console instead." << endl;
            printResults(resultStudents, cout);
        } else {
            printResults(resultStudents, outFile);
            cout << "Results saved to " << outFilename << endl;
        }
    } else {
        printResults(resultStudents, cout);
    }
}

void chooseOutputAndPrint(const vector<Student>& students) {
    if (students.empty()) {
        cout << "No students to display." << endl;
        return;
    }

    vector<Student> resultStudents = chooseSorting(students);
    outputResults(resultStudents);
}

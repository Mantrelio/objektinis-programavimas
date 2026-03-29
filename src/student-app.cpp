#include "student-app.h"

#include "input-utils.h"
#include "student-create.h"
#include "student-grading.h"

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>

namespace {

void printTableHeader(std::ostream& out) {
    out << "\n" << string(70, '=') << endl;
    out << left << setw(20) << "Name"
        << left << setw(20) << "Surname"
        << right << setw(15) << "Final (Avg.)"
        << right << setw(15) << "Final (Med.)" << endl;
    out << string(70, '-') << endl;
}

void printTableFooter(std::ostream& out) {
    out << string(70, '=') << endl;
}

void printStudentRow(std::ostream& out, const Student& s) {
    const double finalAvg = calculateFinalGradeAverage(s.homeworkGrades, s.examGrade);
    const double finalMed = calculateFinalGradeMedian(s.homeworkGrades, s.examGrade);

    out << left << setw(20) << s.name
        << left << setw(20) << s.surname
        << right << std::fixed << std::setprecision(2) << setw(15) << finalAvg
        << right << std::fixed << std::setprecision(2) << setw(15) << finalMed << endl;
}

bool compareStudentsForSort(int sortChoice, const Student& a, const Student& b) {
    switch (sortChoice) {
        case 1:
            if (a.name == b.name) {
                return a.surname < b.surname;
            }
            return a.name < b.name;
        case 2:
            if (a.surname == b.surname) {
                return a.name < b.name;
            }
            return a.surname < b.surname;
        case 3: {
            const double fa = calculateFinalGradeAverage(a.homeworkGrades, a.examGrade);
            const double fb = calculateFinalGradeAverage(b.homeworkGrades, b.examGrade);
            return fa < fb;
        }
        case 4: {
            const double fa = calculateFinalGradeMedian(a.homeworkGrades, a.examGrade);
            const double fb = calculateFinalGradeMedian(b.homeworkGrades, b.examGrade);
            return fa < fb;
        }
        default:
            return a.name < b.name;
    }
}

void announceNextStudent(std::size_t studentIndex) {
    cout << "\n--- Student " << studentIndex << " ---" << endl;
}

}  // namespace

void printResults(const vector<Student>& students, std::ostream& out) {
    printTableHeader(out);
    for (const Student& s : students) {
        printStudentRow(out, s);
    }
    printTableFooter(out);
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
    const std::size_t nextIndex = students.size() + 1;

    switch (choice) {
        case 1:
            announceNextStudent(nextIndex);
            students.push_back(createStudentManual());
            break;
        case 2:
            announceNextStudent(nextIndex);
            students.push_back(createStudentRandomGrades());
            break;
        case 3:
            announceNextStudent(nextIndex);
            students.push_back(createStudentFullyRandom());
            break;
        case 4: {
            string filename;
            cout << "Enter file name (e.g. data.txt): ";
            cin >> filename;
            try {
                const vector<Student> fileStudents = createStudentsFromFile(filename);
                if (fileStudents.empty()) {
                    cout << "File opened, but no valid student rows were found (empty file or bad lines)."
                         << endl;
                } else {
                    cout << "Loaded " << fileStudents.size() << " students from file." << endl;
                }
                students.insert(students.end(), fileStudents.begin(), fileStudents.end());
            } catch (const std::exception& e) {
                cout << "Error reading \"" << filename << "\": " << e.what() << endl;
            }
            break;
        }
    }
}

void collectStudents(vector<Student>& students) {
    int choice = 0;

    while (choice != 5) {
        showMainMenu();
        choice = read_int_in_range(cin, cout, "", 1, 5);

        if (choice == 5) {
            break;
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
    sortChoice = read_int_in_range(cin, cout, "", 0, 4);

    vector<Student> resultStudents = students;

    if (sortChoice == 0) {
        cout << "Showing unsorted results (original order)." << endl;
    } else {
        std::sort(resultStudents.begin(), resultStudents.end(),
            [sortChoice](const Student& a, const Student& b) {
                return compareStudentsForSort(sortChoice, a, b);
            });
    }

    return resultStudents;
}

void outputResults(const vector<Student>& students) {
    int outputChoice = 0;
    cout << "\nChoose output method:" << endl;
    cout << "1 - Show results in console" << endl;
    cout << "2 - Save results to text file" << endl;
    cout << "Choice: ";
    outputChoice = read_int_in_range(cin, cout, "", 1, 2);

    if (outputChoice == 2) {
        string outFilename;
        cout << "Enter output filename (e.g. results.txt): ";
        cin >> outFilename;

        try {
            std::ofstream outFile(outFilename);
            if (!outFile) {
                throw std::runtime_error("could not open file for writing (path or permission)");
            }
            printResults(students, outFile);
            outFile.flush();
            if (!outFile) {
                throw std::runtime_error("write failed (disk full or I/O error)");
            }
            cout << "Results saved to " << outFilename << endl;
        } catch (const std::exception& e) {
            cout << "Error writing \"" << outFilename << "\": " << e.what() << endl;
            cout << "Showing results in console instead." << endl;
            printResults(students, cout);
        }
    } else {
        printResults(students, cout);
    }
}

void chooseOutputAndPrint(const vector<Student>& students) {
    if (students.empty()) {
        cout << "No students to display." << endl;
        return;
    }

    const vector<Student> resultStudents = chooseSorting(students);
    outputResults(resultStudents);
}

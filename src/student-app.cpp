#include "student-app.h"

#include "input-utils.h"
#include "student-create.h"
#include "student-grading.h"

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>

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

constexpr int k_max_bulk_random_students = 10'000'000;

void write_random_students_table_to_file(int count, const string& filename) {
    try {
        std::ofstream outFile(filename);
        if (!outFile) {
            throw std::runtime_error(
                "nepavyko atidaryti failo rašymui (kelias arba teisės)");
        }
        printTableHeader(outFile);
        for (int i = 0; i < count; ++i) {
            const Student s = create_student_fully_random_silent();
            printStudentRow(outFile, s);
        }
        printTableFooter(outFile);
        outFile.flush();
        if (!outFile) {
            throw std::runtime_error(
                "rašymas nepavyko (diskas pilnas arba įvesties/išvesties klaida)");
        }
        cout << "Wrote " << count << " students to " << filename << endl;
    } catch (const std::exception& e) {
        cout << "Klaida rašant į „" << filename << "“: " << e.what() << endl;
    }
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
    cout << "5 - Generate random student list to file (count only)" << endl;
    cout << "6 - Exit and show results" << endl;
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
            const string filename =
                read_required_line(cin, cout, "Enter file name (e.g. data.txt): ");
            try {
                const vector<Student> fileStudents = createStudentsFromFile(filename);
                if (fileStudents.empty()) {
                    cout << "Failas atidarytas, bet tinkamų studentų eilučių nerasta "
                            "(tuščias failas arba netinkamos eilutės)."
                         << endl;
                } else {
                    cout << "Loaded " << fileStudents.size() << " students from file." << endl;
                }
                students.insert(students.end(), fileStudents.begin(), fileStudents.end());
            } catch (const std::exception& e) {
                cout << "Klaida skaitant „" << filename << "“: " << e.what() << endl;
            }
            break;
        }
        case 5: {
            const int count = read_int_in_range(cin, cout,
                "How many students to generate (1-" + std::to_string(k_max_bulk_random_students)
                    + "): ",
                1, k_max_bulk_random_students);
            const string outFilename =
                read_required_line(cin, cout, "Enter output filename (e.g. results.txt): ");
            write_random_students_table_to_file(count, outFilename);
            break;
        }
    }
}

void collectStudents(vector<Student>& students) {
    int choice = 0;

    while (choice != 6) {
        showMainMenu();
        choice = read_int_in_range(cin, cout, "", 1, 6);

        if (choice == 6) {
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
        const string outFilename =
            read_required_line(cin, cout, "Enter output filename (e.g. results.txt): ");

        try {
            std::ofstream outFile(outFilename);
            if (!outFile) {
                throw std::runtime_error(
                    "nepavyko atidaryti failo rašymui (kelias arba teisės)");
            }
            printResults(students, outFile);
            outFile.flush();
            if (!outFile) {
                throw std::runtime_error("rašymas nepavyko (diskas pilnas arba įvesties/išvesties klaida)");
            }
            cout << "Results saved to " << outFilename << endl;
        } catch (const std::exception& e) {
            cout << "Klaida rašant į „" << outFilename << "“: " << e.what() << endl;
            cout << "Rezultatai rodomi konsolėje." << endl;
            printResults(students, cout);
        }
    } else {
        printResults(students, cout);
    }
}

void chooseOutputAndPrint(const vector<Student>& students) {
    if (students.empty()) {
        cout << "Nėra studentų, kuriuos būtų galima rodyti." << endl;
        return;
    }

    const vector<Student> resultStudents = chooseSorting(students);
    outputResults(resultStudents);
}

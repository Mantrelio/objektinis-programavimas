#include "student-app.h"

#include "input-utils.h"
#include "student-create.h"
#include "student-grading.h"

#include <algorithm>
#include <chrono>
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

vector<Student> applySorting(const vector<Student>& students, int sortChoice) {
    vector<Student> resultStudents = students;
    if (sortChoice != 0) {
        std::sort(resultStudents.begin(), resultStudents.end(),
            [sortChoice](const Student& a, const Student& b) {
                return compareStudentsForSort(sortChoice, a, b);
            });
    }
    return resultStudents;
}

void print_sort_menu(const char* title) {
    cout << "\n" << title << endl;
    cout << "0 - Unsorted (original order)" << endl;
    cout << "1 - By name" << endl;
    cout << "2 - By surname" << endl;
    cout << "3 - By final average" << endl;
    cout << "4 - By final median" << endl;
    cout << "Choice: ";
}

void announceNextStudent(std::size_t studentIndex) {
    cout << "\n--- Student " << studentIndex << " ---" << endl;
}

constexpr int k_max_bulk_random_students = 10'000'000;

void print_kursiokai_header(std::ostream& out) {
    out << left << setw(25) << "Vardas"
        << left << setw(25) << "Pavarde";
    for (int i = 1; i <= 15; ++i) {
        out << right << setw(10) << ("ND" + std::to_string(i));
    }
    out << right << setw(10) << "Egz." << endl;
}

void print_kursiokai_student_row(std::ostream& out, const Student& s) {
    out << left << setw(25) << s.name
        << left << setw(25) << s.surname;
    for (int g : s.homeworkGrades) {
        out << right << setw(10) << g;
    }
    out << right << setw(10) << s.examGrade << endl;
}

void write_random_students_table_to_file(int count, const string& filename) {
    try {
        std::ofstream outFile(filename);
        if (!outFile) {
            throw std::runtime_error(
                "nepavyko atidaryti failo rašymui (kelias arba teisės)");
        }
        print_kursiokai_header(outFile);
        const auto t0 = std::chrono::steady_clock::now();
        for (int i = 0; i < count; ++i) {
            Student s = create_student_fully_random_silent();
            s.homeworkGrades.clear();
            s.homeworkGrades.reserve(15);
            for (int j = 0; j < 15; ++j) {
                s.homeworkGrades.push_back(randomGrade());
            }
            print_kursiokai_student_row(outFile, s);
        }
        outFile.flush();
        if (!outFile) {
            throw std::runtime_error(
                "rašymas nepavyko (diskas pilnas arba įvesties/išvesties klaida)");
        }
        const auto t1 = std::chrono::steady_clock::now();
        const double elapsedSec =
            std::chrono::duration<double>(t1 - t0).count();
        cout << "Wrote " << count << " students to " << filename << endl;
        cout << "Time elapsed: " << std::fixed << std::setprecision(3) << elapsedSec
             << " s" << endl;
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

namespace {

constexpr double k_grade_split_boundary = 5.0;

}  // namespace

void split_protingi_kvaili() {
    const string filename =
        read_required_line(cin, cout, "Enter data file name (e.g. data.txt): ");

    vector<Student> fileStudents;
    double readElapsedSec = 0.0;
    try {
        const auto tRead0 = std::chrono::steady_clock::now();
        fileStudents = createStudentsFromFile(filename);
        const auto tRead1 = std::chrono::steady_clock::now();
        readElapsedSec = std::chrono::duration<double>(tRead1 - tRead0).count();
    } catch (const std::exception& e) {
        cout << "Klaida skaitant „" << filename << "“: " << e.what() << endl;
        return;
    }

    cout << "Time elapsed (read file): " << std::fixed << std::setprecision(3)
         << readElapsedSec << " s" << endl;

    if (fileStudents.empty()) {
        cout << "Failas atidarytas, bet tinkamų studentų eilučių nerasta "
                "(tuščias failas arba netinkamos eilutės)."
             << endl;
        return;
    }

    cout << "Loaded " << fileStudents.size() << " students from file." << endl;

    vector<Student> protingi;
    vector<Student> kvaili;
    protingi.reserve(fileStudents.size());
    kvaili.reserve(fileStudents.size());

    const auto tSplit0 = std::chrono::steady_clock::now();
    for (const Student& s : fileStudents) {
        const double finalAvg = calculateFinalGradeAverage(s.homeworkGrades, s.examGrade);
        if (finalAvg < k_grade_split_boundary) {
            kvaili.push_back(s);
        } else {
            protingi.push_back(s);
        }
    }
    const auto tSplit1 = std::chrono::steady_clock::now();
    const double splitIntoGroupsSec =
        std::chrono::duration<double>(tSplit1 - tSplit0).count();
    cout << "Time elapsed (split into Protingi / Kvaili): " << std::fixed
         << std::setprecision(3) << splitIntoGroupsSec << " s" << endl;

    print_sort_menu("Choose sorting for Protingi file:");
    const int protingiSort = read_int_in_range(cin, cout, "", 0, 4);
    if (protingiSort == 0) {
        cout << "Protingi: original order within group." << endl;
    }
    const vector<Student> protingiOut = applySorting(protingi, protingiSort);

    print_sort_menu("Choose sorting for Kvaili file:");
    const int kvailiSort = read_int_in_range(cin, cout, "", 0, 4);
    if (kvailiSort == 0) {
        cout << "Kvaili: original order within group." << endl;
    }
    const vector<Student> kvailiOut = applySorting(kvaili, kvailiSort);

    const string protingiFilename =
        read_required_line(cin, cout, "Enter Protingi output filename (e.g. Protingi.txt): ");
    const string kvailiFilename =
        read_required_line(cin, cout, "Enter Kvaili output filename (e.g. Kvaili.txt): ");

    try {
        std::ofstream protingiFile(protingiFilename);
        std::ofstream kvailiFile(kvailiFilename);
        if (!protingiFile || !kvailiFile) {
            throw std::runtime_error(
                "nepavyko atidaryti failo rašymui (kelias arba teisės)");
        }
        printResults(protingiOut, protingiFile);
        printResults(kvailiOut, kvailiFile);
        protingiFile.flush();
        kvailiFile.flush();
        if (!protingiFile || !kvailiFile) {
            throw std::runtime_error(
                "rašymas nepavyko (diskas pilnas arba įvesties/išvesties klaida)");
        }
        cout << "Protingi saved to " << protingiFilename << endl;
        cout << "Kvaili saved to " << kvailiFilename << endl;
    } catch (const std::exception& e) {
        cout << "Klaida rašant: " << e.what() << endl;
    }
}

void showMainMenu() {
    cout << "\n=== MENU ===" << endl;
    cout << "1 - Manual input (enter all values)" << endl;
    cout << "2 - Enter name/surname, generate grades" << endl;
    cout << "3 - Generate all data randomly" << endl;
    cout << "4 - Read students from file" << endl;
    cout << "5 - Generate random student list to file (count only)" << endl;
    cout << "6 - Split into Protingi / Kvaili files (results format)" << endl;
    cout << "7 - Exit and show results" << endl;
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
                read_required_line(cin, cout, "Enter output filename (e.g. kursiokai.txt): ");
            write_random_students_table_to_file(count, outFilename);
            break;
        }
        case 6:
            split_protingi_kvaili();
            break;
    }
}

void collectStudents(vector<Student>& students) {
    int choice = 0;

    while (choice != 7) {
        showMainMenu();
        choice = read_int_in_range(cin, cout, "", 1, 7);

        if (choice == 7) {
            break;
        }

        handleMenuChoice(choice, students);
    }
}

vector<Student> chooseSorting(const vector<Student>& students) {
    print_sort_menu("Choose sorting option:");
    const int sortChoice = read_int_in_range(cin, cout, "", 0, 4);

    if (sortChoice == 0) {
        cout << "Showing unsorted results (original order)." << endl;
    }

    return applySorting(students, sortChoice);
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

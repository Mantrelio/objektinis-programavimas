#include "output-results.h"

#include "input-utils.h"
#include "sort-students.h"
#include "student-grading.h"

#include <deque>
#include <fstream>
#include <iomanip>
#include <list>
#include <stdexcept>

using std::endl;
using std::fixed;
using std::left;
using std::ofstream;
using std::right;
using std::runtime_error;
using std::setprecision;
using std::setw;

template <typename T>
void outputResults(const T& students, std::ostream& out) {
    if (students.empty()) {
        cout << "NeraĮ rodytį studentų." << endl;
        return;
    }

    out << "\n" << string(70, '=') << endl;
    out << left << setw(20) << "Vardas"
        << left << setw(20) << "Pavardė"
        << right << setw(15) << "Gal. (Vid.)"
        << right << setw(15) << "Gal. (Med.)" << endl;
    out << string(70, '-') << endl;

    for (const Student& student : students) {
        const double finalAvg = calculateFinalGradeAverage(student.homeworkGrades, student.examGrade);
        const double finalMed = calculateFinalGradeMedian(student.homeworkGrades, student.examGrade);

        out << left << setw(20) << student.name
            << left << setw(20) << student.surname
            << right << fixed << setprecision(2) << setw(15) << finalAvg
            << right << fixed << setprecision(2) << setw(15) << finalMed << endl;
    }
    out << string(70, '=') << endl;
}

template <typename T>
void handleResultOutput(const T& students, int outputChoice, const string& outFilename) {
    if (outputChoice == 2 || outputChoice == 3) {
        try {
            ofstream outFile(outFilename);
            if (!outFile) {
                throw runtime_error("failed to open output file for writing");
            }

            outputResults(students, outFile);
            outFile.flush();
            if (!outFile) {
                throw runtime_error("failed while writing results to file");
            }

            cout << "Rezultatai išsaugoti: " << outFilename << endl;

            if (outputChoice == 3) {
                outputResults(students, cout);
            }
        } catch (const std::exception& e) {
            cout << "Nepavyko išsaugoti rezultatų į \"" << outFilename << "\": " << e.what() << endl;
            cout << "Rezultatai rodomi konsoleje." << endl;
            outputResults(students, cout);
        }
        return;
    } else {
        outputResults(students, cout);
    }
}

void runHandleResultOutputPrompt(const vector<Student>& students) {
    cout << "\nPasirinkite išvedimo būdą:" << endl;
    cout << "1 - Rodyti rezultatus konsoleje" << endl;
    cout << "2 - Išsaugoti rezultatus į tekstinį failą" << endl;
    cout << "3 - Rodyti rezultatus konsoleje ir išsaugoti į tekstinį failą" << endl;

    const int outputChoice = readIntInRange("Pasirinkimas: ", 1, 3);

    if (outputChoice == 2 || outputChoice == 3) {
        const string outFilename =
            readSingleStringToken("Suveskite išsaugų failo pavadinimą (pvz. results.txt): ");
        handleResultOutput(students, outputChoice, outFilename);
        return;
    }

    handleResultOutput(students, outputChoice, "");
}

void chooseOutputAndPrint(const vector<Student>& students) {
    if (students.empty()) {
        cout << "Studentu sarasas tuscias" << endl;
        return;
    }

    const vector<Student> sortedStudents = runSortStudentsChoicePrompt(students);
    runHandleResultOutputPrompt(sortedStudents);
}

template void outputResults(const vector<Student>& students, std::ostream& out);
template void outputResults(const std::list<Student>& students, std::ostream& out);
template void outputResults(const std::deque<Student>& students, std::ostream& out);

template void handleResultOutput(const vector<Student>& students, int outputChoice, const string& outFilename);
template void handleResultOutput(const std::list<Student>& students, int outputChoice, const string& outFilename);
template void handleResultOutput(const std::deque<Student>& students, int outputChoice, const string& outFilename);
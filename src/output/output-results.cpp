#include "output-results.h"

#include "input-utils.h"
#include "sort-students.h"
#include "student-grading.h"

#include <fstream>
#include <iomanip>
#include <stdexcept>

using std::endl;
using std::fixed;
using std::left;
using std::ofstream;
using std::right;
using std::runtime_error;
using std::setprecision;
using std::setw;

void outputResults(const vector<Student>& students, std::ostream& out) {
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

    for (int i = 0; i < static_cast<int>(students.size()); i++) {
        const double finalAvg = calculateFinalGradeAverage(students[i].homeworkGrades, students[i].examGrade);
        const double finalMed = calculateFinalGradeMedian(students[i].homeworkGrades, students[i].examGrade);

        out << left << setw(20) << students[i].name
            << left << setw(20) << students[i].surname
            << right << fixed << setprecision(2) << setw(15) << finalAvg
            << right << fixed << setprecision(2) << setw(15) << finalMed << endl;
    }
    out << string(70, '=') << endl;
}

void handleResultOutput(const vector<Student>& students, int outputChoice, const string& outFilename) {
    if (outputChoice == 2) {
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

void handleResultOutput(const vector<Student>& students) {
    cout << "\nPasirinkite išvedimo būdą:" << endl;
    cout << "1 - Rodyti rezultatus konsoleje" << endl;
    cout << "2 - Išsaugoti rezultatus į tekstinį failą" << endl;

    const int outputChoice = readIntInRange("Pasirinkimas: ", 1, 2);

    if (outputChoice == 2) {
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
    handleResultOutput(sortedStudents);
}
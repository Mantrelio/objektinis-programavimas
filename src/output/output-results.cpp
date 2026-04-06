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

void outputResultsInConsole(const vector<Student>& students, std::ostream& out) {
    if (students.empty()) {
        cout << "No students to display." << endl;
        return;
    }

    out << "\n" << string(70, '=') << endl;
    out << left << setw(20) << "Name"
        << left << setw(20) << "Surname"
        << right << setw(15) << "Final (Avg.)"
        << right << setw(15) << "Final (Med.)" << endl;
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

void printResults(const vector<Student>& students, std::ostream& out) {
    outputResultsInConsole(students, out);
}

void outputResults(const vector<Student>& students) {
    cout << "\nChoose output method:" << endl;
    cout << "1 - Show results in console" << endl;
    cout << "2 - Save results to text file" << endl;

    const int outputChoice = readIntInRange("Choice: ", 1, 2);

    if (outputChoice == 2) {
        const string outFilename =
            readSingleStringToken("Enter output filename (e.g. results.txt): ");

        try {
            ofstream outFile(outFilename);
            if (!outFile) {
                throw runtime_error("failed to open output file for writing");
            }

            printResults(students, outFile);
            outFile.flush();
            if (!outFile) {
                throw runtime_error("failed while writing results to file");
            }

            cout << "Results saved to " << outFilename << endl;
        } catch (const std::exception& e) {
            cout << "Failed to write results to \"" << outFilename << "\": " << e.what() << endl;
            cout << "Showing results in console instead." << endl;
            printResults(students, cout);
        }
        return;
    }

    printResults(students, cout);
}

void chooseOutputAndPrint(const vector<Student>& students) {
    if (students.empty()) {
        cout << "No students to display." << endl;
        return;
    }

    const vector<Student> sortedStudents = chooseSorting(students);
    outputResults(sortedStudents);
}
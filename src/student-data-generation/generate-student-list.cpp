#include "generate-student-list.h"
#include "input-utils.h"
#include "student-vector.h"
#include "create-student.h"
#include "student-grading.h"

#include <cctype>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdexcept>

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::istringstream;
using std::left;
using std::right;
using std::setw;
using std::toupper;
using std::ws;

void printHeader(std::ostream& output) {
    output << left << setw(25) << "Vardas"
        << left << setw(25) << "Pavarde";
    for (int i = 1; i <= 15; ++i) {
        output << right << setw(10) << ("ND" + std::to_string(i));
    }
    output << right << setw(10) << "Egz." << endl;
}

void printStudentListRow(std::ostream& output, const Student& s) {
    output << left << setw(25) << s.name
        << left << setw(25) << s.surname;
    for (int g : s.homeworkGrades) {
        output << right << setw(10) << g;
    }
    output << right << setw(10) << s.examGrade << endl;
}

void generateStudentListFile(int studentCount, const std::string& filename) {
    try {
        std::ofstream outputFile(filename);

        if (!outputFile) {
            throw std::runtime_error("nepavyko atidaryti failo rasymui");
        }

        printHeader(outputFile);

        Student student;

        for (int i = 0; i < studentCount; i++) {
            Student student = createStudentFullyRandom();
            student.homeworkGrades.clear();
            student.homeworkGrades.reserve(15);
            
            for (int j = 0; j < 15; j++) {
                student.homeworkGrades.push_back(randomGrade());
            }

            printStudentListRow(outputFile, student);
        }

        outputFile.flush();

        if (!outputFile) {
            throw std::runtime_error("Rasymas nepavyko");
        }
        
        cout << "Failas sukurtas: " << filename << endl;
    } catch (const std::exception& e) {
        cout << "Klaida rasant i " << filename << ": " << e.what() << endl;
    }
}

void handleGenerateStudentListFile() {
    int studentCount = readSingleIntToken("Sugeneruotu studentu skaicius: ");
    string fileName = readSingleStringToken("Failo pavadinimas: ");

    generateStudentListFile(studentCount, fileName);
}
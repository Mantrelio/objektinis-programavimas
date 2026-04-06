#include "output-nuskriausti-and-protingi-test.h"
#include "input-utils.h"
#include "create-student.h"
#include "output-nuskriausti-and-protingi.h"
#include "student-grading.h"
#include "sort-students.h"
#include "output-results.h"

#include <chrono>
#include <iomanip>
#include <iostream>

using std::cout;
using std::endl;

void outputNuskriaustiAndProtingiTest() {
    const string filename = readSingleStringToken("Suveskite failo pavadinimą (pvz. data.txt): ");
    const int sortChoice = 1;
    const bool ascending = true;
    const int outputChoice = 2;
    const string outFilename = readSingleStringToken("Suveskite protingu failo pavadinima: ");
    const string outFilename2 = readSingleStringToken("Suveskite nuskriaustu failo pavadinima: ");

    double totalLoadSeconds = 0.0;
    double totalSortSeconds = 0.0;
    double totalOutputSeconds = 0.0;
    double totalIterationSeconds = 0.0;

    for (int i = 0; i < 5; i++) {
        const auto loadStart = std::chrono::steady_clock::now();
        vector<Student> students = createStudentsFromFile(filename);
        const auto loadEnd = std::chrono::steady_clock::now();

        const auto sortStart = std::chrono::steady_clock::now();
        vector<Student> nuskriausti, protingi;
        for (Student student : students) {
            if (calculateFinalGradeAverage(student.homeworkGrades, student.examGrade) >= 5) {
                protingi.push_back(student);
            } else {
                nuskriausti.push_back(student);
            }
        }

        nuskriausti = sortStudents(nuskriausti, sortChoice, ascending);

        protingi = sortStudents(protingi, sortChoice, ascending);

        const auto sortEnd = std::chrono::steady_clock::now();

        const auto outputStart = std::chrono::steady_clock::now();

        handleResultOutput(nuskriausti, outputChoice, outFilename2);

        handleResultOutput(protingi, outputChoice, outFilename);

        const auto outputEnd = std::chrono::steady_clock::now();

        const double loadSeconds = std::chrono::duration<double>(loadEnd - loadStart).count();
        const double sortSeconds = std::chrono::duration<double>(sortEnd - sortStart).count();
        const double outputSeconds = std::chrono::duration<double>(outputEnd - outputStart).count();
        const double iterationSeconds = loadSeconds + sortSeconds + outputSeconds;

        totalLoadSeconds += loadSeconds;
        totalSortSeconds += sortSeconds;
        totalOutputSeconds += outputSeconds;
        totalIterationSeconds += iterationSeconds;

        cout << std::fixed << std::setprecision(6)
             << "Iteracija " << (i + 1) << ":\n"
             << "  Failo nuskaitymas: " << loadSeconds << " s\n"
             << "  Rusiavimas: " << sortSeconds << " s\n"
             << "  Rezultatu spausdinimas: " << outputSeconds << " s\n"
             << "  Is viso: " << iterationSeconds << " s" << endl;
    }

    const double averageLoadSeconds = totalLoadSeconds / 5.0;
    const double averageSortSeconds = totalSortSeconds / 5.0;
    const double averageOutputSeconds = totalOutputSeconds / 5.0;
    const double averageIterationSeconds = totalIterationSeconds / 5.0;

    cout << std::fixed << std::setprecision(6)
         << "\nVidurkiai per 5 iteracijas:\n"
         << "  Failo nuskaitymas: " << averageLoadSeconds << " s\n"
         << "  Rusiavimas: " << averageSortSeconds << " s\n"
         << "  Rezultatu spausdinimas: " << averageOutputSeconds << " s\n"
         << "  Is viso: " << averageIterationSeconds << " s" << endl;
}
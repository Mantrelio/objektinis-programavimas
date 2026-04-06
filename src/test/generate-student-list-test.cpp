#include "generate-student-list-test.h"
#include "generate-student-list.h"
#include "input-utils.h"

#include <chrono>
#include <iomanip>
#include <iostream>

using std::cout;
using std::endl;

void handleGenerateStudentListTest() {
    cout << "Pasirinkite testavimo varianta:" << endl;
    cout << "1 - 1000" << endl;
    cout << "2 - 10000" << endl;
    cout << "3 - 100000" << endl;
    cout << "4 - 1000000" << endl;
    cout << "5 - 10000000" << endl;
    int choice = readIntInRange("Pasirinkite variantą: ", 1, 5);

    int studentCount;

    switch(choice) {
        case 1:
            studentCount = 1000;
            break;
        case 2:
            studentCount = 10000;
            break;
        case 3:
            studentCount = 100000;
            break;
        case 4:
            studentCount = 1000000;
            break;
        case 5:
            studentCount = 10000000;
            break;
    }

    double totalSeconds = 0.0;

    for (int i = 0; i < 5; i++) {
        const auto start = std::chrono::steady_clock::now();
        generateStudentListFile(studentCount, "test.txt");
        const auto end = std::chrono::steady_clock::now();

        const double iterationSeconds = std::chrono::duration<double>(end - start).count();
        totalSeconds += iterationSeconds;

        cout << std::fixed << std::setprecision(6)
             << "Iteracija " << (i + 1) << " uztruko: " << iterationSeconds << " s" << endl;
    }

    const double averageSeconds = totalSeconds / 5.0;
    cout << std::fixed << std::setprecision(6)
         << "Vidutinis laikas: " << averageSeconds << " s" << endl;
}
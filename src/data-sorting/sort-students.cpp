#include "sort-students.h"

#include "input-utils.h"
#include "student-grading.h"

#include <algorithm>
#include <iostream>

using std::cout;
using std::endl;
using std::sort;

vector<Student> chooseSorting(const vector<Student>& students) {
    int sortChoice;
    cout << "\nPasirinkite rūšiavimo būdą:" << endl;
    cout << "0 - Nerūšiuotas (pradinė tvarka)" << endl;
    cout << "1 - Pagal vardą" << endl;
    cout << "2 - Pagal pavardę" << endl;
    cout << "3 - Pagal galitinį vidurkį" << endl;
    cout << "4 - Pagal galitinę medianą" << endl;
    sortChoice = readIntInRange("Pasirinkimas: ", 0, 4);

    vector<Student> resultStudents = students;

    if (sortChoice == 0) {
        cout << "Rodomi nerūšiuoti rezultatai (pradinėje tvarkoj)." << endl;
        return resultStudents;
    }

    cout << "\nPasirinkite rūšiavimo tvarką:" << endl;
    cout << "1 - Didėjanti" << endl;
    cout << "2 - Mažėjanti" << endl;
    int orderChoice = readIntInRange("Pasirinkimas: ", 1, 2);
    bool ascending = (orderChoice == 1);

    auto lessByChoice = [sortChoice](const Student& a, const Student& b) {
        switch (sortChoice) {
            case 1:
                if (a.name == b.name) return a.surname < b.surname;
                return a.name < b.name;
            case 2:
                if (a.surname == b.surname) return a.name < b.name;
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
    };

    if (ascending) {
        sort(resultStudents.begin(), resultStudents.end(), lessByChoice);
    } else {
        sort(resultStudents.begin(), resultStudents.end(),
            [&lessByChoice](const Student& a, const Student& b) {
                return lessByChoice(b, a);
            }
        );
    }

    return resultStudents;
}
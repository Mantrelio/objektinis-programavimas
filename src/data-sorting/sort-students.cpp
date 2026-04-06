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
    cout << "\nChoose sorting option:" << endl;
    cout << "0 - Unsorted (original order)" << endl;
    cout << "1 - By name" << endl;
    cout << "2 - By surname" << endl;
    cout << "3 - By final average" << endl;
    cout << "4 - By final median" << endl;
    sortChoice = readIntInRange("Choice: ", 0, 4);

    vector<Student> resultStudents = students;

    if (sortChoice == 0) {
        cout << "Showing unsorted results (original order)." << endl;
        return resultStudents;
    }

    cout << "\nChoose sorting order:" << endl;
    cout << "1 - Ascending" << endl;
    cout << "2 - Descending" << endl;
    int orderChoice = readIntInRange("Choice: ", 1, 2);
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
#include "sort-students.h"

#include "input-utils.h"
#include "student-grading.h"

#include <algorithm>
#include <iostream>
#include <deque>
#include <list>
#include <type_traits>

using std::cout;
using std::endl;
using std::sort;

template <typename T>
T sortStudents(const T& students, int sortChoice, bool ascending) {
    T resultStudents = students;

    if (sortChoice == 0) {
        return resultStudents;
    }

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
        if constexpr (std::is_same_v<T, std::list<Student>>) {
            resultStudents.sort(lessByChoice);
        } else {
            sort(resultStudents.begin(), resultStudents.end(), lessByChoice);
        }
    } else {
        if constexpr (std::is_same_v<T, std::list<Student>>) {
            resultStudents.sort([&lessByChoice](const Student& a, const Student& b) {
                return lessByChoice(b, a);
            });
        } else {
            sort(resultStudents.begin(), resultStudents.end(),
                [&lessByChoice](const Student& a, const Student& b) {
                    return lessByChoice(b, a);
                }
            );
        }
    }

    return resultStudents;
}

template <typename T>
T runSortStudentsChoicePrompt(const T& students) {
    int sortChoice;
    cout << "\nPasirinkite rūšiavimo būdą:" << endl;
    cout << "0 - Nerūšiuotas (pradinė tvarka)" << endl;
    cout << "1 - Pagal vardą" << endl;
    cout << "2 - Pagal pavardę" << endl;
    cout << "3 - Pagal galitinį vidurkį" << endl;
    cout << "4 - Pagal galitinę medianą" << endl;
    sortChoice = readIntInRange("Pasirinkimas: ", 0, 4);

    if (sortChoice == 0) {
        cout << "Rodomi nerūšiuoti rezultatai (pradinėje tvarkoj)." << endl;
        return students;
    }

    cout << "\nPasirinkite rūšiavimo tvarką:" << endl;
    cout << "1 - Didėjanti" << endl;
    cout << "2 - Mažėjanti" << endl;
    int orderChoice = readIntInRange("Pasirinkimas: ", 1, 2);

    return sortStudents(students, sortChoice, orderChoice == 1);
}

template vector<Student> sortStudents(const vector<Student>&, int, bool);
template std::list<Student> sortStudents(const std::list<Student>&, int, bool);
template std::deque<Student> sortStudents(const std::deque<Student>&, int, bool);

template vector<Student> runSortStudentsChoicePrompt(const vector<Student>&);
template std::list<Student> runSortStudentsChoicePrompt(const std::list<Student>&);
template std::deque<Student> runSortStudentsChoicePrompt(const std::deque<Student>&);
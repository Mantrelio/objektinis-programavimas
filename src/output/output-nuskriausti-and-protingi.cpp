#include "output-nuskriausti-and-protingi.h"
#include "student-grading.h"
#include "sort-students.h"
#include "output-results.h"

#include <vector>

using std::vector;

void outputNuskriaustiAndProtingi(vector<Student> &students) {
    vector<Student> nuskriausti, protingi;
    for (Student student : students) {
        if (calculateFinalGradeAverage(student.homeworkGrades, student.examGrade) >= 5) {
            protingi.push_back(student);
        } else {
            nuskriausti.push_back(student);
        }
    }

    cout << "\n--- Nuskriausti ---" << endl;
    sortStudents(nuskriausti);

    cout << "\n--- Protingi ---" << endl;
    sortStudents(protingi);

    cout << "\n--- Nuskriausti ---" << endl;
    handleResultOutput(nuskriausti);

    cout << "\n--- Protingi ---" << endl;
    handleResultOutput(protingi);
}
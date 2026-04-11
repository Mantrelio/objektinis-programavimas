#include "sort-nuskriausti-and-protingi.h"

#include "student-grading.h"

std::pair<vector<Student>, vector<Student>> sortNuskriaustiAndProtingi(const vector<Student>& students) {
    vector<Student> nuskriausti, protingi;
    for (Student student : students) {
        if (calculateFinalGradeAverage(student.homeworkGrades, student.examGrade) >= 5) {
            protingi.push_back(student);
        } else {
            nuskriausti.push_back(student);
        }
    }

    return {nuskriausti, protingi};
}
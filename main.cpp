#include <iostream>
#include "student.h"

using std::cout;
using std::cin;
using std::endl;

double calculateFinalGradeAverage(vector<int> homeworkGrades, int examGrade) {
    double homeworkGradeSum = 0;

    for (int i = 0; i < homeworkGrades.size(); i++) {
        homeworkGradeSum += homeworkGrades[i];
    }

    return homeworkGradeSum / homeworkGrades.size() * 0.4 + examGrade * 0.6;
}

int main() {
    return 0;
}

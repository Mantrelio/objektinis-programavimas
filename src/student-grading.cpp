#include "student-grading.h"

#include <algorithm>
#include <cstdlib>

int randomGrade(int min, int max) {
    return rand() % (max - min + 1) + min;
}

double calculateFinalGradeAverage(std::vector<int> homeworkGrades, int examGrade) {
    double homeworkGradeSum = 0;

    for (int grade : homeworkGrades) {
        homeworkGradeSum += grade;
    }

    return homeworkGradeSum / homeworkGrades.size() * 0.4 + examGrade * 0.6;
}

double calculateFinalGradeMedian(std::vector<int> homeworkGrades, int examGrade) {
    std::vector<int> sortedGrades = homeworkGrades;
    std::sort(sortedGrades.begin(), sortedGrades.end());

    const std::size_t n = sortedGrades.size();
    double median;
    if (n % 2 == 0) {
        median = (sortedGrades[n / 2 - 1] + sortedGrades[n / 2]) / 2.0;
    } else {
        median = sortedGrades[n / 2];
    }

    return median * 0.4 + examGrade * 0.6;
}

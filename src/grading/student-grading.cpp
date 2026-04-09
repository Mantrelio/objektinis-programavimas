#include "student-grading.h"

#include <algorithm>
#include <cstdlib>

using std::sort;

int randomGrade(int min, int max) {
    return min + rand() % (max - min + 1);
}

double calculateFinalGradeMedian(const vector<int>& homeworkGrades, int examGrade) {
    vector<int> sortedGrades = homeworkGrades;
    sort(sortedGrades.begin(), sortedGrades.end());
    
    double median;
    int size = sortedGrades.size();
    
    if (size % 2 == 0) {
        median = (sortedGrades[size / 2 - 1] + sortedGrades[size / 2]) / 2.0;
    } else {
        median = sortedGrades[size / 2];
    }
    
    return median * 0.4 + examGrade * 0.6;
}

double calculateFinalGradeAverage(const vector<int>& homeworkGrades, int examGrade) {
    double homeworkGradeSum = 0;

    for (int i = 0; i < homeworkGrades.size(); i++) {
        homeworkGradeSum += homeworkGrades[i];
    }

    return homeworkGradeSum / homeworkGrades.size() * 0.4 + examGrade * 0.6;
}
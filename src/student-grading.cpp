#include "student-grading.h"

#include <algorithm>
#include <cstdlib>
#include <numeric>

namespace {

constexpr double k_homework_weight = 0.4;
constexpr double k_exam_weight = 0.6;

double homeworkAverage(const std::vector<int>& grades) {
    if (grades.empty()) {
        return 0.0;
    }
    const double sum = std::accumulate(grades.begin(), grades.end(), 0.0);
    return sum / static_cast<double>(grades.size());
}

double homeworkMedian(std::vector<int> grades) {
    if (grades.empty()) {
        return 0.0;
    }
    std::sort(grades.begin(), grades.end());
    const std::size_t n = grades.size();
    if (n % 2 == 0) {
        return (grades[n / 2 - 1] + grades[n / 2]) / 2.0;
    }
    return static_cast<double>(grades[n / 2]);
}

double weightedFinal(double homeworkComponent, int examGrade) {
    return k_homework_weight * homeworkComponent + k_exam_weight * static_cast<double>(examGrade);
}

}  // namespace

int randomGrade(int min, int max) {
    return rand() % (max - min + 1) + min;
}

double calculateFinalGradeAverage(const std::vector<int>& homeworkGrades, int examGrade) {
    return weightedFinal(homeworkAverage(homeworkGrades), examGrade);
}

double calculateFinalGradeMedian(const std::vector<int>& homeworkGrades, int examGrade) {
    return weightedFinal(homeworkMedian(homeworkGrades), examGrade);
}

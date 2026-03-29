#pragma once

#include <string>
#include <vector>

int randomGrade(int min = 1, int max = 10);
double calculateFinalGradeAverage(const std::vector<int>& homeworkGrades, int examGrade);
double calculateFinalGradeMedian(const std::vector<int>& homeworkGrades, int examGrade);

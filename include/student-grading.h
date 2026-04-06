#pragma once

#include <vector>

using std::vector;

int randomGrade(int min = 1, int max = 10);
double calculateFinalGradeAverage(const vector<int>& homeworkGrades, int examGrade);
double calculateFinalGradeMedian(const vector<int>& homeworkGrades, int examGrade);

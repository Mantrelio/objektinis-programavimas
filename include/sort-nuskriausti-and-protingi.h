#pragma once

#include "student-vector.h"
#include "student-grading.h"

#include <utility>

template <typename T>
std::pair<T, T> sortNuskriaustiAndProtingi(const T& students) {
	T nuskriausti;
	T protingi;

	for (const Student& student : students) {
		if (calculateFinalGradeAverage(student.homeworkGrades, student.examGrade) >= 5) {
			protingi.push_back(student);
		} else {
			nuskriausti.push_back(student);
		}
	}

	return {nuskriausti, protingi};
}
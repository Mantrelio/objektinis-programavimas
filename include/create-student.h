#pragma once

#include "student-vector.h"

Student createStudentManual();
Student createStudentRandomGrades();
Student createStudentFullyRandom();

template <typename T>
T createStudentsFromFile(const string& filename);

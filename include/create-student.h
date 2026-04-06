#pragma once

#include "student-vector.h"

Student createStudentManual();
Student createStudentRandomGrades();
Student createStudentFullyRandom();
vector<Student> createStudentsFromFile(const string& filename);

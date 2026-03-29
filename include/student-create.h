#pragma once

#include "student-vector.h"

string randomName();
string randomSurname();

Student createStudentManual();
Student createStudentRandomGrades();
Student createStudentFullyRandom();
vector<Student> createStudentsFromFile(const string& filename);

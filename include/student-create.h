#pragma once

#include "student-vector.h"

string randomName();
string randomSurname();

Student createStudentManual();
Student createStudentRandomGrades();
Student createStudentFullyRandom();
Student create_student_fully_random_silent();
vector<Student> createStudentsFromFile(const string& filename);

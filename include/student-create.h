#pragma once

#include <cstddef>

#include "student-vector.h"

string randomName();
string randomSurname();

Student createStudentManual();
Student createStudentRandomGrades();
Student createStudentFullyRandom();
Student create_student_fully_random_silent();
vector<Student> createStudentsFromFile(const string& filename);

/** Reads the file once and appends each student to protingi or kvaili by final average.
 *  Does not keep a full copy of all students in a third vector (lower peak memory). */
std::size_t readStudentsFromFileSplitByFinalAverage(const string& filename,
    vector<Student>& protingi, vector<Student>& kvaili, double average_boundary);

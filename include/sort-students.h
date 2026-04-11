#pragma once

#include "student-vector.h"

template <typename T>
T runSortStudentsChoicePrompt(const T& students);

template <typename T>
T sortStudents(const T& students, int sortChoice, bool ascending);
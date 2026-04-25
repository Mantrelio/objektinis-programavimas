#pragma once

#include "create-student.h"
#include "input-utils.h"
#include "output-results.h"
#include "sort-students.h"
#include "student-vector.h"
#include "student-grading.h"

#include <utility>

template <typename T>
void handleSortNuskriaustiAndProtingiFromFile();

template <typename T>
std::pair<T, T> sortNuskriaustiAndProtingiFirstStrategy(const T& students);

template <typename T>
T sortNuskriaustiAndProtingiSecondStrategy(T& students);

template <typename T>
std::pair<T, T> sortNuskriaustiAndProtingiThirdStrategy(T& students);
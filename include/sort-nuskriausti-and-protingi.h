#pragma once

#include "student-vector.h"
#include "student-grading.h"

#include <utility>

template <typename T>
std::pair<T, T> sortNuskriaustiAndProtingiFirstStrategy(const T& students);

template <typename T>
T sortNuskriaustiAndProtingiSecondStrategy(T& students);
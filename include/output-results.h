#pragma once

#include "student-vector.h"

#include <iostream>

template <typename T>
void outputResults(const T& students, std::ostream& out);

void runHandleResultOutputPrompt(const vector<Student>& students);

template <typename T>
void handleResultOutput(const T& students, int outputChoice, const string& outFilename);

void chooseOutputAndPrint(const vector<Student>& students);

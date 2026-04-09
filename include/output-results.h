#pragma once

#include "student-vector.h"

#include <iostream>

void outputResults(const vector<Student>& students, std::ostream& out);
void handleResultOutput(const vector<Student>& students);
void handleResultOutput(const vector<Student>& students, int outputChoice, const string& outFilename);
void chooseOutputAndPrint(const vector<Student>& students);

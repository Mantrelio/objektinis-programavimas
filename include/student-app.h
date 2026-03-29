#pragma once

#include "student-vector.h"
#include <iostream>

void printResults(const vector<Student>& students, std::ostream& out);
void showMainMenu();
void handleMenuChoice(int choice, vector<Student>& students);
void collectStudents(vector<Student>& students);
vector<Student> chooseSorting(const vector<Student>& students);
void outputResults(const vector<Student>& students);
void chooseOutputAndPrint(const vector<Student>& students);
void split_protingi_kvaili(int benchmark_runs = 1);

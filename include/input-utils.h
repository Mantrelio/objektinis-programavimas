#pragma once

#include <iostream>
#include <istream>
#include <ostream>
#include <string>

using std::istream;
using std::ostream;
using std::string;

int readIntInRange(const string& prompt, int min, int max);
string readSingleStringToken(const string& prompt);
char readYesOrNo(const string& prompt);
int readSingleIntToken(const string& prompt);

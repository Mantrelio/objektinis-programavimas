#pragma once

#include <iostream>
#include <string>

int read_int(std::istream& in, std::ostream& out, const std::string& prompt);
int read_int_in_range(std::istream& in, std::ostream& out, const std::string& prompt, int min,
    int max);

#include "input-utils.h"

#include <cctype>
#include <cstring>
#include <limits>
#include <stdexcept>
#include <string>

namespace {

const char k_empty_line[] = "empty_line";

std::string read_line(std::istream& in) {
    std::string line;
    if (!std::getline(in, line)) {
        throw std::runtime_error("input ended unexpectedly");
    }
    return line;
}

bool is_blank(const std::string& s) {
    return s.find_first_not_of(" \t\r\f\v") == std::string::npos;
}

int parse_int_strict(const std::string& line) {
    std::size_t pos = 0;
    const long long v = std::stoll(line, &pos, 10);
    while (pos < line.size() && std::isspace(static_cast<unsigned char>(line[pos]))) {
        ++pos;
    }
    if (pos != line.size()) {
        throw std::invalid_argument("non-numeric trailing text");
    }
    if (v > std::numeric_limits<int>::max() || v < std::numeric_limits<int>::min()) {
        throw std::out_of_range("value");
    }
    return static_cast<int>(v);
}

}  // namespace

int read_int(std::istream& in, std::ostream& out, const std::string& prompt) {
    while (true) {
        out << prompt;
        try {
            const std::string line = read_line(in);
            if (is_blank(line)) {
                throw std::invalid_argument(k_empty_line);
            }
            return parse_int_strict(line);
        } catch (const std::invalid_argument& e) {
            if (std::strcmp(e.what(), k_empty_line) == 0) {
                out << "Input cannot be empty.\n";
            } else {
                out << "Invalid input: please enter a whole number (no letters).\n";
            }
        } catch (const std::out_of_range&) {
            out << "Number is out of range.\n";
        }
    }
}

int read_int_in_range(std::istream& in, std::ostream& out, const std::string& prompt, int min,
    int max) {
    while (true) {
        const int v = read_int(in, out, prompt);
        if (v >= min && v <= max) {
            return v;
        }
        out << "Please enter a number between " << min << " and " << max << ".\n";
    }
}

std::string read_required_line(std::istream& in, std::ostream& out, const std::string& prompt) {
    while (true) {
        out << prompt;
        const std::string line = read_line(in);
        if (!is_blank(line)) {
            return line;
        }
        out << "Input cannot be empty.\n";
    }
}

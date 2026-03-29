#include "input-utils.h"

#include <cctype>
#include <limits>
#include <stdexcept>
#include <string>

namespace {

std::string read_non_empty_line(std::istream& in) {
    std::string line;
    while (std::getline(in, line)) {
        if (line.find_first_not_of(" \t\r\f\v") != std::string::npos) {
            return line;
        }
    }
    throw std::runtime_error("input ended unexpectedly");
}

}  // namespace

int read_int(std::istream& in, std::ostream& out, const std::string& prompt) {
    while (true) {
        out << prompt;
        try {
            const std::string line = read_non_empty_line(in);
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
        } catch (const std::invalid_argument&) {
            out << "Invalid input: please enter a whole number (no letters).\n";
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

#include "input-utils.h"

#include <limits>
#include <stdexcept>
#include <string>

namespace {

std::string read_line(std::istream& in) {
    std::string line;
    if (!std::getline(in, line)) {
        throw std::runtime_error("įvestis netikėtai baigėsi");
    }
    return line;
}

bool is_blank(const std::string& s) {
    return s.find_first_not_of(" \t\r\f\v") == std::string::npos;
}

int parse_int_strict(const std::string& line) {
    std::size_t pos = 0;
    const long long v = std::stoll(line, &pos, 10);
    if (line.find_first_not_of(" \t\r\f\v", pos) != std::string::npos) {
        throw std::invalid_argument("po skaičiaus liko netinkamas tekstas");
    }
    if (v > std::numeric_limits<int>::max() || v < std::numeric_limits<int>::min()) {
        throw std::out_of_range("reikšmė");
    }
    return static_cast<int>(v);
}

std::string read_line_until_nonempty(std::istream& in, std::ostream& out,
    const std::string& prompt) {
    while (true) {
        out << prompt;
        const std::string line = read_line(in);
        if (!is_blank(line)) {
            return line;
        }
        out << "Įvestis negali būti tuščia.\n";
    }
}

}  // namespace

int read_int(std::istream& in, std::ostream& out, const std::string& prompt) {
    while (true) {
        try {
            return parse_int_strict(read_line_until_nonempty(in, out, prompt));
        } catch (const std::invalid_argument&) {
            out << "Netinkama įvestis: įveskite sveikąjį skaičių (be raidžių).\n";
        } catch (const std::out_of_range&) {
            out << "Skaičius nepatenka į leidžiamą intervalą.\n";
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
        out << "Įveskite skaičių nuo " << min << " iki " << max << ".\n";
    }
}

std::string read_required_line(std::istream& in, std::ostream& out, const std::string& prompt) {
    return read_line_until_nonempty(in, out, prompt);
}

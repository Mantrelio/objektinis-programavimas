#include "input-utils.h"

#include <cctype>
#include <sstream>

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::istringstream;
using std::toupper;
using std::ws;

int readIntInRange(const string& prompt, int min, int max) {
    string line;
    while (true) {
        cout << prompt;
        getline(cin >> ws, line);

        try {
            int value;
            istringstream iss(line);

            if(!(iss >> value) || (iss >> ws && !iss.eof())) {
                throw std::invalid_argument("Netinkamas Skaicius");
            }

            if (value < min || value > max) {
                throw std::out_of_range("Skaicius uz galimybiu ribu");
            }

            return value;
        } catch (const std::invalid_argument&) {
            cout << "Prašau įvesti vieną galiojantį sveikąjį skaičių." << endl;
        } catch (const std::out_of_range&) {
            cout << "Reikšmė turi būti nuo " << min << " iki " << max << "\n";
        }
    }
}

string readSingleStringToken(const string& prompt) {
    string line;

    while (true) {
        cout << prompt;
        getline(cin >> ws, line);

        try {
            string value;
            istringstream iss(line);

            if (!(iss >> value)) {
                throw std::invalid_argument("missing token");
            }

            if (iss >> ws && !iss.eof()) {
                throw std::runtime_error("extra tokens");
            }

            return value;
        } catch (const std::invalid_argument&) {
            cout << "Prašau įvesti reikšmę." << endl;
        } catch (const std::runtime_error&) {
            cout << "Prašau įvesti tik vieną žodį." << endl;
        }
    }
}

char readYesOrNo(const string& prompt) {
    string line;

    while (true) {
        cout << prompt;
        getline(cin >> ws, line);

        try {
            char answer;
            string extra;
            istringstream iss(line);

            if (!(iss >> answer) || (iss >> extra)) {
                throw std::invalid_argument("invalid yes/no input");
            }

            char answerToUpper = static_cast<char>(toupper(static_cast<unsigned char>(answer)));
            if (answerToUpper == 'Y' || answerToUpper == 'N' ) {
                return answerToUpper;
            }

            throw std::invalid_argument("answer is not y/n");
        } catch (const std::invalid_argument&) {
            cout << "Prašau įvesti tik y arba n" << endl;
        }
    }
}

int readSingleIntToken(const string& prompt) {
    string line;

    while (true) {
        cout << prompt;
        getline(cin >> ws, line);

        try {
            int value;
            istringstream iss(line);

            if (!(iss >> value) || (iss >> ws && !iss.eof())) {
                throw std::invalid_argument("invalid integer input");
            }

            return value;
        } catch (const std::invalid_argument&) {
            cout << "Prasau ivesti tik viena sveikaji skaiciu." << endl;
        }
    }
}
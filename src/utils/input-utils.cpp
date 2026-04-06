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
    int value;
    while (true) {
        cout << prompt;
        getline(cin >> ws, line);

        istringstream iss(line);

        if(!(iss >> value) || (iss >> ws && !iss.eof())) {
            cout << "Prašau įvesti vieną galiojantį sveikąjį skaičių." << endl;
            continue;
        }

        if (value < min || value > max) {
            cout << "Reikšmė turi būti nuo " << min << " iki " << max << "\n";
            continue;
        }

        return value;
    }
}

int readSingleIntToken(const string& prompt) {
    string line;
    int value;
    while (true) {
        cout << prompt;
        getline(cin >> ws, line);

        istringstream iss(line);

        if(!(iss >> value) || (iss >> ws && !iss.eof())) {
            cout << "Prašau įvesti vieną galiojantį sveikąjį skaičių." << endl;
            continue;
        }

        if (value < 0) {
            cout << "Prašau įvesti neneigiamą sveikąjį skaičių." << endl;
            continue;
        }

        return value;
    }
}

string readSingleStringToken(const string& prompt) {
    string line;
    string value;

    while (true) {
        cout << prompt;
        getline(cin >> ws, line);

        istringstream iss(line);

        if (!(iss >> value)) {
            cout << "Prašau įvesti reikšmę." << endl;
        }

        if (iss >> ws && !iss.eof()) {
            cout << "Prašau įvesti tik vieną žodį." << endl;
            continue;
        }

        return value;
    }
}

char readYesOrNo(const string& prompt) {
    string line;
    char answer;
    string extra;

    while (true) {
        cout << prompt;
        getline(cin >> ws, line);

        istringstream iss(line);
        if (!(iss >> answer) || (iss >> extra)) {
            cout << "Prašau įvesti tik y arba n" << endl;
            continue;
        }

        char answerToUpper = toupper(answer);
        if (answerToUpper == 'Y' || answerToUpper == 'N' ) {
            return answerToUpper;
        }
    }
}
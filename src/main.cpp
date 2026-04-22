#include "student-menu.h"
#include "input-utils.h"

#include <deque>
#include <iostream>
#include <list>

int main() {
    cout << "Pasirinkite konteinerio tipa:" << endl;
    cout << "1 - vector<Student>" << endl;
    cout << "2 - list<Student>" << endl;
    cout << "3 - deque<Student>" << endl;

    const int containerChoice = readIntInRange("Pasirinkimas: ", 1, 3);

    switch (containerChoice) {
        case 1:
            startMainMenu<vector<Student>>();
            break;
        case 2:
            startMainMenu<std::list<Student>>();
            break;
        case 3:
            startMainMenu<std::deque<Student>>();
            break;
    }

    return 0;
}
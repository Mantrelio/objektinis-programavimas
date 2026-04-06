#include "student-menu.h"

#include "create-student.h"
#include "input-utils.h"
#include "output-results.h"

#include <iostream>
#include <stdexcept>

namespace {

void announceNextStudent(int studentIndex) {
    cout << "\n--- Student " << studentIndex << " ---" << endl;
}

}  // namespace

void showMainMenu() {
    cout << "\n=== MENU ===" << endl;
    cout << "1 - Manual input (enter all values)" << endl;
    cout << "2 - Enter name/surname, generate grades" << endl;
    cout << "3 - Generate all data randomly" << endl;
    cout << "4 - Read students from file" << endl;
    cout << "5 - Exit and show results" << endl;
    cout << "Choose option: ";
}

void handleMenuChoice(int choice, vector<Student>& students) {
    int nextIndex = students.size() + 1;

    switch (choice) {
        case 1:
            announceNextStudent(nextIndex);
            students.push_back(createStudentManual());
            break;
        case 2:
            announceNextStudent(nextIndex);
            students.push_back(createStudentRandomGrades());
            break;
        case 3:
            announceNextStudent(nextIndex);
            students.push_back(createStudentFullyRandom());
            break;
        case 4: {
            const string filename =
                readSingleStringToken("Enter file name (e.g. data.txt): ");
            try {
                const vector<Student> fileStudents = createStudentsFromFile(filename);
                if (fileStudents.empty()) {
                    cout << "Failas atidarytas, bet tinkamu studentu eiluciu nerasta "
                            "(tuscias failas arba netinkamos eilutes)."
                         << endl;
                } else {
                    cout << "Loaded " << fileStudents.size() << " students from file." << endl;
                }
                students.insert(students.end(), fileStudents.begin(), fileStudents.end());
            } catch (const std::exception& e) {
                cout << "Klaida skaitant \"" << filename << "\": " << e.what() << endl;
            }
            break;
        }
        case 5:
            chooseOutputAndPrint(students);
            break;
    }
}

void startMainMenu() {
    vector<Student> students;

    int choice = 0;

    while (choice != 5) {
        showMainMenu();
        choice = readIntInRange("", 1, 5);
        handleMenuChoice(choice, students);
    }
}

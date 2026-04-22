#include "student-menu.h"

#include "create-student.h"
#include "input-utils.h"
#include "output-results.h"

#include <iostream>
#include <stdexcept>

namespace {

void announceNextStudent(int studentIndex) {
    cout << "\n--- Studentas " << studentIndex << " ---" << endl;
}

}  // namespace

void showMainMenu() {
    cout << "\n=== MENIU ===" << endl;
    cout << "1 - Rankinė įvestis (įvesti visas reikšmes)" << endl;
    cout << "2 - Įvesti vardą/pavardę, generuoti pažymius" << endl;
    cout << "3 - Generuoti visus duomenis atsitiktinai" << endl;
    cout << "4 - Skaityti studentus iš failo" << endl;
    cout << "5 - Baigti ir peržiūrėti rezultatus" << endl;
    cout << "Pasirinkite variantą: ";
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
                readSingleStringToken("Suveskite failo pavadinimą (pvz. data.txt): ");
            try {
                const vector<Student> fileStudents = createStudentsFromFile(filename);
                
                cout << "Sėkmingai nuskaityti " << fileStudents.size() << " studentai iš failo." << endl;
                
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
        choice = readIntInRange("Pasirinkimas: ", 1, 5);
        handleMenuChoice(choice, students);
    }
}

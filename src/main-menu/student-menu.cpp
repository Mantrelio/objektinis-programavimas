#include "student-menu.h"

#include "create-student.h"
#include "input-utils.h"
#include "output-results.h"
#include "generate-student-list.h"
#include "output-nuskriausti-and-protingi.h"
#include "generate-student-list-test.h"
#include "output-nuskriausti-and-protingi-test.h"

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
    cout << "5 - Generuoti studentu sarasa" << endl;
    cout << "6 - Skirstyti i nuskriaustus ir protingus" << endl;
    cout << "7 - Testuoti failo kurima" << endl;
    cout << "8 - Testuoti studentu skirstyma i nuskriaustus ir protingus" << endl;
    cout << "9 - Baigti ir peržiūrėti rezultatus" << endl;
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
                const vector<Student> fileStudents = createStudentsFromFile<vector<Student>>(filename);
                if (fileStudents.empty()) {
                    cout << "Failas atidarytas, bet tinkamų studentų eilučių nerasta "
                            "(tuščias failas arba netinkamos eilutės)."
                         << endl;
                } else {
                    cout << "Sėkmingai nuskaityti " << fileStudents.size() << " studentai iš failo." << endl;
                }
                students.insert(students.end(), fileStudents.begin(), fileStudents.end());
            } catch (const std::exception& e) {
                cout << "Klaida skaitant \"" << filename << "\": " << e.what() << endl;
            }
            break;
        }
        case 5: 
            handleGenerateStudentListFile();
            break;
        case 6: {
            const string filename = readSingleStringToken("Suveskite failo pavadinimą (pvz. data.txt): ");
            vector<Student> students = createStudentsFromFile<vector<Student>>(filename);
            outputNuskriaustiAndProtingi(students);
            break;
        }
        case 7: 
            handleGenerateStudentListTest();
            break;
        case 8: 
            outputNuskriaustiAndProtingiTestForAllStudentsTxtFiles();
            break;
        case 9:
            chooseOutputAndPrint(students);
            break;
    }
}

void startMainMenu() {
    vector<Student> students;

    int choice = 0;

    while (choice != 9) {
        showMainMenu();
        choice = readIntInRange("Pasirinkimas: ", 1, 9);
        handleMenuChoice(choice, students);
    }
}

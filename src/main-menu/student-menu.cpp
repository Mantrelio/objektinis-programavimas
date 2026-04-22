#include "student-menu.h"

#include "create-student.h"
#include "input-utils.h"
#include "output-results.h"
#include "generate-student-list.h"
#include "generate-student-list-test.h"
#include "output-nuskriausti-and-protingi-test.h"
#include "sort-nuskriausti-and-protingi.h"
#include "sort-students.h"

#include <iostream>
#include <deque>
#include <list>
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

template <typename T>
void handleMenuChoice(int choice, T& students) {
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
            const string filename = readSingleStringToken("Suveskite failo pavadinimą (pvz. data.txt): ");
            try {
                const T fileStudents = createStudentsFromFile<T>(filename);
                cout << "Sėkmingai nuskaityti " << fileStudents.size() << " studentai iš failo." << endl;
                
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
            try {
                T fileStudents = createStudentsFromFile<T>(filename);

                runSortStudentsChoicePrompt(fileStudents);

                cout << "\nPasirinkite strategija:" << endl;
                cout << "1 - Pirma" << endl;
                cout << "2 - Antra" << endl;
                cout << "3 - Trecia" << endl;

                const int strategyChoice = readIntInRange("Pasirinkimas: ", 1, 3);

                T nuskriausti;
                T protingi;

                switch (strategyChoice) {
                    case 1: {
                        auto splitResult = sortNuskriaustiAndProtingiFirstStrategy(fileStudents);
                        nuskriausti = std::move(splitResult.first);
                        protingi = std::move(splitResult.second);
                        break;
                    }
                    case 2:
                        nuskriausti = sortNuskriaustiAndProtingiSecondStrategy(fileStudents);
                        protingi = std::move(fileStudents);
                        break;
                    case 3: {
                        auto splitResult = sortNuskriaustiAndProtingiThirdStrategy(fileStudents);
                        nuskriausti = std::move(splitResult.first);
                        protingi = std::move(splitResult.second);
                        break;
                    }
                }

                cout << "\n--- Nuskriausti ---" << endl;
                chooseOutputAndPrint(nuskriausti);

                cout << "\n--- Protingi ---" << endl;
                chooseOutputAndPrint(protingi);
            } catch (const std::exception& e) {
                cout << "Klaida skaitant \"" << filename << "\": " << e.what() << endl;
            }
            break;
        }
        case 7: 
            handleGenerateStudentListTest();
            break;
        case 8: 
            outputNuskriaustiAndProtingiTestForAllStudentsTxtFiles();
            break;
        case 9:
            runSortStudentsChoicePrompt(students);
            chooseOutputAndPrint(students);
            break;
    }
}

template void handleMenuChoice<vector<Student>>(int, vector<Student>&);
template void handleMenuChoice<std::list<Student>>(int, std::list<Student>&);
template void handleMenuChoice<std::deque<Student>>(int, std::deque<Student>&);

template <typename T>
void startMainMenu() {
    T students;

    int choice = 0;

    while (choice != 9) {
        showMainMenu();
        choice = readIntInRange("Pasirinkimas: ", 1, 9);
        handleMenuChoice(choice, students);
    }
}

template void startMainMenu<vector<Student>>();
template void startMainMenu<std::list<Student>>();
template void startMainMenu<std::deque<Student>>();

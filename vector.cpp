#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include "student-vector.h"

int randomGrade(int min = 1, int max = 10) {
    return rand() % (max - min + 1) + min;
}

string randomName() {
    const string names[] = {"Jonas", "Petras", "Antanas", "Marija", "Ona", "Jurate", "Tomas", "Mindaugas", "Ruta", "Greta"};
    return names[rand() % 10];
}

string randomSurname() {
    const string surnames[] = {"Jonaitis", "Petraitis", "Antanaitis", "Kazlauskas", "Zukauskas", "Jankauskas", "Paulauskas", "Stankevicius", "Vasiliauskas", "Baranauskas"};
    return surnames[rand() % 10];
}

double calculateFinalGradeAverage(vector<int> homeworkGrades, int examGrade) {
    double homeworkGradeSum = 0;

    for (int i = 0; i < homeworkGrades.size(); i++) {
        homeworkGradeSum += homeworkGrades[i];
    }

    return homeworkGradeSum / homeworkGrades.size() * 0.4 + examGrade * 0.6;
}

double calculateFinalGradeMedian(vector<int> homeworkGrades, int examGrade) {
    vector<int> sortedGrades = homeworkGrades;
    std::sort(sortedGrades.begin(), sortedGrades.end());
    
    double median;
    int size = sortedGrades.size();
    
    if (size % 2 == 0) {
        median = (sortedGrades[size / 2 - 1] + sortedGrades[size / 2]) / 2.0;
    } else {
        median = sortedGrades[size / 2];
    }
    
    return median * 0.4 + examGrade * 0.6;
}

void printResults(const vector<Student>& students, std::ostream& out) {
    out << "\n" << string(70, '=') << endl;
    out << left  << setw(20) << "Name" 
        << left  << setw(20) << "Surname" 
        << right << setw(15) << "Final (Avg.)"
        << right << setw(15) << "Final (Med.)" << endl;
    out << string(70, '-') << endl;
    
    for (int i = 0; i < students.size(); i++) {
        double finalAvg = calculateFinalGradeAverage(students[i].homeworkGrades, students[i].examGrade);
        double finalMed = calculateFinalGradeMedian(students[i].homeworkGrades, students[i].examGrade);

        out << left  << setw(20) << students[i].name 
            << left  << setw(20) << students[i].surname 
            << right << std::fixed << std::setprecision(2) << setw(15) << finalAvg
            << right << std::fixed << std::setprecision(2) << setw(15) << finalMed << endl;
    }
    out << string(70, '=') << endl;
}

Student createStudentManual() {
    Student student = Student();

    cout << "Enter student name: ";
    cin >> student.name;
    
    cout << "Enter student surname: ";
    cin >> student.surname;
    
    cout << "Enter exam grade: ";
    cin >> student.examGrade;

    char continueHomework = 'y';
    int homeworkNumber = 1;
    
    while (continueHomework == 'y' || continueHomework == 'Y') {
        cout << "Enter homework grade " << homeworkNumber << ": ";
        int grade;
        cin >> grade;
        student.homeworkGrades.push_back(grade);
        homeworkNumber++;
        
        cout << "Add another homework grade? (y/n): ";
        cin >> continueHomework;
    }
    
    return student;
}

Student createStudentRandomGrades() {
    Student student = Student();

    cout << "Enter student name: ";
    cin >> student.name;
    
    cout << "Enter student surname: ";
    cin >> student.surname;
    
    student.examGrade = randomGrade();
    cout << "Generated exam grade: " << student.examGrade << endl;

    int homeworkCount = randomGrade(3, 10);
    
    cout << "Generated " << homeworkCount << " homework grades: ";
    for (int i = 0; i < homeworkCount; i++) {
        int grade = randomGrade();
        student.homeworkGrades.push_back(grade);
        cout << grade;
        if (i < homeworkCount - 1) cout << ", ";
    }
    cout << endl;
    
    return student;
}

Student createStudentFullyRandom() {
    Student student = Student();

    student.name = randomName();
    student.surname = randomSurname();
    student.examGrade = randomGrade();

    int homeworkCount = randomGrade(3, 10);
    
    for (int i = 0; i < homeworkCount; i++) {
        student.homeworkGrades.push_back(randomGrade());
    }
    
    cout << "Generated student: " << student.name << " " << student.surname << endl;
    
    return student;
}

vector<Student> createStudentsFromFile(const string& filename) {
    vector<Student> studentsFromFile;
    std::ifstream in(filename);

    if (!in) {
        cout << "Failed to open file: " << filename << endl;
        return studentsFromFile;
    }

    string headerLine;
    std::getline(in, headerLine);

    string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;

        std::istringstream iss(line);
        Student student;
        student.homeworkGrades.clear();

        if (!(iss >> student.name >> student.surname)) {
            continue; 
        }

        int grade;
        vector<int> allGrades;
        while (iss >> grade) {
            allGrades.push_back(grade);
        }

        if (allGrades.empty()) {
            continue; 
        }

        student.examGrade = allGrades.back();
        allGrades.pop_back();
        student.homeworkGrades = allGrades;

        studentsFromFile.push_back(student);
    }

    return studentsFromFile;
}

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
    switch (choice) {
        case 1:
            cout << "\n--- Student " << (students.size() + 1) << " ---" << endl;
            students.push_back(createStudentManual());
            break;
        case 2:
            cout << "\n--- Student " << (students.size() + 1) << " ---" << endl;
            students.push_back(createStudentRandomGrades());
            break;
        case 3:
            cout << "\n--- Student " << (students.size() + 1) << " ---" << endl;
            students.push_back(createStudentFullyRandom());
            break;
        case 4: {
            string filename;
            cout << "Enter file name (e.g. data.txt): ";
            cin >> filename;
            vector<Student> fileStudents = createStudentsFromFile(filename);
            cout << "Loaded " << fileStudents.size() << " students from file." << endl;
            students.insert(students.end(), fileStudents.begin(), fileStudents.end());
            break;
        }
    }
}

void collectStudents(vector<Student>& students) {
    int choice = 0;

    while (choice != 5) {
        showMainMenu();
        cin >> choice;
        
        if (choice == 5) break;
        
        if (choice < 1 || choice > 5) {
            cout << "Invalid option. Please try again." << endl;
            continue;
        }
        
        handleMenuChoice(choice, students);
    }
}

vector<Student> chooseSorting(const vector<Student>& students) {
    int sortChoice = 0;
    cout << "\nChoose sorting option:" << endl;
    cout << "0 - Unsorted (original order)" << endl;
    cout << "1 - By name" << endl;
    cout << "2 - By surname" << endl;
    cout << "3 - By final average" << endl;
    cout << "4 - By final median" << endl;
    cout << "Choice: ";
    cin >> sortChoice;

    vector<Student> resultStudents = students;

    if (sortChoice == 0) {
        cout << "Showing unsorted results (original order)." << endl;
    } else if (sortChoice >= 1 && sortChoice <= 4) {
        std::sort(resultStudents.begin(), resultStudents.end(),
            [sortChoice](const Student& a, const Student& b) {
                switch (sortChoice) {
                    case 1: 
                        if (a.name == b.name) return a.surname < b.surname;
                        return a.name < b.name;
                    case 2: 
                        if (a.surname == b.surname) return a.name < b.name;
                        return a.surname < b.surname;
                    case 3: {
                        double fa = calculateFinalGradeAverage(a.homeworkGrades, a.examGrade);
                        double fb = calculateFinalGradeAverage(b.homeworkGrades, b.examGrade);
                        return fa < fb;
                    }
                    case 4: {
                        double fa = calculateFinalGradeMedian(a.homeworkGrades, a.examGrade);
                        double fb = calculateFinalGradeMedian(b.homeworkGrades, b.examGrade);
                        return fa < fb;
                    }
                    default:
                        return a.name < b.name;
                }
            }
        );
    } else {
        cout << "Invalid sorting option. Showing unsorted results (original order)." << endl;
    }

    return resultStudents;
}

void outputResults(const vector<Student>& students) {
    const vector<Student>& resultStudents = students;

    int outputChoice = 0;
    cout << "\nChoose output method:" << endl;
    cout << "1 - Show results in console" << endl;
    cout << "2 - Save results to text file" << endl;
    cout << "Choice: ";
    cin >> outputChoice;

    if (outputChoice == 2) {
        string outFilename;
        cout << "Enter output filename (e.g. results.txt): ";
        cin >> outFilename;

        std::ofstream outFile(outFilename);
        if (!outFile) {
            cout << "Failed to open output file. Showing results in console instead." << endl;
            printResults(resultStudents, cout);
        } else {
            printResults(resultStudents, outFile);
            cout << "Results saved to " << outFilename << endl;
        }
    } else {
        printResults(resultStudents, cout);
    }
}

void chooseOutputAndPrint(const vector<Student>& students) {
    if (students.empty()) {
        cout << "No students to display." << endl;
        return;
    }

    vector<Student> resultStudents = chooseSorting(students);
    outputResults(resultStudents);
}

int main() {
    srand(time(0));

    vector<Student> students;

    collectStudents(students);
    chooseOutputAndPrint(students);

    return 0;
}

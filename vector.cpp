#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <ctime>
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

Student createStudentManual(bool useMedian) {
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
    
    if (useMedian) {
        student.finalGrade = calculateFinalGradeMedian(student.homeworkGrades, student.examGrade);
    } else {
        student.finalGrade = calculateFinalGradeAverage(student.homeworkGrades, student.examGrade);
    }
    
    return student;
}

Student createStudentRandomGrades(bool useMedian) {
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
    
    if (useMedian) {
        student.finalGrade = calculateFinalGradeMedian(student.homeworkGrades, student.examGrade);
    } else {
        student.finalGrade = calculateFinalGradeAverage(student.homeworkGrades, student.examGrade);
    }
    
    return student;
}

Student createStudentFullyRandom(bool useMedian) {
    Student student = Student();

    student.name = randomName();
    student.surname = randomSurname();
    student.examGrade = randomGrade();

    int homeworkCount = randomGrade(3, 10);
    
    for (int i = 0; i < homeworkCount; i++) {
        student.homeworkGrades.push_back(randomGrade());
    }
    
    if (useMedian) {
        student.finalGrade = calculateFinalGradeMedian(student.homeworkGrades, student.examGrade);
    } else {
        student.finalGrade = calculateFinalGradeAverage(student.homeworkGrades, student.examGrade);
    }
    
    cout << "Generated student: " << student.name << " " << student.surname << endl;
    
    return student;
}

int main() {
    srand(time(0));
    
    char calculationType;
    bool useMedian;
    
    cout << "Use median (m) or average (a) for final grade calculation? ";
    cin >> calculationType;
    useMedian = (calculationType == 'm' || calculationType == 'M');

    vector<Student> students;

    int choice = 0;

    while (choice != 4) {
        cout << "\n=== MENU ===" << endl;
        cout << "1 - Manual input (enter all values)" << endl;
        cout << "2 - Enter name/surname, generate grades" << endl;
        cout << "3 - Generate all data randomly" << endl;
        cout << "4 - Exit and show results" << endl;
        cout << "Choose option: ";
        cin >> choice;
        
        if (choice == 4) break;
        
        if (choice < 1 || choice > 4) {
            cout << "Invalid option. Please try again." << endl;
            continue;
        }
        
        cout << "\n--- Student " << (students.size() + 1) << " ---" << endl;
        
        switch (choice) {
            case 1:
                students.push_back(createStudentManual(useMedian));
                break;
            case 2:
                students.push_back(createStudentRandomGrades(useMedian));
                break;
            case 3:
                students.push_back(createStudentFullyRandom(useMedian));
                break;
        }
    }

    string headerLabel = useMedian ? "Final (Med.)" : "Final (Avg.)";
    
    cout << "\n" << string(52, '=') << endl;
    cout << left << setw(20) << "Name" 
         << setw(20) << "Surname" 
         << headerLabel << endl;
    cout << string(52, '-') << endl;
    
    for (int i = 0; i < students.size(); i++) {
        cout << left << setw(20) << students[i].name 
             << setw(20) << students[i].surname 
             << std::fixed << std::setprecision(2) << students[i].finalGrade << endl;
    }
    cout << string(52, '=') << endl;

    return 0;
}

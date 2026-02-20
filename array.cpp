#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "student-array.h"

using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::left;
using std::string;

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

double calculateFinalGradeAverage(int* homeworkGrades, int count, int examGrade) {
    double homeworkGradeSum = 0;

    for (int i = 0; i < count; i++) {
        homeworkGradeSum += homeworkGrades[i];
    }

    return homeworkGradeSum / count * 0.4 + examGrade * 0.6;
}

double calculateFinalGradeMedian(int* homeworkGrades, int count, int examGrade) {
    int* sortedGrades = new int[count];
    for (int i = 0; i < count; i++) {
        sortedGrades[i] = homeworkGrades[i];
    }
    std::sort(sortedGrades, sortedGrades + count);
    
    double median;
    
    if (count % 2 == 0) {
        median = (sortedGrades[count / 2 - 1] + sortedGrades[count / 2]) / 2.0;
    } else {
        median = sortedGrades[count / 2];
    }
    
    delete[] sortedGrades;
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

    int capacity = 10;
    student.homeworkGrades = new int[capacity];
    student.homeworkCount = 0;
    
    char continueHomework = 'y';
    
    while (continueHomework == 'y' || continueHomework == 'Y') {
        if (student.homeworkCount >= capacity) {
            capacity *= 2;
            int* newArray = new int[capacity];
            for (int i = 0; i < student.homeworkCount; i++) {
                newArray[i] = student.homeworkGrades[i];
            }
            delete[] student.homeworkGrades;
            student.homeworkGrades = newArray;
        }
        
        cout << "Enter homework grade " << (student.homeworkCount + 1) << ": ";
        cin >> student.homeworkGrades[student.homeworkCount];
        student.homeworkCount++;
        
        cout << "Add another homework grade? (y/n): ";
        cin >> continueHomework;
    }
    
    if (useMedian) {
        student.finalGrade = calculateFinalGradeMedian(student.homeworkGrades, student.homeworkCount, student.examGrade);
    } else {
        student.finalGrade = calculateFinalGradeAverage(student.homeworkGrades, student.homeworkCount, student.examGrade);
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
    student.homeworkGrades = new int[homeworkCount];
    student.homeworkCount = homeworkCount;
    
    cout << "Generated " << homeworkCount << " homework grades: ";
    for (int i = 0; i < homeworkCount; i++) {
        student.homeworkGrades[i] = randomGrade();
        cout << student.homeworkGrades[i];
        if (i < homeworkCount - 1) cout << ", ";
    }
    cout << endl;
    
    if (useMedian) {
        student.finalGrade = calculateFinalGradeMedian(student.homeworkGrades, student.homeworkCount, student.examGrade);
    } else {
        student.finalGrade = calculateFinalGradeAverage(student.homeworkGrades, student.homeworkCount, student.examGrade);
    }
    
    return student;
}

Student createStudentFullyRandom(bool useMedian) {
    Student student = Student();

    student.name = randomName();
    student.surname = randomSurname();
    student.examGrade = randomGrade();

    int homeworkCount = randomGrade(3, 10);
    student.homeworkGrades = new int[homeworkCount];
    student.homeworkCount = homeworkCount;
    
    for (int i = 0; i < homeworkCount; i++) {
        student.homeworkGrades[i] = randomGrade();
    }
    
    if (useMedian) {
        student.finalGrade = calculateFinalGradeMedian(student.homeworkGrades, student.homeworkCount, student.examGrade);
    } else {
        student.finalGrade = calculateFinalGradeAverage(student.homeworkGrades, student.homeworkCount, student.examGrade);
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

    int capacity = 10;
    Student* students = new Student[capacity];
    int studentCount = 0;

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
        
        if (studentCount >= capacity) {
            capacity *= 2;
            Student* newArray = new Student[capacity];
            for (int i = 0; i < studentCount; i++) {
                newArray[i] = students[i];
            }
            delete[] students;
            students = newArray;
        }
        
        cout << "\n--- Student " << (studentCount + 1) << " ---" << endl;
        
        switch (choice) {
            case 1:
                students[studentCount] = createStudentManual(useMedian);
                break;
            case 2:
                students[studentCount] = createStudentRandomGrades(useMedian);
                break;
            case 3:
                students[studentCount] = createStudentFullyRandom(useMedian);
                break;
        }
        
        studentCount++;
    }

    string headerLabel = useMedian ? "Final (Med.)" : "Final (Avg.)";
    
    cout << "\n" << string(52, '=') << endl;
    cout << left << setw(20) << "Name" 
         << setw(20) << "Surname" 
         << headerLabel << endl;
    cout << string(52, '-') << endl;
    
    for (int i = 0; i < studentCount; i++) {
        cout << left << setw(20) << students[i].name 
             << setw(20) << students[i].surname 
             << std::fixed << std::setprecision(2) << students[i].finalGrade << endl;
    }
    cout << string(52, '=') << endl;

    for (int i = 0; i < studentCount; i++) {
        delete[] students[i].homeworkGrades;
    }
    delete[] students;

    return 0;
}

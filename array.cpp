#include <iostream>
#include <iomanip>
#include <algorithm>
#include "student-array.h"

using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::left;
using std::string;

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

Student createStudent(bool useMedian) {
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

int main() {
    char calculationType;
    bool useMedian;
    
    cout << "Use median (m) or average (a) for final grade calculation? ";
    cin >> calculationType;
    useMedian = (calculationType == 'm' || calculationType == 'M');

    int capacity = 10;
    Student* students = new Student[capacity];
    int studentCount = 0;

    char continueInput = 'y';

    while (continueInput == 'y' || continueInput == 'Y') {
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
        students[studentCount] = createStudent(useMedian);
        studentCount++;
        
        cout << "\nAdd another student? (y/n): ";
        cin >> continueInput;
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

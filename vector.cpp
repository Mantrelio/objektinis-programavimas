#include <iostream>
#include <iomanip>
#include <algorithm>
#include "student-vector.h"

using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::left;
using std::string;

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

Student createStudent(bool useMedian) {
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

int main() {
    char calculationType;
    bool useMedian;
    
    cout << "Use median (m) or average (a) for final grade calculation? ";
    cin >> calculationType;
    useMedian = (calculationType == 'm' || calculationType == 'M');

    vector<Student> students;

    char continueInput = 'y';
    int studentNumber = 1;

    while (continueInput == 'y' || continueInput == 'Y') {
        cout << "\n--- Student " << studentNumber << " ---" << endl;
        students.push_back(createStudent(useMedian));
        studentNumber++;
        
        cout << "\nAdd another student? (y/n): ";
        cin >> continueInput;
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

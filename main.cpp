#include <iostream>
#include <iomanip>
#include "student.h"

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

Student createStudent() {
    Student student = Student();

    cout << "Enter student name: ";
    cin >> student.name;
    
    cout << "Enter student surname: ";
    cin >> student.surname;
    
    cout << "Enter exam grade: ";
    cin >> student.examGrade;

    int homeworkCount;

    cout << "Enter number of homework grades: ";
    cin >> homeworkCount;
    
    for (int i = 0; i < homeworkCount; i++) {
        cout << "Enter homework grade " << (i + 1) << ": ";
        int grade;
        cin >> grade;
        student.homeworkGrades.push_back(grade);
    }
    
    student.finalGrade = calculateFinalGradeAverage(student.homeworkGrades, student.examGrade);
    
    return student;
}

int main() {
    int studentCount;

    cout << "Enter number of students: ";
    cin >> studentCount;

    vector<Student> students;

    for (int i = 0; i < studentCount; i++) {
        cout << "\n--- Student " << (i + 1) << " ---" << endl;
        students.push_back(createStudent());
    }

    cout << "\n" << string(52, '=') << endl;
    cout << left << setw(20) << "Name" 
         << setw(20) << "Surname" 
         << "Final (Avg.)" << endl;
    cout << string(52, '-') << endl;
    
    for (int i = 0; i < studentCount; i++) {
        cout << left << setw(20) << students[i].name 
             << setw(20) << students[i].surname 
             << std::fixed << std::setprecision(2) << students[i].finalGrade << endl;
    }
    cout << string(52, '=') << endl;

    return 0;
}

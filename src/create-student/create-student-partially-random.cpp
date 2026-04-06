#include "student-vector.h"
#include "input-utils.h"
#include "student-grading.h"

using std::cout;
using std::endl;

Student createStudentRandomGrades() {
    Student student = Student();

    student.name = readSingleStringToken("Enter student name: ");
    
    student.surname = readSingleStringToken("Enter student surname: ");
    
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
#include "student-vector.h"
#include "input-utils.h"
#include "student-grading.h"

using std::cout;
using std::endl;

Student createStudentRandomGrades() {
    Student student = Student();

    student.name = readSingleStringToken("Suveskite studento vardą: ");
    
    student.surname = readSingleStringToken("Suveskite studento pavardę: ");
    
    student.examGrade = randomGrade();
    cout << "Sugeneruotas egzamino pažymys: " << student.examGrade << endl;

    int homeworkCount = randomGrade(3, 10);
    
    cout << "Sugeneruoti " << homeworkCount << " namu darbo pažymiai: ";
    for (int i = 0; i < homeworkCount; i++) {
        int grade = randomGrade();
        student.homeworkGrades.push_back(grade);
        cout << grade;
        if (i < homeworkCount - 1) cout << ", ";
    }
    cout << endl;
    
    return student;
}
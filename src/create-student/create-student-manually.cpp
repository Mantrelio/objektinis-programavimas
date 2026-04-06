#include "student-vector.h"
#include "input-utils.h"

using std::cout;
using std::endl;

Student createStudentManual() {
    Student student = Student();

    student.name = readSingleStringToken("Enter student name: ");
    
    student.surname = readSingleStringToken("Enter student surname: ");
    
    student.examGrade = readIntInRange("Enter student exam grade: ", 1, 10);

    char continueHomework = 'Y';
    int homeworkNumber = 1;
    
    while (continueHomework == 'Y') {
        int grade = readIntInRange("Enter homework grade: ", 1, 10);
        student.homeworkGrades.push_back(grade);
        homeworkNumber++;
        
        continueHomework = readYesOrNo("Add another homework grade? (y/n): ");
    }
    
    return student;
}
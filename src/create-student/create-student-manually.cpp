#include "student-vector.h"
#include "input-utils.h"

using std::cout;
using std::endl;

Student createStudentManual() {
    Student student = Student();

    student.name = readSingleStringToken("Suveskite studento vardą: ");
    student.surname = readSingleStringToken("Suveskite studento pavard: ");
    student.examGrade = readIntInRange("Suveskite egzamino pažymį: ", 1, 10);

    char continueHomework = 'Y';
    int homeworkNumber = 1;
    
    while (continueHomework == 'Y') {
        int grade = readIntInRange("Suveskite namu darbo pažymį: ", 1, 10);
        student.homeworkGrades.push_back(grade);
        homeworkNumber++;
        
        continueHomework = readYesOrNo("Pridėti dar vieną namu darbo pažymį? (y/n): ");
    }
    
    return student;
}
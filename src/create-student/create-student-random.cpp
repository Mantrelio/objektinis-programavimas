#include "student-vector.h"
#include "student-grading.h"

using std::cout;
using std::endl;

string randomName() {
    const string names[] = {"Jonas", "Petras", "Antanas", "Marija", "Ona", "Jurate", "Tomas", "Mindaugas", "Ruta", "Greta"};
    return names[rand() % 10];
}

string randomSurname() {
    const string surnames[] = {"Jonaitis", "Petraitis", "Antanaitis", "Kazlauskas", "Zukauskas", "Jankauskas", "Paulauskas", "Stankevicius", "Vasiliauskas", "Baranauskas"};
    return surnames[rand() % 10];
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
#include <cstdlib>
#include <ctime>

#include "student-app.h"

int main() {
    srand(time(0));

    vector<Student> students;

    collectStudents(students);
    chooseOutputAndPrint(students);

    return 0;
}

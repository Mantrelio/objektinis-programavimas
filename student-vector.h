#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::left;

struct Student {
    string name, surname;
    vector<int> homeworkGrades;
    int examGrade;
    float finalGrade;
};

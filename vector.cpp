#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include "student-vector.h"
#include <limits>

int randomGrade(int min = 1, int max = 10) {
    return rand() % (max - min + 1) + min;
}

string randomName() {
    const string names[] = {"Jonas", "Petras", "Antanas", "Marija", "Ona", "Jurate", "Tomas", "Mindaugas", "Ruta", "Greta"};
    return names[rand() % 10];
}

string randomSurname() {
    const string surnames[] = {"Jonaitis", "Petraitis", "Antanaitis", "Kazlauskas", "Zukauskas", "Jankauskas", "Paulauskas", "Stankevicius", "Vasiliauskas", "Baranauskas"};
    return surnames[rand() % 10];
}

int readIntInRange(const string& prompt, int min, int max) {
    string line;
    int value;
    while (true) {
        cout << prompt;
        std::getline(cin >> std::ws, line);

        std::istringstream iss(line);

        if(!(iss >> value) || (iss >> std::ws && !iss.eof())) {
            cout << "Please enter a single valid integer." << endl;
            continue;
        }

        if (value < min || value > max) {
            cout << "Value must be between " << min << " and " << max << "\n";
            continue;
        }

        return value;
    }
}

string readSingleStringToken(const string& prompt) {
    string line;
    string value;

    while (true) {
        cout << prompt;
        std::getline(cin >> std::ws, line);

        std::istringstream iss(line);

        if (!(iss >> value)) {
            cout << "Please enter a value." << endl;
        }

        if (iss >> std::ws && !iss.eof()) {
            cout << "Please enter only one word." << endl;
            continue;
        }

        return value;
    }
}

char readYesOrNo(const string& prompt) {
    string line;
    char answer;
    string extra;

    while (true) {
        cout << prompt;
        std::getline(cin >> std::ws, line);

        std::istringstream iss(line);
        if (!(iss >> answer) || (iss >> extra)) {
            cout << "Please enter only y or n" << endl;
            continue;
        }

        char answerToUpper = toupper(answer);
        if (answerToUpper == 'Y' || answer == 'N' ) {
            return answerToUpper;
        }
    }
}

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

void printResults(const vector<Student>& students, std::ostream& out) {
    out << "\n" << string(70, '=') << endl;
    out << left  << setw(20) << "Name" 
        << left  << setw(20) << "Surname" 
        << right << setw(15) << "Final (Avg.)"
        << right << setw(15) << "Final (Med.)" << endl;
    out << string(70, '-') << endl;
    
    for (int i = 0; i < students.size(); i++) {
        double finalAvg = calculateFinalGradeAverage(students[i].homeworkGrades, students[i].examGrade);
        double finalMed = calculateFinalGradeMedian(students[i].homeworkGrades, students[i].examGrade);

        out << left  << setw(20) << students[i].name 
            << left  << setw(20) << students[i].surname 
            << right << std::fixed << std::setprecision(2) << setw(15) << finalAvg
            << right << std::fixed << std::setprecision(2) << setw(15) << finalMed << endl;
    }
    out << string(70, '=') << endl;
}

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

bool parseStudentLine(const std::string& line, Student& out, std::string& error) {
    std::istringstream iss(line);
    string name, surname;

    if (!(iss >> name >> surname)) {
        error = "missing name/surname";
        return false;
    }

    vector<int> grades;
    string token;
    
    while (iss >> token) {
        std::istringstream ts(token);
        int grade;

        if (!(ts >> grade) || !ts.eof()) {
            error = "non-integer grade token: " + token;
            return false;
        }

        if (grade < 1 || grade > 10) {
            error = "grade out of [1;10] range";
            return false;
        }

        grades.push_back(grade);
    }

    if (grades.size() < 2) {
        error = "need at least 1 homework + 1 exam grade";
        return false;
    }

    out.name = name;
    out.surname = surname;
    out.examGrade = grades.back();
    grades.pop_back();
    out.homeworkGrades = std::move(grades);
    return true;
}

vector<Student> createStudentsFromFile(const string& filename) {
    vector<Student> studentsFromFile;
    std::ifstream in(filename);

    if (!in) {
        cout << "Failed to open file: " << filename << endl;
        return studentsFromFile;
    }

    string headerLine;
    std::getline(in, headerLine);

    string line;
    int lineNumber = 1;

    while(std::getline(in, line)) {
        ++lineNumber;

        if (line.empty()) {
            continue;
        }

        Student student;
        std::string error;

        if (parseStudentLine(line, student, error)) {
            studentsFromFile.push_back(std::move(student));
        } else {
            cout << "Skipping line " << lineNumber << ": " << error << endl;
        }
    }

    return studentsFromFile;
}

void showMainMenu() {
    cout << "\n=== MENU ===" << endl;
    cout << "1 - Manual input (enter all values)" << endl;
    cout << "2 - Enter name/surname, generate grades" << endl;
    cout << "3 - Generate all data randomly" << endl;
    cout << "4 - Read students from file" << endl;
    cout << "5 - Exit and show results" << endl;
    cout << "Choose option: ";
}

void handleMenuChoice(int choice, vector<Student>& students) {
    switch (choice) {
        case 1:
            cout << "\n--- Student " << (students.size() + 1) << " ---" << endl;
            students.push_back(createStudentManual());
            break;
        case 2:
            cout << "\n--- Student " << (students.size() + 1) << " ---" << endl;
            students.push_back(createStudentRandomGrades());
            break;
        case 3:
            cout << "\n--- Student " << (students.size() + 1) << " ---" << endl;
            students.push_back(createStudentFullyRandom());
            break;
        case 4: {
            string filename;
            cout << "Enter file name (e.g. data.txt): ";
            cin >> filename;
            vector<Student> fileStudents = createStudentsFromFile(filename);
            cout << "Loaded " << fileStudents.size() << " students from file." << endl;
            students.insert(students.end(), fileStudents.begin(), fileStudents.end());
            break;
        }
    }
}

void collectStudents(vector<Student>& students) {
    int choice;

    while (true) {
        showMainMenu();
        choice = readIntInRange("Choice: ", 1, 5);
        
        if (choice == 5) break;
        
        handleMenuChoice(choice, students);
    }
}

vector<Student> chooseSorting(const vector<Student>& students) {
    int sortChoice;
    cout << "\nChoose sorting option:" << endl;
    cout << "0 - Unsorted (original order)" << endl;
    cout << "1 - By name" << endl;
    cout << "2 - By surname" << endl;
    cout << "3 - By final average" << endl;
    cout << "4 - By final median" << endl;
    sortChoice = readIntInRange("Choice: ", 0, 4);

    vector<Student> resultStudents = students;

    if (sortChoice == 0) {
        cout << "Showing unsorted results (original order)." << endl;
        return resultStudents;
    }

    cout << "\nChoose sorting order:" << endl;
    cout << "1 - Ascending" << endl;
    cout << "2 - Descending" << endl;
    int orderChoice = readIntInRange("Choice: ", 1, 2);
    bool ascending = (orderChoice == 1);

    auto lessByChoice = [sortChoice](const Student& a, const Student& b) {
        switch (sortChoice) {
            case 1:
                if (a.name == b.name) return a.surname < b.surname;
                return a.name < b.name;
            case 2:
                if (a.surname == b.surname) return a.name < b.name;
                return a.surname < b.surname;
            case 3: {
                double fa = calculateFinalGradeAverage(a.homeworkGrades, a.examGrade);
                double fb = calculateFinalGradeAverage(b.homeworkGrades, b.examGrade);
                return fa < fb;
            }
            case 4: {
                double fa = calculateFinalGradeMedian(a.homeworkGrades, a.examGrade);
                double fb = calculateFinalGradeMedian(b.homeworkGrades, b.examGrade);
                return fa < fb;
            }
            default:
                return a.name < b.name;
        }
    };

    if (ascending) {
        std::sort(resultStudents.begin(), resultStudents.end(), lessByChoice);
    } else {
        std::sort(resultStudents.begin(), resultStudents.end(),
            [&lessByChoice](const Student& a, const Student& b) {
                return lessByChoice(b, a);
            }
        );
    }

    return resultStudents;
}

void outputResults(const vector<Student>& students) {
    const vector<Student>& resultStudents = students;

    int outputChoice;
    cout << "\nChoose output method:" << endl;
    cout << "1 - Show results in console" << endl;
    cout << "2 - Save results to text file" << endl;
    cout << "Choice: ";
    outputChoice = readIntInRange("Choice: ", 1, 2);

    if (outputChoice == 2) {
        string outFilename;
        cout << "Enter output filename (e.g. results.txt): ";
        cin >> outFilename;

        std::ofstream outFile(outFilename);
        if (!outFile) {
            cout << "Failed to open output file. Showing results in console instead." << endl;
            printResults(resultStudents, cout);
        } else {
            printResults(resultStudents, outFile);
            cout << "Results saved to " << outFilename << endl;
        }
    } else {
        printResults(resultStudents, cout);
    }
}

void chooseOutputAndPrint(const vector<Student>& students) {
    if (students.empty()) {
        cout << "No students to display." << endl;
        return;
    }

    vector<Student> resultStudents = chooseSorting(students);
    outputResults(resultStudents);
}

int main() {
    srand(time(0));

    vector<Student> students;

    collectStudents(students);
    chooseOutputAndPrint(students);

    return 0;
}

#include "sort-nuskriausti-and-protingi.h"

#include <algorithm>
#include <deque>
#include <list>
#include <type_traits>

template <typename T>
std::pair<T, T> sortNuskriaustiAndProtingiFirstStrategy(const T& students) {
	T nuskriausti;
	T protingi;

	for (const Student& student : students) {
		if (calculateFinalGradeAverage(student.homeworkGrades, student.examGrade) >= 5) {
			protingi.push_back(student);
		} else {
			nuskriausti.push_back(student);
		}
	}

	return {nuskriausti, protingi};
}

template std::pair<vector<Student>, vector<Student>> sortNuskriaustiAndProtingiFirstStrategy(const vector<Student>&);
template std::pair<std::list<Student>, std::list<Student>> sortNuskriaustiAndProtingiFirstStrategy(const std::list<Student>&);
template std::pair<std::deque<Student>, std::deque<Student>> sortNuskriaustiAndProtingiFirstStrategy(const std::deque<Student>&);

template <typename T>
T sortNuskriaustiAndProtingiSecondStrategy(T& students) {
	T nuskriausti;
    for (auto it = students.begin(); it != students.end()) {
        if (calculateFinalGradeAverage(*it.homeworkGrades, *it.examGrade) >= 5) {
            nuskriausti.push_back(*it);
            it = students.erase(it);
        } else {
            ++it;
        }
    }
        
	return nuskriausti;
}

template vector<Student> sortNuskriaustiAndProtingiSecondStrategy(vector<Student>&);
template std::list<Student> sortNuskriaustiAndProtingiSecondStrategy(std::list<Student>&);
template std::deque<Student> sortNuskriaustiAndProtingiSecondStrategy(std::deque<Student>&);
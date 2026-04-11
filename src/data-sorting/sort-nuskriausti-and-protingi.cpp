#include "sort-nuskriausti-and-protingi.h"

#include <deque>
#include <list>

template std::pair<vector<Student>, vector<Student>> sortNuskriaustiAndProtingi(const vector<Student>&);
template std::pair<std::list<Student>, std::list<Student>> sortNuskriaustiAndProtingi(const std::list<Student>&);
template std::pair<std::deque<Student>, std::deque<Student>> sortNuskriaustiAndProtingi(const std::deque<Student>&);
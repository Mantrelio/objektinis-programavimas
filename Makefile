CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude
TARGET = student-vector
SOURCES = src/main.cpp src/grading/student-grading.cpp \
	src/main-menu/student-menu.cpp src/utils/input-utils.cpp \
	src/student-data-generation/generate-student-list.cpp \
	src/test/generate-student-list-test.cpp \
	src/test/output-nuskriausti-and-protingi-test.cpp \
	src/data-sorting/sort-students.cpp \
	src/data-sorting/sort-nuskriausti-and-protingi.cpp \
	src/output/output-nuskriausti-and-protingi.cpp \
	src/output/output-results.cpp \
	src/create-student/create-student-manually.cpp src/create-student/create-student-partially-random.cpp \
	src/create-student/create-student-random.cpp src/create-student/create-student-from-file.cpp
OBJECTS = $(SOURCES:.cpp=.o)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)

.PHONY: clean

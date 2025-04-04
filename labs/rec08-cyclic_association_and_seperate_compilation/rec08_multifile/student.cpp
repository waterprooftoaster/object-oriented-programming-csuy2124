#include "student.h"
#include "course.h"
#include <iostream>
using namespace std;

Student::Student(const string& name) : name(name) {}

const string& Student::getName() const {
    return name;
}

const vector<Course*>& Student::getCourses() const {
    return courses;
}

bool Student::addCourse(Course* new_course) {
    courses.push_back(new_course);
    return true;
}

void Student::removedFromCourse(Course* course) {
    for (size_t i = 0; i < courses.size(); i++) {
        if (course == courses[i]) {
            courses.erase(courses.begin() + i);
            break;
        }
    }
}

Student::~Student() {
    courses.clear();
}

ostream& operator<<(ostream& os, const Student& rhs) {
    os << rhs.name << ": ";
    if (rhs.courses.empty()) {
        os << "no courses" << endl;
        return os;
    }
    for (const Course* course : rhs.courses) {
        os << course->getName() << " ";
    }
    return os;
}

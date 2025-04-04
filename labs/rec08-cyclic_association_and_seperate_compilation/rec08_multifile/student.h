#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Course;  // Forward declaration

class Student {
    friend ostream& operator<<(ostream& os, const Student& rhs);
public:
    explicit Student(const string& name);
    const string& getName() const;
    const vector<Course*>& getCourses() const;
    bool addCourse(Course* new_course);
    void removedFromCourse(Course* course);
    ~Student();

private:
    string name;
    vector<Course*> courses;
};

#endif

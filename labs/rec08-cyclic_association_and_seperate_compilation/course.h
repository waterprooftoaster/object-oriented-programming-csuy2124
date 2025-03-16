#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Student;  // Forward declaration

class Course {
    friend ostream& operator<<(ostream& os, const Course& rhs);
public:
    explicit Course(const string& courseName);
    const string& getName() const;
    bool addStudent(Student* new_student);
    void removeStudentsFromCourse(Student* student);
    ~Course();

private:
    string name;
    vector<Student*> students;
};

#endif

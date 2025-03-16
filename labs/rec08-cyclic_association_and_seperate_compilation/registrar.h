#ifndef REGISTRAR_H
#define REGISTRAR_H

#include <string>
#include <vector>
#include "course.h"
#include "student.h"
#include <iostream>
using namespace std;

class Registrar {
    friend ostream& operator<<(ostream& os, const Registrar& rhs);
public:
    Registrar();
    bool addCourse(const string& course_name);
    bool addStudent(const string& student_name);
    bool enrollStudentInCourse(const string& studentName, const string& courseName) const;
    bool cancelCourse(const string& courseName);
    void purge();

private:
    // (Optional helper functions; these are declared but not used in main.)
    size_t findStudent(const string&) const;
    size_t findCourse(const string&) const;

    vector<Course*> courses;
    vector<Student*> students;
};

#endif

/*
  rec08_start.cpp
  Starter Code for required functionality

  Yes, of course, you may add other methods.

  And no, this won't compile. You have to fix the cyclic association
  and implement the methods.

 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Course
{
    friend ostream &operator<<(ostream &os, const Course &rhs);

public:
    // Course methods needed by Registrar
    Course(const string &courseName);
    const string &getName() const;
    bool addStudent(Student *);

    // Tell the students that they are no longer in the course
    void removeStudentsFromCourse();

private:
    string name;
    vector<Student *> students;
}; // Course

class Student
{
    friend ostream &operator<<(ostream &os, const Student &rhs);

public:
    // Student methods needed by Registrar
    Student(const string &name);
    const string &getName() const;
    bool addCourse(Course *);

    // Student method needed by Course::removeStudentsFromCourse
    void removedFromCourse(Course *);

private:
    string name;
    vector<Course *> courses;
}; // Student

class Registrar
{
    friend ostream &operator<<(ostream &os, const Registrar &rhs);

public:
    Registrar();

    // Creates a new course, if none with that name
    bool addCourse(const string &);
    // Creates a new student, if none with that name
    bool addStudent(const string &);

    // If the student and the course exist, then enroll the student.
    bool enrollStudentInCourse(const string &studentName,
                               const string &courseName);

    // Unenroll the students from the course and remove the course
    // from the Registrar.
    bool cancelCourse(const string &courseName);

    // Get rid of everything!!!
    void purge();

private:
    size_t findStudent(const string &) const;
    size_t findCourse(const string &) const;

    vector<Course *> courses;
    vector<Student *> students;
}; // Registrar

int main()
{

    Registrar registrar;

    cout << "No courses or students added yet\n";
    cout << registrar << endl;

    cout << "AddCourse CS101.001\n";
    registrar.addCourse("CS101.001");
    cout << registrar << endl;

    cout << "AddStudent FritzTheCat\n";
    registrar.addStudent("FritzTheCat");
    cout << registrar << endl;

    cout << "AddCourse CS102.001\n";
    registrar.addCourse("CS102.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse FritzTheCat CS102.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS102.001");
    cout << "EnrollStudentInCourse FritzTheCat CS101.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS101.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse Bullwinkle CS101.001\n";
    cout << "Should fail, i.e. do nothing, "
         << "since Bullwinkle is not a student.\n";
    registrar.enrollStudentInCourse("Bullwinkle", "CS101.001");
    cout << registrar << endl;

    cout << "CancelCourse CS102.001\n";
    registrar.cancelCourse("CS102.001");
    cout << registrar << endl;

    cout << "Purge for start of next semester\n";
    registrar.purge();
    cout << registrar << endl;
} // main

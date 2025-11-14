#include "registrar.h"
#include "student.h"
#include "course.h"
#include <iostream>
using namespace std;
// using namespace BrooklynPoly;

namespace BrooklynPoly
{
  Registrar::Registrar() = default;
  bool Registrar::addCourse(const string &course_name)
  {
    for (Course *course : courses)
    {
      if (course->getName() == course_name)
      {
        cout << "Course " << course_name << " already exists" << endl;
        return false;
      }
    }
    courses.push_back(new Course(course_name));
    return true;
  }
  bool Registrar::addStudent(const string &student_name)
  {
    // Note: This replicates the behavior in the single-file version.
    for (Course *course : courses)
    {
      if (course->getName() == student_name)
      {
        cout << "Course " << student_name << " already exists" << endl;
        return false;
      }
    }
    students.push_back(new Student(student_name));
    return true;
  }
  bool Registrar::enrollStudentInCourse(const string &studentName,
                                        const string &courseName) const
  {
    size_t course_index = -1;
    size_t student_index = -1;
    for (size_t i = 0; i < courses.size(); i++)
    {
      if (courses[i]->getName() == courseName)
      {
        course_index = i;
        break;
      }
    }
    for (size_t j = 0; j < students.size(); j++)
    {
      if (students[j]->getName() == studentName)
      {
        student_index = j;
        break;
      }
    }
    if (course_index == -1 || student_index == -1)
    {
      cout << "could not find student or course to enroll" << endl;
      return false;
    }

    courses[course_index]->addStudent(students[student_index]);
    students[student_index]->addCourse(courses[course_index]);
    return true;
  }
  bool Registrar::cancelCourse(const string &courseName)
  {
    Course *courseToCancel = nullptr;
    for (size_t i = 0; i < courses.size(); i++)
    {
      if (courses[i]->getName() == courseName)
      {
        courseToCancel = courses[i];
        courses.erase(courses.begin() + i);
        break;
      }
    }
    if (courseToCancel == nullptr)
      return false;

    for (Student *student : students)
    {
      student->removedFromCourse(courseToCancel);
    }
    delete courseToCancel;
    return true;
  }
  void Registrar::purge()
  {
    for (Course *course : courses)
    {
      delete course;
    }
    for (Student *student : students)
    {
      delete student;
    }
    courses.clear();
    students.clear();
  }
  // (Optional) Implementations for the helper functions
  size_t Registrar::findStudent(const string &name) const
  {
    for (size_t i = 0; i < students.size(); i++)
    {
      if (students[i]->getName() == name)
        return i;
    }
    return students.size(); // indicates not found
  }
  size_t Registrar::findCourse(const string &name) const
  {
    for (size_t i = 0; i < courses.size(); i++)
    {
      if (courses[i]->getName() == name)
        return i;
    }
    return courses.size(); // indicates not found
  }
  ostream &operator<<(ostream &os, const Registrar &rhs)
  {
    os << "Registrar's Report\n"
       << "Courses: " << endl;
    for (const Course *course : rhs.courses)
    {
      os << *course << endl;
    }
    os << "Students: " << endl;
    for (const Student *student : rhs.students)
    {
      os << *student << endl;
    }
    return os;
  }
}
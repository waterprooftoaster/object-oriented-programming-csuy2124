#include "course.h"
#include "student.h"
#include <iostream>
using namespace std;
// using namespace BrooklynPoly;

namespace BrooklynPoly
{
  Course::Course(const string &courseName) : name(courseName) {}
  const string &Course::getName() const
  {
    return name;
  }
  bool Course::addStudent(Student *new_student)
  {
    students.push_back(new_student);
    return true;
  }
  void Course::removeStudentsFromCourse(Student *student)
  {
    for (size_t i = 0; i < students.size(); i++)
    {
      if (student == students[i])
      {
        students.erase(students.begin() + i);
        break;
      }
    }
  }

  ostream &operator<<(ostream &os, const Course &rhs)
  {
    os << rhs.name << ": ";
    if (rhs.students.empty())
    {
      os << "no students" << endl;
      return os;
    }
    for (const Student *student : rhs.students)
    {
      os << student->getName() << " ";
    }
    return os;
  }
}

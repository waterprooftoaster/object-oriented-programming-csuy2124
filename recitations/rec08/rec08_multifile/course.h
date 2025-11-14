#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <vector>
#include <iostream>

namespace BrooklynPoly
{
  class Student; // Forward declaration
  // ostream &operator<<(ostream &os, const Course &rhs);

  class Course
  {
    friend std::ostream &operator<<(std::ostream &os, const Course &rhs);

  public:
    Course(const std::string &courseName);
    const std::string &getName() const;
    bool addStudent(Student *new_student);
    void removeStudentsFromCourse(Student *student);

  private:
    std::string name;
    std::vector<Student *> students;
  };
}
#endif

#ifndef REGISTRAR_H
#define REGISTRAR_H

#include <string>
#include <vector>
#include <iostream>

namespace BrooklynPoly
{
  class Course;
  class Student;

  // ostream &operator<<(ostream &os, const Registrar &rhs);
  class Registrar
  {
    friend std::ostream &operator<<(std::ostream &os, const Registrar &rhs);

  public:
    Registrar();
    bool addCourse(const std::string &course_name);
    bool addStudent(const std::string &student_name);
    bool enrollStudentInCourse(const std::string &studentName, const std::string &courseName) const;
    bool cancelCourse(const std::string &courseName);
    void purge();

  private:
    // (Optional helper functions; these are declared but not used in main.)
    size_t findStudent(const std::string &) const;
    size_t findCourse(const std::string &) const;

    std::vector<Course *> courses;
    std::vector<Student *> students;
  };
}
#endif

#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include <iostream>


namespace BrooklynPoly
{
  class Course; // Forward declaration

  class Student
  {
    friend std::ostream &operator<<(std::ostream &os, const Student &rhs);

  public:
    explicit Student(const std::string &name);
    const std::string &getName() const;
    const std::vector<Course *> &getCourses() const;
    bool addCourse(Course *new_course);
    void removedFromCourse(Course *course);

  private:
    std::string name;
    std::vector<Course *> courses;
  };
}
#endif

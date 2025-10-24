/*
  rec08_start.cpp
  Starter Code for required functionality

  Yes, of course, you may add other methods.

  And no, this won't compile. You have to fix the cyclic association
  and implement the methods.

 */

#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

class Course;
class Student;
class Registrar;

class Course
{
  friend ostream &operator<<(ostream &os, const Course &rhs);
  friend ostream &operator<<(ostream &os, const Registrar &rhs);
  friend ostream &operator<<(ostream &os, const Student &rhs);

public:
  // Course methods needed by Registrar
  explicit Course(const string &courseName) : name(courseName) {};

  void removeStudentsFromCourse(Student *student);
  const string &getName() const;
  bool addStudent(Student *new_student);

  const string &getName() const
  {
    return name;
  }

  bool addStudent(Student *new_student)
  {
    students.push_back(new_student);
    return true;
  }

  // Tell the students that they are no longer in the course
  void removeStudentsFromCourse(Student *student)
  {
    for (size_t i = 0; i < students.size(); i++)
    {
      if (student == students[i])
      {
        students[i] = nullptr;
        students.erase(students.begin() + i);
      }
    }
  }

  ~Course()
  {
    students.clear();
  }

private:
  string name;
  vector<Student *> students;
}; // Course

class Student
{
  friend ostream &operator<<(ostream &os, const Course &rhs);
  friend ostream &operator<<(ostream &os, const Registrar &rhs);
  friend ostream &operator<<(ostream &os, const Student &rhs);

public:
  // Student methods needed by Registrar
  explicit Student(const string &name) : name(name) {}

  const string &getName() const;
  const vector<Course *> &getCourses() const;
  bool addCourse(Course *new_course);
  void removedFromCourse(Course *course);

  const string &getName() const
  {
    return name;
  }

  const vector<Course *> &getCourses() const
  {
    return courses;
  }

  bool addCourse(Course *new_course)
  {
    courses.push_back(new_course);
    return true;
  }

  // Student method needed by Course::removeStudentsFromCourse
  void removedFromCourse(Course *course)
  {
    for (size_t i = 0; i < courses.size(); i++)
    {
      if (course == courses[i])
      {
        courses[i] = nullptr;
        courses.erase(courses.begin() + i);
      }
    }
  }

  ~Student()
  {
    courses.clear();
  }

private:
  string name;
  vector<Course *> courses;
}; // Student

class Registrar
{
  friend ostream &operator<<(ostream &os, const Course &rhs);
  friend ostream &operator<<(ostream &os, const Registrar &rhs);
  friend ostream &operator<<(ostream &os, const Student &rhs);

public:
  Registrar() = default;

  bool addCourse(const string &course_name);
  bool addStudent(const string &student_name);
  bool enrollStudentInCourse(const string &studentName,
                             const string &courseName) const;
  bool cancelCourse(const string &courseName);
  void purge();

  // Creates a new course, if none with that name
  bool addCourse(const string &course_name)
  {
    for (const Course *course : courses)
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

  // Creates a new student, if none with that name
  bool addStudent(const string &student_name)
  {
    for (const Course *course : courses)
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

  // If the student and the course exist, then enroll the student.
  bool enrollStudentInCourse(const string &studentName,
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
      cout << "could not find student or course to enroll"
           << endl;
      return false;
    }

    courses[course_index]->addStudent(students[student_index]);
    students[student_index]->addCourse(courses[course_index]);
    return true;
  }

  // Unenroll the students from the course and remove the course
  // from the Registrar.
  bool cancelCourse(const string &courseName)
  {
    Course *courseToCancel = nullptr;
    // Find the course and remove it from the courses vector.
    for (size_t i = 0; i < courses.size(); i++)
    {
      if (courses[i]->getName() == courseName)
      {
        courseToCancel = courses[i];
        // delete courses[i];
        courses[i] = courses[courses.size() - 1];
        courses.pop_back();
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

  // Get rid of everything!!!
  void purge()
  {
    for (Course *course : courses)
    {
      delete course;
      course = nullptr;
    }

    for (Student *student : students)
    {
      delete student;
      student = nullptr;
    }

    courses.clear();
    students.clear();
  }

private:
  size_t findStudent(const string &) const;
  size_t findCourse(const string &) const;

  vector<Course *> courses;
  vector<Student *> students;
}; // Registrar

ostream &operator<<(ostream &os, const Registrar &rhs);
ostream &operator<<(ostream &os, const Course &rhs);
ostream &operator<<(ostream &os, const Student &rhs);

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
    os << student->name << " ";
  }
  return os;
}

ostream &operator<<(ostream &os, const Student &rhs)
{
  os << rhs.name << ": ";
  if (rhs.courses.empty())
  {
    os << "no courses" << endl;
    return os;
  }

  for (const Course *course : rhs.courses)
  {
    os << course->name << " ";
  }
  return os;
}
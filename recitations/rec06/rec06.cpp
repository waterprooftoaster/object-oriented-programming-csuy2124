/*
    Andy Wu
    cw4483
    rec06_start.cpp
    CS2124
    Focus: Dynamic arrays and copy control
 */

#include <string>
#include <iostream>
using namespace std;

//
// Position class
//
class Position
{
  friend ostream &operator<<(ostream &os, const Position &rhs)
  {
    os << '[' << rhs.title << ',' << rhs.salary << ']';
    return os;
  } // Position op<<

public:
  // constructor
  Position(const string &aTitle, double aSalary)
      : title(aTitle), salary(aSalary) {}

  // methods
  const string &getTitle() const { return title; }
  double getSalary() const { return salary; }
  void changeSalaryTo(double d) { salary = d; }

private:
  string title;
  double salary;
}; // class Position

//
// Directory class
//
class Directory
{
  //
  // nested Entry class
  //
  class Entry
  {
    friend ostream &operator<<(ostream &os, const Entry &rhs)
    {
      os << rhs.name << ' ' << rhs.room
         << ' ' << rhs.phone << ", " << *rhs.pos;
      return os;
    } // Entry op<<

  public:
    // If position is passed as constant reference, the the field
    // would need to be pointer to const.
    Entry(const string &name, unsigned room, unsigned phone,
          Position &position)
        : name(name), room(room), phone(phone), pos(&position) {}

    const string &getName() const { return name; }
    unsigned getPhone() const { return phone; }

  private:
    string name;
    unsigned room;
    unsigned phone;
    Position *pos;
  }; // class Entry

  // Overload Directory's output operator
  // ...
  friend ostream &operator<<(ostream &os, const Directory &rhs)
  {
    for (size_t i = 0; i < rhs.size; i++)
    {
      os << *rhs.entries[i] << endl;
    }
    return os;
  }

public:
  // Of course the first function you need to write for this (or
  // any) class is...
  // constructor
  Directory(const string &company_name) : company(company_name), entries(nullptr) {}

  // We'll get you started with the add method, but obviously you
  // have a lot of work to do here.
  void add(const string &name, unsigned room, unsigned ph, Position &pos)
  {
    if (size == capacity)
    {
      // something is missing!!!  Add it!Directory(): size(0), capacity(8),entries(new Entry*[capacity]) {}
      Entry **old_entries = entries; // keep existing data
      if (capacity == 0)
      {
        capacity = 1;
      }
      entries = new Entry *[2 * capacity];
      for (size_t i = 0; i < size; i++)
      {
        entries[i] = old_entries[i]; // copy over data
      }
      delete[] old_entries;
      capacity *= 2;
    } // if
    entries[size] = new Entry(name, room, ph, pos);
    ++size;
  } // add

  //
  // === Copy Control ===
  //
  // (get checked out on everything else before starting this)

  // copy constructor
  Directory(const Directory &rhs) : size(rhs.size), capacity(rhs.capacity), entries(new Entry *[rhs.capacity]), company(rhs.company)
  {
    cout << "Copy Constructor..." << endl;
    for (size_t i = 0; i < size; i++)
    {
      entries[i] = new Entry(*rhs.entries[i]);
    }
  }

  // assignment operator (deep copy)
  Directory &operator=(const Directory &rhs)
  {
    if (this != &rhs)
    {
      // free existing entries
      for (size_t i = 0; i < size; ++i)
      {
        delete entries[i];
      }
      delete[] entries;

      // copy simple fields
      size = rhs.size;
      capacity = rhs.capacity;
      company = rhs.company;

      // allocate and copy entries if needed
      if (capacity > 0)
      {
        entries = new Entry *[capacity];
        for (size_t i = 0; i < size; ++i)
        {
          entries[i] = new Entry(*rhs.entries[i]);
        }
      }
      else
      {
        entries = nullptr;
      }
    }
    return *this;
  }

  // destructor
  ~Directory()
  {
    cout << "Destructor..." << endl;
    // free up space on heap
    for (size_t i = 0; i < size; i++)
    {
      delete entries[i];
    }
    delete[] entries;
  }

  unsigned operator[](string name) const
  {
    for (size_t i = 0; i < size; i++)
    {
      if (entries[i]->getName() == name)
      {
        return entries[i]->getPhone();
      }
    }
    return 9999999;
  }

private:
  Entry **entries; // Notice the type!!! Pointer to Entry pointers.
  size_t size = 0;
  size_t capacity = 0;
  string company;
}; // class Directory

void doNothing(Directory dir)
{
  // You need to overload the Directory output operator before
  // uncommenting the next line.
  cout << dir << endl;
} // doNothing

int main()
{

  // Note that the Postion objects are NOT on the heap.
  Position boss("Boss", 3141.59);
  Position pointyHair("Pointy Hair", 271.83);
  Position techie("Techie", 14142.13);
  Position peon("Peonissimo", 34.79);

  // Create a Directory
  Directory d("HAL");
  // Add someone
  d.add("Marilyn", 123, 4567, boss);
  // print the directory
  cout << d << endl;
  // Use the square bracket operator, aka the Index operator,
  // to access someone's phone extension.
  cout << "d[\"Marilyn\"]: " << d["Marilyn"] << endl;
  cout << "======\n\n";

  // Everything working so far? Get checked out!!!

  Directory d2 = d; // What function is being used??
  d2.add("Gallagher", 111, 2222, techie);
  d2.add("Carmack", 314, 1592, techie);
  cout << "Directory d:\n"
       << d << endl;
  cout << "Directory d2:\n"
       << d2 << endl;

  cout << "Calling doNothing\n";
  doNothing(d2);
  cout << "Back from doNothing\n";

  // Should display 1592
  cout << d2["Carmack"] << endl;

  Directory d3("IBM");
  d3.add("Torvalds", 628, 3185, techie);
  d3.add("Ritchie", 123, 5813, techie);

  d2 = d3;
  // Should display 5813
  cout << d2["Ritchie"] << endl;

  cout << d2 << endl;
} // main

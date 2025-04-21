#include <iostream>
#include <string>
#include <vector>

using namespace std;

// =============================================================================
// | Inheritance Basics
// =============================================================================

// Simple inheritance
class Base1 {};
class Derived1 : public Base1 {};

// keyword "final" = class cannot be inherited
class Base2 final {};

// Attempting to inherit a final class, will not compile
// class Derived2 : public Base2 {};


// Four levels
class Base {
public:
	//constructors are not inherited
	Base() = default;

    // polymorphism: ability to call the same method on different objects
    // this method is inherited by all derived classes,
    // but definition cannot be changed by derived classes, and the method is
    // called through the base class object
    void foo() {}

    // keyword virtual = method can be overridden
    // virtual methods can certainly have a definition, but the = 0 below
    // indicate it is a pure virtual method, meaning it has no definition
    // and waits to be defined in its children.
    virtual void virtual_foo() = 0;
};

// Level 1 inherited Base Class
class Level1 : public Base { // syntax for inheritance
public:
	// call upon base constructor for initialization
	Level1() : Base() {}

    // keyword: override = method is redefined for this class, must pair with
    // virtual in the base class
    void virtual_foo() override {}
};

//Level 2 inherited Level 1 Class, this can go on arbitrarily (unless final)
class Level2 : public Level1 {
public:
    // keyword: final = this method cannot be overridden
	virtual void foo() final {}
};

class Level3 : public Level2 {
public:
    // Attempting to override a final method, will not compile
    // void foo() override {}
};

// =============================================================================
// | Hiding and Protected
// =============================================================================
class Base_Sneaky {
public:
    void foo(int n) const { cout << "Base::foo(" << n << ")\n"; }

//Protected members are inaccessible to anything before or outisde the family
//tree
protected:
	const int& getX() const { return x; }

private:
    int x = 5;
};

class Derived_Sneaky : public Base_Sneaky {
public:
	// method has same name as base class foo
	// this will hide the base class method
    void foo() const { cout << "Derived::foo()\n"; }

	// keyword: "using" will bring the specified method into the derived class
	// the program then filters by parameter. If parameters are equal,
	// derived class method still takes priority.
	using Base_Sneaky::foo;

	// children accessing protected method of parent class
	const void display() const { cout << getX() << endl; }

};

// =============================================================================
// | Diamond Problem, Slicing, and Upcasting
// =============================================================================
class Person {
	// upcasting: when a derived class object is treated as a base class
	// does not copy, thus it is not slicing. memory of derived class is intact
	// cannot access self-private, but can access base-private bc new status
	// overridden methods remain overriden since memory of derived is intact
	friend ostream& operator<<(ostream& os, const Person& student) {
		os << "I'm a person named " << student.name << endl;
		return os;
	}

public:
	Person(const string& name) : name(name) {}
	const string& getName() const { return name; }
private:
	string name;
};

class Student : virtual public Person {

public:
	Student(const string& name) : Person(name) {}
	virtual void display() const { cout << "Student\n"; }
};

// solution: use virtual inheritance
// compiler does not embed a full copy of the base class in each derived class
// with virtual, instead they share a single copy.
// thus there's no ambiguity when calling the base class method.
class Instructor : virtual public Person { // syntax for virtual inheritance
public:

	//notice keyword "using", this allows Instructor to use Person's constructor
	using Person::Person;
	virtual void display() const { cout << "Instructor\n"; }
};

// yes, class can have 2 parents, but both parents inherit from Person.
// so for ta.getName(), do we call from Person::Instructor or Person::Student?
class TA : public Student, public Instructor {
public:

	// when inheriting virtual classes, MUST initialize common base class.
	// only one copy of Person is allowed, yet it could be initialized multiple
	// ways by Instructor and Student, thus TA provides the initialization.
	TA(const string& name): Person(name), Student(name), Instructor(name) {}

	//since name only exists in Person, do not override getName() in the derived
	//classes.
	void display() const { cout << "TA: " << getName() << endl;}
};

int main() {
    // ========================================================================
    // | Inheritance Basics
    // ========================================================================
    // The simple case
    Base1 b1;
    Derived1 d1;

    // Creating an instance of a final class
    Base2 b2;
    // derived class won't compile bc final
    // Derived2 d2;

    // Creating an instance of a base class
    //Base b0;
    // Creating an instance of a class overriding base method
    Level1 l1;
    // Creating an instance of a class declares a method final
    Level2 l2;
    // Attempting to create an instance of a class that inherits a final method
    // Level3 l3;
    // l3 won't even compile bc it attempts to override a final method

	// ========================================================================
	// | Hiding and Protected
	// ========================================================================
	Derived_Sneaky der;
	der.foo(17); // calls Base::foo(int) through code reuse, i.e. method
				   // inheritance
	der.foo();   // calls Derived::foo() through method hiding
	der.display(); // calls Derived::display() through code reuse from protected

	// ========================================================================
	// | Diamond Problem, Slicing, and Upcasting
	// ========================================================================
	TA rohit("Rohit");
	rohit.display();
	rohit.Instructor::display(); // will display "Instructor"

	// slicing is when derived class is set = to base class, all unique derived
	// aspects will be destroyed in memory.
	vector<Person> people;

	//rohit is a TA, but push_back() will copy it into a Person vector as a
	//Person, anything unique to TA not in Person will be destroyed in the copy.
	people.push_back(rohit);

	cout << rohit << endl; //upcasting
}

/*
Summary:
// inherited classes carry all fields and methods, but need their own
   constructor.

// unless virtual, methods cannnot be overridden.
        -Under the hood, program still uses base class object to call the method.
         Even if the method is called through a derived class object.
        -remember to initialized most common base class if inheriting from
         virtual classs.

// final keyword stops class/method from being inherited/overridden, in other
   words, it is the final iteration of that class/method.
		-final can only be used on virtual methods

// using Base::conflicting_name_func will remove ambiguity

// be careful of the diamond problem when inheriting from 2 classes.
		-virtual inheritance will share the base class, thus no ambiguity
		-explicit qualifiers will bypass virtual, and copy the base class
		 method.

// careful with slicing
		-happens with anything that deep copies

// to access parent fields, upcast or use getters.

// see hw7 for details.

*/



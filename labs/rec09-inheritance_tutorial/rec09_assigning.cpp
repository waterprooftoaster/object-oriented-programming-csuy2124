#include <iostream>
#include <vector>
using namespace std;

class Base;
class Derived;

class Base {
public:
    Base() = default;
private:
};

class Derived: public Base {
public:
    Derived() = default;
private:
};

int main(){
    Base a;
    Derived b;
    Base* aptr = nullptr;
    Derived* bptr = nullptr;

    a = b;
    //b = a;

    aptr = bptr;
    //bptr = aptr;

    aptr = &a;
    bptr = &b;
    aptr = &b;
    //bptr = &a;

}
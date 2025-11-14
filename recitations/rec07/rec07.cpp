
/*
Andy Wu cw4483
  rec07_start.cpp
  CS2124
  Implement the class Rational, so that the following program works.
 */

#include <iostream>
using namespace std;

int greatestCommonDivisor(int x, int y);

// Put your Rational class here.
#include <iostream>
using namespace std;

int greatestCommonDivisor(int x, int y);

// Put your Rational class here.
class Rational {
    int numerator, denominator;

    void normalize() {
        int common = greatestCommonDivisor((numerator < 0 ? -numerator
        : numerator), (denominator < 0 ? -denominator : denominator));
        numerator /= common;
        denominator /= common;
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

public:
    Rational(int num = 0, int den = 1) : numerator(num), denominator(den) {
        normalize();
    }

    Rational& operator+=(const Rational &rhs) {
        int tempNum = numerator * rhs.denominator + rhs.numerator * denominator;
        int tempDen = denominator * rhs.denominator;
        numerator = tempNum;
        denominator = tempDen;
        normalize();
        return *this;
    }

    Rational& operator++() {  // Prefix
        *this += Rational(1);
        return *this;
    }

    Rational operator++(int) {  // Postfix
        Rational tmp(*this);
        ++(*this);
        return tmp;
    }

    explicit operator bool() const {
        return numerator != 0;
    }

    friend ostream& operator<<(ostream &os, const Rational &r) {
        os << r.numerator << "/" << r.denominator;
        return os;
    }

    friend istream& operator>>(istream &is, Rational &r) {
        char delim;
        is >> r.numerator >> delim >> r.denominator;
        r.normalize();
        return is;
    }

    friend bool operator==(const Rational &a, const Rational &b) {
        return a.numerator == b.numerator && a.denominator == b.denominator;
    }

    friend bool operator<(const Rational &a, const Rational &b) {
        return a.numerator * b.denominator < b.numerator * a.denominator;
    }
};

Rational& operator--(Rational& r) {  // Prefix
    r += Rational(-1);
    return r;
}

Rational operator--(Rational& r, int) {  // Postfix
    Rational temp = r;
    r += Rational(-1);
    return temp;
}

Rational operator+(Rational lhs, const Rational& rhs) {
    return lhs += rhs;
}

// Any functions that are not members and not friends should have
// prototypes here and their definitions after main.
bool operator!=(const Rational& rhs, const Rational& lhs);
bool operator<=(const Rational& rhs, const Rational& lhs);
bool operator>(const Rational& rhs, const Rational& lhs);
bool operator>=(const Rational& rhs, const Rational& lhs);

int main()
{
    Rational a, b;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "a: ";
    cin >> a;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "b: ";
    cin >> b;
    const Rational one = 1;

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "one = " << one << endl;
    cout << "a += b: " << (a += b) << endl;	// Implement += as a member
    cout << "a = " << a << endl;

    // Implement + as non-member, but NOT as a friend
    cout << "a + one: " << (a + one) << endl;
    cout << "a == one: " << boolalpha << (a == one) << endl;

    // How does this manage to work?
    // It does NOT require writing another == operator.
    cout << "1 == one: " << boolalpha << (1 == one) << endl;

    // Do not implement as friend.
    cout << "a != one: " << boolalpha << (a != one) << endl;

    //
    // PLEASE CHECK OUT NOW
    //

    cout << "a = " << a << endl;
    cout << "++a = " << (++a) << endl;
    cout << "a = " << a << endl;
    cout << "a++ = " << (a++) << endl;
    cout << "a = " << a << endl;
    cout << "--a = " << (--a) << endl;
    cout << "a = " << a << endl;
    cout << "a-- = " << (a--) << endl;
    cout << "a = " << a << endl;

    cout << "++ ++a = " << (++ ++a) << endl;
    cout << "a = " << a << endl;
    cout << "-- --a = " << (-- --a) << endl;
    cout << "a = " << a << endl;

    cout << "a++ ++ = " << (a++ ++) << endl;
    cout << "a = " << a << endl;

    // Even though the above example, (a++ ++), compiled, the
    // following shouldn't.
    // But some compiler vendors might let it...  Is your compiler
    // doing the right thing? Why SHOULDN'T it compile?
    //cout << "a-- -- = " << (a-- --) << endl;
    cout << "a = " << a << endl;


    // Should report that 1 is true
    if (Rational(1)) {
        cout << "1 is true" << endl;
    } else {
        cout << "1 is false" << endl;
    }

    // Should report that 0 is false
    if (Rational(0)) {
        cout << "0 is true" << endl;
    } else {
        cout << "0 is false" << endl;
    }

    cout << "Comparisons\n";
    Rational twoFifths(2, 5);
    Rational threeHalves(3, 2);
    Rational minusFive(-5);
    cout << twoFifths << " < " << threeHalves << " : "
         << (twoFifths < threeHalves) << endl;
    cout << twoFifths << " <= " << 1 << " : " << (twoFifths <= 1) << endl;
    cout << threeHalves << " < " << twoFifths << " : "
         << (threeHalves < twoFifths) << endl;
    cout << threeHalves << " > " << threeHalves << " : "
         << (threeHalves > threeHalves) << endl;
    cout << threeHalves << " >= " << threeHalves << " : "
         << (threeHalves >= threeHalves) << endl;
    cout << minusFive << " >= " << threeHalves << " : "
         << (minusFive >= threeHalves) << endl;
} // main

int greatestCommonDivisor(int x, int y)
{
    while (y != 0) {
        int temp = x % y;
        x = y;
        y = temp;
    }
    return x;
} // greatestCommonDivisor

// Any functions that are not members and not friends should have
// their definitions here...

bool operator!=(const Rational& rhs, const Rational& lhs) { return !(lhs == rhs);}
bool operator<=(const Rational& rhs, const Rational& lhs) { return !(rhs < lhs);}
bool operator>(const Rational& rhs, const Rational& lhs) { return rhs <= lhs; }
bool operator>=(const Rational& rhs, const Rational& lhs) { return !(lhs < rhs);}

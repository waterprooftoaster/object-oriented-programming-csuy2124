/*
     hw06.cpp
     Andy Wu
     cw4483
*/

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

// Put your BigUnsigned class definition here.
class BigUnsigned{
private:
     vector<int> digits;


public:
     BigUnsigned() {
          digits.push_back(0);
     }

     BigUnsigned(int input) {
          if (input == 0) {
               digits.push_back(0);
          }

          else {
               int decimal_place = 1;
               while (input != 0){
                    const int curr_digit = input % (decimal_place*10); //break down int by digits
                    digits.push_back(curr_digit/decimal_place);
                    input = input - curr_digit;
                    decimal_place = decimal_place * 10;
               }
          }
     }

     BigUnsigned(const string& input) {
          istringstream iss(input);
          int input_number;
          while (iss >> input_number) {
               if (input_number == 0 && digits.empty()) {
                    continue;
               }
               digits.insert(digits.begin(), input_number); //construct with smallest digit in front
          }

          if (digits.empty()) {
               digits.push_back(0);
          }
     }

     BigUnsigned& operator+=(const BigUnsigned& rhs) {
          int carry = 0;
          for (size_t i = 0; i < digits.size(); i++) {
               if (i > (rhs.digits.size() - 1)) {
                    if (carry == 0) {
                         return *this;
                    }
                    if (digits[i] + carry >= 10) {
                         digits[i] = 0;
                         carry = 1;
                    } else {
                         digits[i] += carry;
                         carry = 0;
                    }
               }

               if (digits[i] + rhs.digits[i] + carry >= 10) {
                    digits[i] = (digits[i] + rhs.digits[i] + carry) - 10;
                    carry = 1;
               } else {
                    digits[i] += rhs.digits[i] + carry;
                    carry = 0;
               }

               if (i == digits.size() - 1) {
                    if ((rhs.digits.size() - 1 ) > i) {
                         digits.push_back(0);
                    }
                    if (i >= rhs.digits.size() && carry == 1) {
                         digits.push_back(1);
                    }
               }
          }
          return *this;
     }

     BigUnsigned& operator++() {  // Prefix
          *this += BigUnsigned(1);
          return *this;
     }

     BigUnsigned operator++(int) {  // Postfix
          BigUnsigned tmp(*this);
          ++(*this);
          return tmp;
     }

     explicit operator bool() const {
          if (digits[0] == 0) {
               return false;
          }
          return true;
     }

     friend bool operator==(const BigUnsigned &lhs, const BigUnsigned &rhs) {
          if (lhs.digits == rhs.digits) {
               return true;
          }
          return false;
     }

     friend bool operator<(const BigUnsigned &lhs, const BigUnsigned &rhs) {
          if (lhs.digits.size() > rhs.digits.size()) {
               return false;
          }

          if (lhs.digits.size() < rhs.digits.size()) {
               return true;
          }

          if (lhs.digits == rhs.digits) {
               return false;
          }

          for (size_t i = lhs.digits.size() - 1; i > -1; i--) { //compare by biggest digit first
               if (lhs.digits[i] >= rhs.digits[i]) {
                    return false;
               }
          }
          return true;
     }

     friend ostream &operator << (ostream &os, const BigUnsigned& number) {
          for (int i = static_cast<int>(number.digits.size()) - 1; i >= 0; i--) { //reverse the reversed vector so output is normal
               os << number.digits[i];
          }
          return os;
     }
};

// Any functions that are not members and not friends should have
// prototypes here.
// All non-member functions should have their definitions after main.
BigUnsigned operator+(BigUnsigned lhs, const BigUnsigned& rhs);
bool operator>(const BigUnsigned& rhs, const BigUnsigned& lhs);
bool operator!=(const BigUnsigned& rhs, const BigUnsigned& lhs);
bool operator<=(const BigUnsigned& rhs, const BigUnsigned& lhs);
bool operator>=(const BigUnsigned& rhs, const BigUnsigned& lhs);



int main() {
    BigUnsigned zero;
    BigUnsigned one(1);

    cout << "zero: " << zero << endl;
    cout << "one: " << one << endl;

    BigUnsigned val = 1;
    cout << "val: " << val << endl;
    cout << "++val: " << ++val << endl;
    cout << "val: " << val << endl;
    cout << "val++: " << val++ << endl;
    cout << "val: " << val << endl;

    cout << "(one + zero): " << (one + zero) << endl;
    cout << "(one + one): " <<  (one + one) << endl;

    cout << boolalpha;
    cout << "one < one: " << (one < one) << endl;
    cout << "zero < one: " << (zero < one) << endl;

    BigUnsigned a = 123;
    BigUnsigned b = 1234;
    BigUnsigned c = 124;
    BigUnsigned d = 12345;

    cout << "a: " << a << ", b: " << b
         << ", c: " << c << ", d: " << d << endl;
    cout << "a + d: " << (a + d) << endl;
    cout << "d + d: " << (d + d) << endl;
    cout << "a < d: " << (a < d) << endl;
    cout << "d < a: " << (d < a) << endl;
    cout << "zero == zero: " << (zero == zero) << endl
         << "zero == one: " << (zero == one) << endl
         << "a == a: " << (a == a) << endl
         << "a == d: " << (a == d) << endl
         << "d == a: " << (d == a) << endl;

    cout << "(zero == 0): " << (zero == 0) << endl
         << "(one == 0): " << (one == 0) << endl
         << "(1 == one): " << (1 == one) << endl;

    // +=
    cout << "b: " << b << ", c: " << c << endl;
    cout << "(c += b): " << (c += b) << endl;
    cout << "b: " << b << ", c: " << c << endl;


    BigUnsigned x = a;
    cout << "x: " << x << ", a: " << a << endl
         << "x == a: " << (x == a) << endl
         << "a == x: " << (a == x) << endl
         << "a < x: " << (a < x) << endl
         << "a > x: " << (a > x) << endl;

    cout << "x > a: " << (x > a) << endl
         << "x >= a: " << (x >= a) << endl
         << "x <= a: " << (x <= a) << endl
         << "x != a: " << (x != a) << endl;


    BigUnsigned big("987654321000");
    BigUnsigned big2("  ");
    BigUnsigned big3("felix");
    BigUnsigned big4("00987654321");

    cout << "big: " << big << endl
         << "big2: " << big2 << endl
         << "big3: " << big3 << endl
         << "big4: " << big4 << endl;

    BigUnsigned big5(98765);
    BigUnsigned big6(2457);
    cout << "big5: " << big5  << ", big6: " <<  big6 << endl
         << "(big5 + big6): " << (big5 + big6) << endl
         << "(big6 + big5): " << (big6 + big5) << endl;


    // How does this work?
    cout << zero << " is " << (zero ? "true" : "false") << endl;
    cout << one << " is " << (one ? "true" : "false") << endl;
    cout << big4 << " is " << (big4 ? "true" : "false") << endl;
} // main

BigUnsigned operator+(BigUnsigned lhs, const BigUnsigned& rhs) {
     return lhs += rhs;
}

bool operator!=(const BigUnsigned& rhs, const BigUnsigned& lhs) { return !(lhs == rhs);}
bool operator<=(const BigUnsigned& rhs, const BigUnsigned& lhs) {
     if (lhs == rhs || lhs < rhs) {
          return true;
     }
     return false;
}
bool operator>(const BigUnsigned& rhs, const BigUnsigned& lhs) { return !(rhs <= lhs); }
bool operator>=(const BigUnsigned& rhs, const BigUnsigned& lhs) { return !(lhs < rhs);}
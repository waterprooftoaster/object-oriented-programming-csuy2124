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
class BigUnsigned
{
private:
  vector<int> digits;

public:
  BigUnsigned()
  {
    digits.push_back(0);
  }

  BigUnsigned(int input)
  {
    if (input == 0)
    {
      digits.push_back(0);
    }
    else
    {
      int decimal_place = 1;
      while (input != 0)
      {
        const int curr_digit = input % (decimal_place * 10); // break down int by digits
        digits.push_back(curr_digit / decimal_place);
        input = input - curr_digit;
        decimal_place = decimal_place * 10;
      }
    }
  }

  BigUnsigned(const string &input)
  {
    // Parse the input string for a contiguous sequence of digits
    // We do not use istringstream or iterators. Store digits
    // with least-significant (ones) digit at index 0.
    int start = -1;
    int end = -1;
    for (int i = 0; i < (int)input.size(); ++i)
    {
      if (input[i] >= '0' && input[i] <= '9')
      {
        if (start == -1)
          start = i;
        end = i;
      }
      else if (start != -1)
      {
        // stop at first non-digit after we've started
        break;
      }
    }

    if (start == -1)
    {
      // no digits found -> zero
      digits.push_back(0);
      return;
    }

    // trim leading zeros within the digit substring
    int first_nonzero = start;
    while (first_nonzero <= end && input[first_nonzero] == '0')
      ++first_nonzero;

    if (first_nonzero > end)
    {
      // all zeros -> zero
      digits.push_back(0);
      return;
    }

    // push digits from least-significant to most-significant
    for (int i = end; i >= first_nonzero; --i)
      digits.push_back(input[i] - '0');
  }

  BigUnsigned &operator+=(const BigUnsigned &rhs)
  {
    int carry = 0;
    size_t i = 0;

    // add overlapping digits
    while (i < digits.size() && i < rhs.digits.size())
    {
      int sum = digits[i] + rhs.digits[i] + carry;
      digits[i] = sum % 10;
      carry = sum / 10;
      ++i;
    }

    // if rhs is longer, append remaining rhs digits
    while (i < rhs.digits.size())
    {
      int sum = rhs.digits[i] + carry;
      digits.push_back(sum % 10);
      carry = sum / 10;
      ++i;
    }

    // if lhs still has remaining digits, propagate carry
    while (i < digits.size())
    {
      int sum = digits[i] + carry;
      digits[i] = sum % 10;
      carry = sum / 10;
      ++i;
    }

    if (carry)
      digits.push_back(carry);

    return *this;
  }

  BigUnsigned &operator++()
  { // Prefix
    *this += BigUnsigned(1);
    return *this;
  }

  BigUnsigned operator++(int)
  { // Postfix
    BigUnsigned tmp(*this);
    ++(*this);
    return tmp;
  }

  explicit operator bool() const
  {
    // number is false only when it is exactly zero
    if (digits.size() == 1 && digits[0] == 0)
      return false;
    return true;
  }

  friend bool operator==(const BigUnsigned &lhs, const BigUnsigned &rhs)
  {
    if (lhs.digits == rhs.digits)
    {
      return true;
    }
    return false;
  }

  friend bool operator<(const BigUnsigned &lhs, const BigUnsigned &rhs)
  {
    if (lhs.digits.size() > rhs.digits.size())
      return false;

    if (lhs.digits.size() < rhs.digits.size())
      return true;

    if (lhs.digits == rhs.digits)
      return false;

    // compare from most-significant down to least-significant
    int n = (int)lhs.digits.size();
    for (int i = n - 1; i >= 0; --i)
    {
      if (lhs.digits[i] < rhs.digits[i])
        return true;
      if (lhs.digits[i] > rhs.digits[i])
        return false;
    }
    return false;
  }

  friend ostream &operator<<(ostream &os, const BigUnsigned &number)
  {
    for (int i = (int)number.digits.size() - 1; i >= 0; --i)
    {
      os << number.digits[i];
    }
    return os;
  }
};

// Any functions that are not members and not friends should have
// prototypes here.
// All non-member functions should have their definitions after main.
BigUnsigned operator+(BigUnsigned lhs, const BigUnsigned &rhs);
bool operator>(const BigUnsigned &rhs, const BigUnsigned &lhs);
bool operator!=(const BigUnsigned &rhs, const BigUnsigned &lhs);
bool operator<=(const BigUnsigned &rhs, const BigUnsigned &lhs);
bool operator>=(const BigUnsigned &rhs, const BigUnsigned &lhs);

int main()
{
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
  cout << "(one + one): " << (one + one) << endl;

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
  cout << "big5: " << big5 << ", big6: " << big6 << endl
       << "(big5 + big6): " << (big5 + big6) << endl
       << "(big6 + big5): " << (big6 + big5) << endl;

  // How does this work?
  cout << zero << " is " << (zero ? "true" : "false") << endl;
  cout << one << " is " << (one ? "true" : "false") << endl;
  cout << big4 << " is " << (big4 ? "true" : "false") << endl;
} // main

BigUnsigned operator+(BigUnsigned lhs, const BigUnsigned &rhs)
{
  return lhs += rhs;
}

bool operator!=(const BigUnsigned &rhs, const BigUnsigned &lhs) { return !(lhs == rhs); }
bool operator<=(const BigUnsigned &rhs, const BigUnsigned &lhs)
{
  if (lhs == rhs || lhs < rhs)
  {
    return true;
  }
  return false;
}
bool operator>(const BigUnsigned &rhs, const BigUnsigned &lhs) { return !(rhs <= lhs); }
bool operator>=(const BigUnsigned &rhs, const BigUnsigned &lhs) { return !(lhs < rhs); }
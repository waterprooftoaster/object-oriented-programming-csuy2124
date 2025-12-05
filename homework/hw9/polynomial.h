// Author: waterprooftoaster
// Polynomial class implementation using singly linked list

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <ostream>
#include <vector>

// Polynomial class using a singly linked list to store coefficients
class Polynomial {
  friend std::ostream &operator<<(std::ostream &os, const Polynomial &rhs);

  // Private nested Node structure for linked list
  struct Node {
    int data;
    Node *next = nullptr;
  };

public:
  // Default constructor: creates the zero polynomial
  Polynomial();

  // Constructor from vector of coefficients (highest degree first)
  explicit Polynomial(const std::vector<int> &coefficients);

  // Copy constructor
  Polynomial(const Polynomial &rhs);

  // Assignment operator
  Polynomial &operator=(const Polynomial &rhs);

  // Destructor
  ~Polynomial();

  // Append coefficient to end of list
  void push_back(const int &coefficient);

  // Add coefficient to front of list
  void push_front(const int &coefficient) const;

  // Add-assign operator
  Polynomial &operator+=(const Polynomial &rhs);

  // Equality operator
  bool operator==(const Polynomial &rhs) const;

  // Evaluate polynomial at given x value
  int evaluate(const int &x);

private:
  Node *head;     // Points directly to first coefficient (nullptr for zero)
  int degree = 0; // Degree of polynomial
};

// Addition operator
Polynomial operator+(Polynomial lhs, const Polynomial &rhs);

bool operator!=(const Polynomial &lhs, const Polynomial &rhs);

#endif

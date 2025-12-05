// Author: waterprooftoaster
// Polynomial class implementation

#include "polynomial.h"

#include <ostream>

using namespace std;

// Default constructor: creates zero polynomial (0)
Polynomial::Polynomial() : head(nullptr), degree(0) {}

// Constructor from vector: initializes with given coefficients
Polynomial::Polynomial(const std::vector<int> &coefficients)
    : head(nullptr), degree(0) {
  for (const int &coefficient : coefficients) {
    push_back(coefficient);
  }
}

// Copy constructor: deep copies all coefficients
Polynomial::Polynomial(const Polynomial &rhs) : head(nullptr), degree(0) {
  for (const Node *curr = rhs.head; curr; curr = curr->next) {
    this->push_back(curr->data);
  }
}

// Assignment operator: copies all coefficients from rhs
Polynomial &Polynomial::operator=(const Polynomial &rhs) {
  // Clean up existing data
  Node *curr = head;
  while (curr != nullptr) {
    Node *temp = curr->next;
    delete curr;
    curr = temp;
  }
  head = nullptr;
  degree = 0;

  // Copy coefficients from rhs
  for (const Node *p = rhs.head; p; p = p->next) {
    this->push_back(p->data);
  }
  return *this;
}

// Destructor: deallocates linked list
Polynomial::~Polynomial() {
  Node *curr = head;
  while (curr != nullptr) {
    Node *temp = curr->next;
    delete curr;
    curr = temp;
  }
}

// Append coefficient to end: maintains order from highest to lowest degree
void Polynomial::push_back(const int &coefficient) {
  Node *newNode = new Node{coefficient, nullptr};

  if (head == nullptr) {
    // First node
    head = newNode;
    degree = 0;
  } else {
    // Find last node and append
    Node *curr = head;
    while (curr->next) {
      curr = curr->next;
    }
    curr->next = newNode;
    degree += 1;
  }

  // Cleanup: if first coefficient is 0 but we have more non-zero terms, skip it
  if (head && head->data == 0 && head->next != nullptr) {
    Node *temp = head;
    head = head->next;
    delete temp;
    degree -= 1;
  }
}

// Add coefficient to front: used for higher degree terms
void Polynomial::push_front(const int &coefficient) const {
  Node *newNode = new Node{coefficient, head};
  // Note: const member function workaround - cast to modify head
  const_cast<Polynomial *>(this)->head = newNode;
}

// Add-assign operator: adds two polynomials
Polynomial &Polynomial::operator+=(const Polynomial &rhs) {
  const int d1 = this->degree;
  const int d2 = rhs.degree;
  const int maxDeg = max(d1, d2);

  // Prepend zeros to match degrees
  for (int i = d1; i < maxDeg; ++i) {
    head = new Node{0, head};
  }

  Node *cur = head;
  const Node *other = rhs.head;
  const int skip = maxDeg - d2;
  for (int i = 0; i < skip; ++i) {
    cur = cur->next;
  }

  // Add corresponding coefficients
  while (cur && other) {
    cur->data += other->data;
    cur = cur->next;
    other = other->next;
  }

  this->degree = maxDeg;

  // Clean up leading zeros (maintain class invariant)
  while (head && head->data == 0 && degree > 0) {
    Node *temp = head;
    head = temp->next;
    delete temp;
    degree -= 1;
  }

  return *this;
}

// Equality operator: compares degree and all coefficients
bool Polynomial::operator==(const Polynomial &rhs) const {
  if (degree != rhs.degree) {
    return false;
  }
  for (Node *curr = head, *rhs_curr = rhs.head; curr != nullptr;
       curr = curr->next, rhs_curr = rhs_curr->next) {
    if (curr->data != rhs_curr->data) {
      return false;
    }
  }
  return true;
}

// Evaluate polynomial at given x value using Horner's method
int Polynomial::evaluate(const int &x) {
  if (degree == 0) {
    return head ? head->data : 0;
  }
  int result = 0;
  // Horner's method for efficient evaluation: result = a_n*x + a_(n-1), etc.
  for (Node *curr = head; curr != nullptr; curr = curr->next) {
    result = (result * x) + curr->data;
  }
  return result;
}

// Inequality operator: negation of equality
bool operator!=(const Polynomial &lhs, const Polynomial &rhs) {
  return !(lhs == rhs);
}

// Addition operator: creates new polynomial with sum
Polynomial operator+(Polynomial lhs, const Polynomial &rhs) {
  return lhs += rhs;
}

// Output stream operator: formats polynomial for display
ostream &operator<<(ostream &os, const Polynomial &rhs) {
  // Handle zero polynomial
  if (rhs.head == nullptr) {
    return os << "0";
  }

  int degree = rhs.degree;
  for (const Polynomial::Node *curr = rhs.head; curr != nullptr && degree >= 0;
       curr = curr->next, --degree) {
    // Skip zero coefficients (except for zero polynomial)
    if (curr->data == 0 && degree > 0) {
      continue;
    }
    // Add + for positive non-leading coefficients
    if (curr->data > 0 && degree != rhs.degree) {
      os << "+";
    }
    // Handle ±1 coefficients specially
    if ((curr->data == 1 || curr->data == -1) && degree > 0) {
      if (curr->data == 1) {
        os << "x";
      } else {
        os << "-x";
      }
    } else {
      os << curr->data;
      if (degree >= 1) {
        os << "x";
      }
    }
    // Add exponent if degree > 1
    if (degree > 1) {
      os << "^" << degree;
    }
  }
  return os;
}

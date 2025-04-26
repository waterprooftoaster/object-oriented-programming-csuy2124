#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <ostream>
#include <vector>

class Polynomial {
	friend std::ostream& operator<<(std::ostream& os, const Polynomial& rhs);

	struct Node {
		int data;
		Node* next= nullptr;
	};

public:
	//constructors
	Polynomial();

	Polynomial(const std::vector<int>& coefficients);

	//copy constructor
	Polynomial(const Polynomial& rhs);

	//destructor
	~Polynomial() {
		Node* curr = head;
		while (curr != nullptr) {
			Node* temp = curr->next;
			delete curr;
			curr = temp;
		}
		delete head;
	}

	//methods
	void push_back(const int& coefficient);

	Polynomial& operator+=(const Polynomial& rhs);

	bool operator==(const Polynomial& rhs) const;

	int evaluate(const int& x);

private:
	Node* head;
	int degree = 0;
};

Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs);

bool operator!=(const Polynomial& lhs, const Polynomial& rhs);

#endif

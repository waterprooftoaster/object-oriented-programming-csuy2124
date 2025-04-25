#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <ostream>
#include <vector>

class Polynomial {
	friend std::ostream& operator<<(std::ostream& os, const Polynomial& rhs);

	struct Node {
		int data;
		Node *next;
	};

public:
	Polynomial() { head->next = new Node{0, nullptr}; }
	Polynomial(const std::vector<int>& coefficients) {
		for (const int& coefficient : coefficients) { push_back(coefficient); }
	}

	void push_back(const int& coefficient);

	Polynomial& operator+=(const Polynomial& rhs);
	bool operator==(const Polynomial& rhs) const;

private:
	Node* head;
	int degree = 0;
};

#endif
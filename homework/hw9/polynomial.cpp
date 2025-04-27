#include "polynomial.h"

#include <ostream>

using namespace std;

Polynomial::Polynomial()
: head(new Node()) { head->next = new Node {0, nullptr}; }

Polynomial::Polynomial(const std::vector<int>& coefficients)
: head(new Node()) {
	head->next = new Node {0, nullptr};
	for (const int& coefficient : coefficients) { push_back(coefficient); }
}

Polynomial::Polynomial(const Polynomial& rhs)
: head(new Node()) {
	head->next = new Node {0, nullptr};
	for (const Node* curr = rhs.head->next; curr; curr = curr->next) {
		this->push_back(curr->data);
	}
}

void Polynomial::push_back(const int& coefficient) {
	if (head->next->data == 0) {
		delete head->next;
		head->next = new Node {coefficient, nullptr};
	}
	else {
		Node* curr = head->next;
		while (curr->next) { curr = curr->next; }
		curr->next = new Node {coefficient, nullptr};
		degree += 1;
	}
}

void Polynomial::push_front(const int& coefficient) const {
	if (head->next->data == 0) {
		delete head->next;
		head->next = new Node {coefficient, nullptr};
	}
	else {
		Node* temp = new Node {coefficient, head->next};
		head->next = temp;
	}
}

Polynomial& Polynomial::operator+=(const Polynomial& rhs) {
	const int d1 = this->degree;
	const int d2 = rhs.degree;
	const int maxDeg = max(d1, d2);

	for (int i = d1; i < maxDeg; ++i) {
		head -> next = new Node{0, head -> next};
	}

	Node* cur = head -> next;
	const Node* other = rhs.head -> next;
	const int skip  = maxDeg - d2;
	for (int i = 0; i < skip; ++i) { cur = cur -> next; }

	while (cur && other) {
		cur -> data += other -> data;
		cur   = cur -> next;
		other = other -> next;
	}

	this->degree = maxDeg;
	return *this;
}

bool Polynomial::operator==(const Polynomial& rhs) const {
	if (degree != rhs.degree) { return false; }
	for (Node* curr = head,* rhs_curr = rhs.head; curr != nullptr;
		 curr = curr -> next, rhs_curr = rhs_curr -> next) {
		if (curr -> data != rhs_curr -> data) { return false; }
	}
	return true;
}

int Polynomial::evaluate(const int& x) {
	if (degree = 0) { return head->next->data; }
	int result = 0;
	// horner's method
	for (Node* curr = head; curr != nullptr; curr = curr->next) {
		if (curr->next) { result = (result * x) + (curr->next->data); }
	}
	return result;
}

bool operator!=(const Polynomial& lhs, const Polynomial& rhs) {
	return !(lhs == rhs);
}

Polynomial operator+(Polynomial lhs, const Polynomial& rhs) {
	return lhs += rhs;
}

ostream& operator<<(ostream& os, const Polynomial& rhs) {
	int degree = rhs.degree;
	for (auto curr = rhs.head->next; curr != nullptr && degree >= 0;
		 curr = curr->next, --degree) {
		if (curr->data == 0 && degree > 0) { continue; }
		if (curr->data > 0 && degree != rhs.degree) { os << "+"; }
		if ((curr-> data == 1 || curr-> data == -1) && degree > 0) {
			if (curr-> data == 1) {os << "x";}
			else {os << "-x";}
		} else {
			os << curr->data;
			if (degree >= 1) { os << "x"; }
		}
		if (degree > 1) { os << "^" << degree; }
	}
	return os;
}

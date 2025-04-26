#include "polynomial.h"

#include <ostream>

using namespace std;
Polynomial::Polynomial() {
	head = new Node{};
	head->next = new Node {0, nullptr};
}

Polynomial::Polynomial(const std::vector<int>& coefficients) {
	head = new Node{};
	head->next = new Node {0, nullptr};
	for (const int& coefficient : coefficients) { push_back(coefficient); }
}
Polynomial::Polynomial( const Polynomial& rhs) : head(new Node()), degree(0) {
	for (const Node* curr = rhs.head->next; curr; curr = curr->next) {
		this->push_back(curr->data);
	}
}
void Polynomial::push_back(const int& coefficient) {
	if (head->next->data = 0) {
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

Polynomial& Polynomial::operator+=(const Polynomial& rhs) {
	Node* lhs_curr = head->next;
	const Node* rhs_curr = rhs.head->next;
	if (degree > rhs.degree) {
		for (int i = 0; i < degree - rhs.degree && lhs_curr != nullptr; i++) {
			lhs_curr = lhs_curr->next;
		}
	}
	if (rhs.degree > degree) {
		for (int i = 0; i < rhs.degree - degree && rhs_curr != nullptr; i++) {
			rhs_curr = rhs_curr->next;
		}
	}
	for (; lhs_curr != nullptr && rhs_curr != nullptr;
		   lhs_curr = lhs_curr->next, rhs_curr = rhs_curr->next) {
		lhs_curr->data = lhs_curr->data + rhs_curr->data;
	}
	return *this;
}

bool Polynomial::operator==(const Polynomial& rhs) const {
	if (degree != rhs.degree) { return false; }
	for (Node* curr = head,
			 * rhs_curr = rhs.head;
	     curr != nullptr;
		 curr = curr->next, rhs_curr = rhs_curr->next) {
		if (curr->data != rhs_curr->data) { return false; }
	}
	return true;
}

int Polynomial::evaluate(const int& x) {
	if (degree = 0) { return head -> next -> data; }
	int result = 0;
	//horner's method
	for (Node* curr = head; curr != nullptr; curr = curr->next) {
		if (curr -> next) {
			result = (result * x) + (curr -> next-> data);
		}
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
	for (const Polynomial::Node* curr = rhs.head; curr != nullptr;
		 curr = curr->next) {
		if (curr->data == 0) {
			degree -= 1;
			continue;
		}
		if (degree == 1) {
			os << curr->data << "x";
			degree -= 1;
		}
		if (degree == 0) { os << curr->data; }
		os << curr->data << "x^" << degree;
		if (curr->next) { os << "+"; }
		if (!(curr->next)) { os << endl; }
	}
	return os;
}

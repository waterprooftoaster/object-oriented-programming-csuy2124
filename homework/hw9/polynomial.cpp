#include "polynomial.h"

#include <ostream>

using namespace std;

void Polynomial::push_back(const int& coefficient) {
	if (head->next->data = 0) {
		delete head -> next;
		head -> next = new Node{coefficient, nullptr};
	} else {
		Node* curr = head -> next;
		while (curr -> next) {
			curr = curr -> next;
		}
		curr -> next = new Node{coefficient, nullptr};
		degree += 1;
	}
}

Polynomial& Polynomial::operator+=(const Polynomial& rhs) {
	Node* lhs_curr = head;
	Node* rhs_curr = rhs.head;
	if (degree > rhs.degree) {
		for (int i = 0; i < degree - rhs.degree; i++){ lhs_curr = lhs_curr -> next; }
	}
	if (rhs.degree > degree) {
		for (int i = 0; i < rhs.degree - degree; i++){ rhs_curr = rhs_curr -> next; }
	}
	for (; lhs_curr != nullptr, rhs_curr != nullptr;
		 lhs_curr = lhs_curr->next, rhs_curr = rhs_curr->next) {
		lhs_curr -> data = lhs_curr -> data + rhs_curr -> data;
	}
	return *this;
}

bool Polynomial::operator==(const Polynomial& rhs) const {
	if (degree != rhs.degree) { return false; }
	for (Node* curr = head, Node* rhs_curr = rhs.head; curr != nullptr;
		 curr = curr->next, rhs_curr = rhs_curr->next) {
		if (curr -> data != rhs_curr -> data) { return false; }
	}
	return true;
}

ostream& operator<<(ostream& os, const Polynomial& rhs) {

}

bool operator!=(const Polynomial& lhs, const Polynomial& rhs) {
	return !(lhs == rhs);
}

Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs) {
	return lhs += rhs;
}
#include "List.h"

namespace DoublyLinkedList{

std::ostream& operator<<(std::ostream& os, const List& list) {
  printListInfo(list);
  return os;
}

void List::push_back(int data) const {
	Node* new_node = new Node {data, tail, tail->prev};
	tail->prev = new_node;
	new_node->prev->next = new_node;
}

void List::push_front(int data) const {
	Node* new_node = new Node {data, head->next, head};
	head->next = new_node;
	new_node->next->prev = new_node;
}

void List::pop_back() const {
	if (head->next == tail) { return; }
	Node* to_delete = tail->prev;
	Node* new_last = to_delete->prev;
	new_last->next = tail;
	tail->prev = new_last;
	to_delete->prev = nullptr;
	to_delete->next = nullptr;
	delete to_delete;
}

void List::pop_front() const {
	if (head->next == tail) { return; }
	Node* to_delete = head->next;
	Node* new_first = to_delete->next;
	new_first->prev = to_delete->prev;
	head->next = new_first;
	to_delete->next = nullptr;
	to_delete->prev = nullptr;
	delete to_delete;
}

int List::front() const { return head->next->data; }

int List::back() const { return tail->prev->data; }

int& List::front() { return head->next->data; }

int& List::back() { return tail->prev->data; }

size_t List::size() const {
	size_t size = 0;
	for (Node* node = head; node != tail; node = node->next) { size++; }
	return size;
}

void List::clear() const {
	if (head->next == tail) { return; }
	Node* pointer = head->next;
	while (pointer->next != tail) {
		Node* temp = pointer->next;
		pointer->next = nullptr;
		pointer->prev = nullptr;
		delete pointer;
		pointer = temp;
	}
}

int& List::operator[](std::size_t index) {
	Node* cur = head->next;
	for (std::size_t i = 0; i < index && cur != tail; ++i)
		cur = cur->next;
	if (cur == tail)
		throw std::out_of_range("Index out of range");
	return cur->data;
}

const int& List::operator[](std::size_t index) const {
	Node* cur = head->next;
	for (std::size_t i = 0; i < index && cur != tail; ++i)
		cur = cur->next;
	if (cur == tail)
		throw std::out_of_range("Index out of range");
	return cur->data;
}

void changeFrontAndBack(List& theList) {
	theList.front() = 17;
	theList.back() = 42;
}

// Task 4
void printListSlow(const List& myList) {
	for (size_t i = 0; i < myList.size(); ++i) { std::cout << myList[i] << ' '; }
	std::cout << std::endl;
}

// Task 8
void doNothing(List aList) {
	std::cout << "In doNothing\n";
	printListInfo(aList);
	std::cout << std::endl;
	std::cout << "Leaving doNothing\n";
}

// Task 1
void printListInfo(const List& myList) {
	std::cout << "size: " << myList.size() << ", front: " << myList.front() <<
		", back(): " << myList.back() << ", list: " << myList << std::endl;
}

// The following should not compile. Check that it does not.
// void changeFrontAndBackConst(const List &theList) {
// 	theList . front() = 17;
// 	theList . back() = 42;
// }

}
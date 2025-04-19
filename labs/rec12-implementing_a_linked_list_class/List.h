#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <cstdlib>
#include <ostream>
#include <string>

namespace DoublyLinkedList{

class List {
	friend std::ostream& operator<<(std::ostream& os, const List& list);

	struct Node {
		int data;
		Node* next = nullptr;
		Node* prev = nullptr;
	};

public:
	List() : head(new Node()), tail(new Node()) {
		head->next = tail, tail->prev = head;
	}

	~List() {}

	void push_back(int data) const;

	void push_front(int data) const;

	void pop_back() const;

	void pop_front() const;

	int front() const;

	int back() const;

	int& front();

	int& back();

	size_t size() const;

	void clear() const;

	int& operator[](std::size_t index);

	const int& operator[](std::size_t index) const;

private:
	Node* tail;
	Node* head;
};

void changeFrontAndBack(List& theList);

void printListSlow(const List& myList);

void doNothing(List aList);

void printListInfo(const List& myList);
}
#endif
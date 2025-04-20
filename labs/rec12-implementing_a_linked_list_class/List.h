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

	void push_back(int data);

	void push_front(int data);

	void pop_back();

	void pop_front();

	int front() const;

	int back() const;

	int& front();

	int& back();

	size_t size() const;

	void clear();

	int& operator[](std::size_t index);

	const int& operator[](std::size_t index) const;

private:
	Node* tail;
	Node* head;
	size_t list_size = 0;
};

void changeFrontAndBack(List& theList);

void printListSlow(const List& myList);

void doNothing(List aList);

void printListInfo(const List& myList);
}
#endif
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
	class iterator {
	friend class List;

	public:
		explicit iterator(Node* iterator_node = nullptr): node(iterator_node) {}

		int& operator*() const;

		iterator& operator++();

		iterator& operator--();

		bool operator==(const iterator& rhs) const;

		bool operator!=(const iterator& rhs) const;
	
	private:
		Node* node = nullptr;
	};
	
	List() : head(new Node()), tail(new Node()) {
		head->next = tail, tail->prev = head;
	}
	~List() {clear(); delete head; delete tail;}

	iterator begin() const;

	iterator end() const;
	
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

	int& operator[](const std::size_t& index);

	const int& operator[](const std::size_t& index) const;

	const iterator insert(const iterator& index_iterator, const int& data);

	const iterator erase(const iterator& index_iterator);

private:
	Node* tail;
	Node* head;
	size_t list_size = 0;
};

void changeFrontAndBack(List& theList);

void printListSlow(const List& myList);

void doNothing(const List& aList);

void printListInfo(const List& myList);
}
#endif
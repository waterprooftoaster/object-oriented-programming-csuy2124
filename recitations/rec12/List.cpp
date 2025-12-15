#include "List.h"

namespace DoublyLinkedList
{

	std::ostream &operator<<(std::ostream &os, const List &list)
	{
		for (List::Node *curr = list.head->next; curr != list.tail; curr = curr->next)
		{
			os << curr->data << " ";
		}
		return os;
	}

	void List::push_back(int data)
	{
		Node *new_node = new Node{data, tail, tail->prev};
		tail->prev = new_node;
		new_node->prev->next = new_node;
		list_size++;
	}

	void List::push_front(int data)
	{
		Node *new_node = new Node{data, head->next, head};
		head->next = new_node;
		new_node->next->prev = new_node;
		list_size++;
	}

	void List::pop_back()
	{
		if (head->next == tail)
		{
			return;
		}
		Node *to_delete = tail->prev;
		Node *new_last = to_delete->prev;
		new_last->next = tail;
		tail->prev = new_last;
		to_delete->prev = nullptr;
		to_delete->next = nullptr;
		delete to_delete;
		list_size--;
	}

	void List::pop_front()
	{
		if (head->next == tail)
		{
			return;
		}
		Node *to_delete = head->next;
		Node *new_first = to_delete->next;
		new_first->prev = to_delete->prev;
		head->next = new_first;
		to_delete->next = nullptr;
		to_delete->prev = nullptr;
		delete to_delete;
		list_size--;
	}

	int List::front() const { return head->next->data; }

	int List::back() const { return tail->prev->data; }

	int &List::front() { return head->next->data; }

	int &List::back() { return tail->prev->data; }

	size_t List::size() const { return list_size; }

	void List::clear()
	{
		if (head->next == tail)
		{
			return;
		}
		list_size = 0;
		const Node *curr = head->next;
		while (curr != tail)
		{
			const Node *next = curr->next;
			delete curr;
			curr = next;
		}
		// relink head and tail
		head->next = tail;
		tail->prev = head;
	}

	int &List::operator[](const std::size_t &index)
	{
		if (index > size() - 1 || index < 0)
		{
			throw std::out_of_range("index out of range");
		}
		iterator curr = begin();
		for (std::size_t i = 0; i < index; ++i)
		{
			++curr;
		}
		return *curr;
		// Node* cur = head->next;
		// for (std::size_t i = 0; i < index && cur != tail; ++i)
		// 	cur = cur->next;
		// if (cur == tail)
		// 	std::cout << "index out of range" << std::endl;
		// return cur->data;
	}

	const int &List::operator[](const std::size_t &index) const
	{
		if (index > size() - 1 || index < 0)
		{
			throw std::out_of_range("index out of range");
		}
		iterator curr = begin();
		for (std::size_t i = 0; i < index; ++i)
		{
			++curr;
		}
		return *curr;
		// Node* cur = head->next;
		// for (std::size_t i = 0; i < index && cur != tail; ++i)
		// 	cur = cur->next;
		// if (cur == tail)
		// 	std::cout << "index out of range" << std::endl;
		// return cur->data;
	}
	List::iterator List::begin() const { return iterator{head->next}; }

	List::iterator List::end() const { return iterator{tail}; }

	int &List::iterator::operator*() const { return node->data; }

	List::iterator &List::iterator::operator++()
	{
		node = node->next;
		return *this;
	}

	List::iterator &List::iterator::operator--()
	{
		node = node->prev;
		return *this;
	}

	bool List::iterator::operator==(const iterator &rhs) const { return node == rhs.node; }

	bool List::iterator::operator!=(const iterator &rhs) const { return !(*this == rhs); }

	const List::iterator List::insert(const iterator &index_iterator, const int &data)
	{
		Node *new_node = new Node{data, index_iterator.node, index_iterator.node->prev};
		index_iterator.node->prev->next = new_node;
		index_iterator.node->prev = new_node;
		list_size++;
		return iterator{new_node};
	}

	const List::iterator List::erase(const iterator &index_iterator)
	{
		Node *temp = index_iterator.node->next;
		index_iterator.node->prev->next = index_iterator.node->next;
		index_iterator.node->next->prev = index_iterator.node->prev;
		index_iterator.node->prev = nullptr;
		index_iterator.node->next = nullptr;
		delete index_iterator.node;
		list_size--;
		return iterator{temp};
	}

	void changeFrontAndBack(List &theList)
	{
		theList.front() = 17;
		theList.back() = 42;
	}

	// Task 4
	void printListSlow(const List &myList)
	{
		for (size_t i = 0; i < myList.size(); ++i)
		{
			std::cout << myList[i] << ' ';
		}
		std::cout << std::endl;
	}

	// Task 8
	void doNothing(const List &aList)
	{
		std::cout << "In doNothing\n";
		printListInfo(aList);
		std::cout << std::endl;
		std::cout << "Leaving doNothing\n";
	}

	// Task 1
	void printListInfo(const List &myList)
	{
		std::cout << "size: " << myList.size() << ", front: " << myList.front() << ", back(): " << myList.back() << ", list: " << myList << std::endl;
	}

	// The following should not compile. Check that it does not.
	// void changeFrontAndBackConst(const List &theList) {
	// 	theList . front() = 17;
	// 	theList . back() = 42;
	// }
}
// Doubly linked list
//  Test code

#include <cstdlib>
#include <iostream>
using namespace std;

class List {
	friend ostream& operator<<(ostream& os, const List& list);

	struct Node {
		int data;
		Node* next = nullptr;
		Node* prev = nullptr;
	};

public:
	List()
	: head(new Node()), tail(new Node()) {
		head->next = tail, tail->prev = head;
	}

	~List() {}

	void push_back(int data) {
		Node* new_node = new Node {data, tail, tail->prev};
		tail->prev = new_node;
		new_node->prev->next = new_node;
	}

	void push_front(int data) {
		Node* new_node = new Node {data, head->next, head};
		head->next = new_node;
		new_node->next->prev = new_node;
	}

	void pop_back() {
		if (head->next == tail) { return; }
		Node* to_delete = tail->prev;
		Node* new_last = to_delete->prev;
		new_last->next = tail;
		tail->prev = new_last;
		to_delete->prev = nullptr;
		to_delete->next = nullptr;
		delete to_delete;
	}

	void pop_front() {
		if (head->next == tail) { return; }
		Node* to_delete = head->next;
		Node* new_first = to_delete->next;
		new_first->prev = to_delete->prev;
		head->next = new_first;
		to_delete->next = nullptr;
		to_delete->prev = nullptr;
		delete to_delete;
	}

	int front() const { return head->next->data; }

	int back() const { return tail->prev->data; }

	int& front() { return head->next->data; }

	int& back() { return tail->prev->data; }

	size_t size() const {
		size_t size = 0;
		for (Node* node = head; node != tail; node = node->next) { size++; }
		return size;
	}

	void clear() {
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

	int& operator[](std::size_t index) {
		Node* cur = head->next;
		for (std::size_t i = 0; i < index && cur != tail; ++i)
			cur = cur->next;
		if (cur == tail)
			throw std::out_of_range("Index out of range");
		return cur->data;
	}

	const int& operator[](std::size_t index) const {
		Node* cur = head->next;
		for (std::size_t i = 0; i < index && cur != tail; ++i)
			cur = cur->next;
		if (cur == tail)
			throw std::out_of_range("Index out of range");
		return cur->data;
	}

private:
	Node* tail;
	Node* head;
};

ostream& operator<<(ostream& os, const List& list) { printListInfo(list);}

void changeFrontAndBack(List& theList) {
	theList.front() = 17;
	theList.back() = 42;
}

// Task 4
void printListSlow(const List& myList) {
	for (size_t i = 0; i < myList.size(); ++i) { cout << myList[i] << ' '; }
	cout << endl;
}

// Task 8
void doNothing(List aList) {
	cout << "In doNothing\n";
	printListInfo(aList);
	cout << endl;
	cout << "Leaving doNothing\n";
}

// Task 1
void printListInfo(const List& myList) {
	cout << "size: " << myList.size() << ", front: " << myList.front() <<
		", back(): " << myList.back() << ", list: " << myList << endl;
}

// The following should not compile. Check that it does not.
// void changeFrontAndBackConst(const List &theList) {
// 	theList . front() = 17;
// 	theList . back() = 42;
// }

int main() {
	// Task 1
	cout << "\n------Task One------\n";
	List myList;
	cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
	for (int i = 0; i < 10; ++i) {
		cout << "myList.push_back(" << i * i << ");\n";
		myList.push_back(i * i);
		printListInfo(myList);
	}
	cout << "===================\n";

	cout << "Modify the first and last items, and display the results\n";
	changeFrontAndBack(myList);
	printListInfo(myList);
	cout << "===================\n";

	cout << "Remove the items with pop_back\n";
	while (myList.size()) {
		printListInfo(myList);
		myList.pop_back();
	}
	cout << "===================\n";

	// Task 2
	cout << "\n------Task Two------\n";
	cout << "Fill empty list with push_front: i*i for i from 0 to 9\n";
	for (int i = 0; i < 10; ++i) {
		cout << "myList2.push_front(" << i * i << ");\n";
		myList.push_front(i * i);
		printListInfo(myList);
	}
	cout << "===================\n";
	cout << "Remove the items with pop_front\n";
	while (myList.size()) {
		printListInfo(myList);
		myList.pop_front();
	}
	printListInfo(myList);
	cout << "===================\n";

	cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
	for (int i = 0; i < 10; ++i) { myList.push_back(i * i); }
	printListInfo(myList);
	cout << "Now clear\n";
	myList.clear();
	cout << "Size: " << myList.size() << ", list: " << myList << endl;
	cout << "===================\n";
	/*
		// Task 3
		cout << "\n------Task Three------\n";
		cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
		for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
		cout << "Display elements with op[]\n";
		for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
		cout << endl;
		cout << "Add one to each element with op[]\n";
		for (size_t i = 0; i < myList.size(); ++i) myList[i] += 1;
		cout << "And print it out again with op[]\n";
		for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
		cout << endl;
		cout << "Now calling a function, printListSlow, to do the same thing\n";
		printListSlow(myList);
		cout << "Finally, for this task, using the index operator to modify\n"
			 << "the data in the third item in the list\n"
			 << "and then using printListSlow to display it again\n";
		myList[2] = 42;
		printListSlow(myList);


		// Task 4
		cout << "\n------Task Four------\n";
		cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
		myList.clear();
		for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
		printListInfo(myList);
		cout << "Now display the elements in a ranged for\n";
		for (int x : myList) cout << x << ' ';
		cout << endl;
		cout << "And again using the iterator type directly:\n";
		// Note you can choose to nest the iterator class or not, your choice.
		//for (iterator iter = myList.begin(); iter != myList.end(); ++iter) {
		for (List::iterator iter = myList.begin(); iter != myList.end(); ++iter) {
			cout << *iter << ' ';
		}
		cout << endl;
		cout << "WOW!!! (I thought it was cool.)\n";

		// Task 5
		cout << "\n------Task Five------\n";
		cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
		myList.clear();
		for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
		printListInfo(myList);
		cout << "Filling an empty list with insert at begin(): "
			 << "i*i for i from 0 to 9\n";
		myList.clear();
		for (int i = 0; i < 10; ++i) myList.insert(myList.begin(), i*i);
		printListInfo(myList);
		// ***Need test for insert other than begin/end***
		cout << "===================\n";

		// Task 6
		cout << "\n------Task Six------\n";
		cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
		myList.clear();
		for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
		cout << "Erasing the elements in the list, starting from the beginning\n";
		while (myList.size()) {
			printListInfo(myList);
			myList.erase(myList.begin());
		}
		// ***Need test for erase other than begin/end***
		cout << "===================\n";

		// Task 7
		cout << "\n------Task Seven------\n";
		cout << "Copy control\n";
		cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
		myList.clear();
		for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
		printListInfo(myList);
		cout << "Calling doNothing(myList)\n";
		doNothing(myList);
		cout << "Back from doNothing(myList)\n";
		printListInfo(myList);

		cout << "Filling listTwo with insert at begin: i*i for i from 0 to 9\n";
		List listTwo;
		for (int i = 0; i < 10; ++i) listTwo.insert(listTwo.begin(), i*i);
		printListInfo(listTwo);
		cout << "listTwo = myList\n";
		listTwo = myList;
		cout << "myList: ";
		printListInfo(myList);
		cout << "listTwo: ";
		printListInfo(listTwo);
		cout << "===================\n";
		*/
}

/*
  rec11-starter.cpp
  John Sterling

  Test code for students to use for the linked list basics
  recitation.
*/

#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

//
//  From linked list library in the course's sample code
//
struct Node
{
  // Node(int data = 0, Node *next = nullptr) : data(data), next(next) {}
  int data;
  Node *next;
};
//
//  Solution to recitation goes here:
//

// reverse. Creates a new list with all new nodes. Does not modify
// anything in the original list. About seven lines, ignoring close
// braces.
Node *reverse(const Node *hp);

// reverseInPlace. Modifies the original list. No new nodes are
// created. Doesn't change the data values in the nodes, just their
// next fields, so it rearranges the nodes themselves within the
// list.

// Note the "pass by reference" for the head pointer! The parameter,
// hp will be holding a different address when you are done.

// This solution is likely a couple of lines longer than reverse.
void reverseInPlace(Node *&hp);

// Does the sequence of data VALUES in pattern appear anywhere contiguously
// in that order in target?
// Return the position where a match is found, otherwise null.
// Node* isSublist(Node* pattern, Node* target);
const Node *isSublist(const Node *pattern, const Node *target);

// test the nodes in listB looking for the first one to match a node
// from listA. Note that we are matching the addresses of the nodes,
// not the data they hold.
// Node* sharedListBruteForce(Node* listA, Node* listB);
const Node *sharedListBruteForce(const Node *listA, const Node *listB);

// Use an "unordered set", i.e. a hashtable, to identify the first
// element in listB that is also in listA.
// Node* sharedListUsingSet(Node* listA, Node* listB);
const Node *sharedListUsingSet(const Node *listA, const Node *listB);

///////////////////////////////////////////////////////////////////////////////
//
// Provided test code
//
void listAddHead(Node *&headPtr, int entry);
void listPrint(const Node *headPtr);
void listClear(Node *&headPtr);
Node *listBuild(const vector<int> &vals);
void match(const Node *target, const Node *pattern);

int main()
{
  cout << "Part one: \n\n";

  Node *original = listBuild({6, 3, 2, 5});
  cout << "original: ";
  listPrint(original);

  Node *reversed = reverse(original);
  cout << "Calling reverse:\n";
  cout << "original: ";
  listPrint(original);
  cout << "Reversed: ";
  listPrint(reversed);

  cout << "Calling reverseInPlace on the original:\n";
  cout << "original before: ";
  listPrint(original);
  reverseInPlace(original);
  cout << "original after: ";
  listPrint(original);

  cout << "=====================\n\n"
       << "Part two: \n\n";

  // Target: 1 2 3 2 3 2 4 5 6
  Node *target = listBuild({1, 2, 3, 2, 3, 2, 4, 5, 6});
  cout << "Target: ";
  listPrint(target);
  cout << endl;

  // Attempt Match: 1
  // Node* m1 = nullptr;
  Node *m1 = listBuild({1});
  match(target, m1);
  listClear(m1);

  // Attempt : 3 9
  // Node* m2 = nullptr;
  Node *m2 = listBuild({3, 9});
  match(target, m2);
  listClear(m2);

  // Attempt Match: 2 3
  // Node* m3 = nullptr;
  Node *m3 = listBuild({2, 3});
  match(target, m3);
  listClear(m3);

  // Attempt Match: 2 4 5 6
  Node *m4 = listBuild({2, 4, 5, 6});
  match(target, m4);
  listClear(m4);

  // Attempt Match: 2 3 2 4
  Node *m5 = listBuild({2, 3, 2, 4});
  match(target, m5);
  listClear(m5);

  // Attempt Match: 5 6 7
  Node *m6 = listBuild({5, 6, 7});
  match(target, m6);
  listClear(m6);

  // Attempt Match:
  m1 = listBuild({6});
  match(target, m1);
  listClear(m1);

  // Attempt Match:
  m1 = nullptr;
  match(target, m1);

  cout << "Task Three\n";
  cout << "Target: ";
  listPrint(target);

  cout << "Matching target against self:\n";
  cout << "Brute force: ";
  listPrint(sharedListBruteForce(target, target));
  cout << "Using Set:   ";
  listPrint(sharedListUsingSet(target, target));

  cout << "Matching target against dup of self:\n";
  // Node* dupOfTarget = listDup(target);
  Node *dupOfTarget = listBuild({1, 2, 3, 2, 3, 2, 4, 5, 6});
  cout << "Brute force: ";
  listPrint(sharedListBruteForce(target, dupOfTarget));
  cout << "Using Set:   ";
  listPrint(sharedListUsingSet(target, dupOfTarget));
  listClear(dupOfTarget);

  cout << "Matching target against part of self from fourth node:\n";
  cout << "Brute force: ";
  listPrint(sharedListBruteForce(target, target->next->next->next));
  cout << "Using Set:   ";
  listPrint(sharedListUsingSet(target, target->next->next->next));

  cout << "testing against another list whose fourth node"
       << " matches target's fifth node\n";
  Node *another = target->next->next->next->next;
  listAddHead(another, 7);
  listAddHead(another, 6);
  listAddHead(another, 5);
  cout << "other list:\n";
  listPrint(another);

  cout << "Brute force: ";
  const Node *startOfShared = sharedListBruteForce(target, another);
  listPrint(startOfShared);

  cout << "Using Set:   ";
  startOfShared = sharedListUsingSet(target, another);
  listPrint(startOfShared);

  // Clean up
  listClear(target);
  for (Node *p = another; p != startOfShared;)
  {
    Node *pNext = p->next;
    delete p;
    p = pNext;
  }
} // main

Node *reverse(const Node *hp)
{
  Node *result = nullptr;
  for (const Node *p = hp; p; p = p->next)
  {
    result = new Node{p->data, result};
  }
  return result;
}

void reverseInPlace(Node *&hp)
{
  Node *prev = nullptr;
  Node *curr = hp;
  while (curr)
  {
    Node *next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }
  hp = prev;
}

void match(const Node *target, const Node *pattern)
{
  cout << "Attempt pattern: ";
  listPrint(pattern);
  const Node *result = isSublist(pattern, target);
  if (result)
    listPrint(result);
  else
    cout << "Failed to match\n";
  cout << endl;
}

void listAddHead(Node *&headPtr, int entry)
{
  headPtr = new Node{entry, headPtr};
}

void listPrint(const Node *headPtr)
{
  const Node *p = headPtr;
  while (p != nullptr)
  {
    cout << p->data << ' ';
    p = p->next;
  }
  cout << endl;
}

Node *listBuild(const vector<int> &vals)
{
  Node *result = nullptr;
  for (size_t index = vals.size(); index > 0; --index)
  {
    listAddHead(result, vals[index - 1]);
  }
  return result;
} // listBuild

void listClear(Node *&headPtr)
{
  while (headPtr)
  {
    Node *next = headPtr->next;
    delete headPtr;
    headPtr = next;
  }
}

const Node *isSublist(const Node *pattern, const Node *target)
{
  for (const Node *t = target; t != nullptr; t = t->next)
  {
    const Node *p = pattern;
    const Node *q = t;
    while (p && q && p->data == q->data)
    {
      p = p->next;
      q = q->next;
    }
    if (!p)
      return t;
  }
  return nullptr;
}

const Node *sharedListBruteForce(const Node *listA, const Node *listB)
{
  while (listA)
  {
    const Node *start = listB;
    while (listB)
    {
      if (listB == listA)
        return listA;
      listB = listB->next;
    }
    listA = listA->next;
    listB = start;
  }
  return nullptr;
}

// Use an "unordered set", i.e. a hashtable, to identify the first
// element in listB that is also in listA.
// Node* sharedListUsingSet(Node* listA, Node* listB);
const Node *sharedListUsingSet(const Node *listA, const Node *listB)
{
  unordered_set<const Node *> addresses;
  while (listA)
  {
    addresses.insert(listA);
    listA = listA->next;
  }
  while (listB)
  {
    if (addresses.find(listB) == addresses.end())
    {
      listB = listB->next;
    }
    else
    {
      return listB;
    }
  }
  return nullptr;
}
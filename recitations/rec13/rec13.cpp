#include <algorithm> // task 3
#include <fstream>
#include <iostream>
#include <list>   // task 2
#include <map>    // task 23
#include <set>    // task 22
#include <string> // task 21
#include <vector> // task 1
using namespace std;

template <typename T> void printVec(const vector<T> &v) {
  for (const T &i : v) {
    cout << i << " ";
  }
  cout << endl;
}

void printListRF(const list<int> &l) {
  for (int i : l) {
    cout << i << " ";
  }
  cout << endl;
}

void printlistAuto(const list<int> &l) {
  for (auto iter = l.begin(); iter != l.end();) {
    cout << *iter << " ";
    ++iter;
    if (iter == l.end())
      break;
    ++iter;
  }
  cout << endl;
}

auto findList(const list<int> &l, int val) {
  cout << "findList()" << endl;
  for (auto iter = l.begin(); iter != l.end(); ++iter) {
    if (*iter == val)
      return iter;
  }
  return l.end();
}

list<int>::const_iterator ourFind(list<int>::const_iterator begin,
                                  list<int>::const_iterator end, int target) {
  cout << "ourFind list<int> (non-template)" << endl;
  for (list<int>::const_iterator p = begin; p != end; ++p) {
    if (*p == target)
      return p;
  }
  return end;
}

template <typename Fred, typename Mary>
Fred ourFind(Fred begin, Fred end, Mary target) {
  cout << "ourFind template" << endl;
  for (Fred p = begin; p != end; ++p) {
    if (*p == target)
      return p;
  }
  return end;
}

bool predicate(int n) { return (n & 1) == 0; }

class Predicate {
public:
  bool operator()(int n) const { return (n & 1) == 0; }
};

void countDistinctWordVec(const string &filename) {
  ifstream ifs(filename);
  string curr_word;
  vector<string> collection;
  while (ifs >> curr_word) {
    if (find(collection.begin(), collection.end(), curr_word) ==
        collection.end())
      collection.push_back(curr_word);
  }
  ifs.close();
  cout << "Number of Distinct Words: " << collection.size() << endl;
  printVec(collection);
}

void countDistinctWordSet(const string &filename) {
  ifstream ifs(filename);
  string curr_word;
  set<string> collection;
  while (ifs >> curr_word) {
    if (find(collection.begin(), collection.end(), curr_word) ==
        collection.end())
      collection.insert(curr_word);
  }
  ifs.close();
  cout << "Number of Distinct Words: " << collection.size() << endl;
  for (const string &i : collection) {
    cout << i << " ";
  }
  cout << endl;
}

void countDistinctWordMap(const string &filename) {
  ifstream ifs(filename);
  string curr_word;
  map<string, vector<int>> collection;
  int index = 0;
  while (ifs >> curr_word) {
    collection[curr_word].push_back(index++);
  }
  ifs.close();
  for (const auto &entry : collection) {
    cout << entry.first << " ";
    printVec(entry.second);
  }
}

int main() {
  //
  // Container Basics
  //

  // 1. Print out the vector
  cout << "Task 1:\n";
  vector<int> v{9, 1, 3, 4, 7, 10, 3, 6};
  printVec(v);
  cout << "\n=======\n";

  // 2. Create a list, assign it the values from the vector.
  cout << "Task 2:\n";
  list<int> l(v.begin(), v.end());
  printListRF(l);
  cout << "\n=======\n";

  // 3. Sort the original vector.  Display both the vector and the list
  cout << "Task 3:\n";
  sort(v.begin(), v.end());
  printVec(v);
  printListRF(l);
  cout << "\n=======\n";

  // 4. print every other element of the vector.
  cout << "Task 4:\n";
  for (size_t i = 0; i < v.size(); i += 2) {
    cout << v[i];
  }
  cout << "\n=======\n";

  // 5. Attempt to print every other element of the list using the
  //    same technique.
  cout << "Task 5:\n";
  //    for (size_t i = 0; i < l.size(); i += 2) {
  //        cout << l[i];
  //    }
  cout << "Cannot use index based loop\n";
  cout << "\n=======\n";

  //
  // Iterators
  //

  // 6. Print alternate elements of vector using iterators
  cout << "Task 6:\n";
  for (auto iter = v.begin(); iter < v.end(); iter += 2) {
    cout << *iter;
  }
  cout << "\n=======\n";

  // 7. Print alternate elements of list using iterators
  cout << "Task 7:\n";
  auto iter = l.begin();
  while (iter != l.end()) {
    cout << *iter;
    ++iter;
    if (iter == l.end())
      break;
    ++iter;
  }
  cout << "\n=======\n";

  // 8 Sort the list
  cout << "Task 8:\n";
  l.sort();
  printListRF(l);
  cout << "\n=======\n";

  // 9. Print out every other element of list
  //    using ranged-for
  cout << "Task 9:\n";
  bool skip = false;
  for (const int &i : l) {
    if (!skip)
      cout << i;
    skip = !skip;
  }
  cout << "\n=======\n";

  // 10. Print out every other element of list
  //     using "iterators".
  cout << "Task 10:\n";
  int idx = 0;
  for (list<int>::const_iterator iterator = l.begin(); iterator != l.end();
       ++iterator) {
    if ((idx % 2) == 0) {
      cout << *iterator;
    }
    idx++;
  }
  cout << "\n=======\n";

  // 11.Print the list in task 8 then print every other element using
  // items in the list
  cout << "Task 11:\n";
  printlistAuto(l);
  cout << "\n=======\n";

  // 12.  Write a function find that takes a list and value to search for.
  //      What should we return if not found
  cout << "Task 12:\n";
  {
    list<int>::const_iterator it = findList(l, 3);
    if (it != l.end())
      cout << *it;
    else
      cout << "not found";
  }
  cout << "\n=======\n";

  // 13.  Write a function find that takes a list and value to search for.
  //      What should we return if not found
  cout << "Task 13:\n";
  {
    list<int>::const_iterator it = findList(l, 3);
    if (it != l.end())
      cout << *it;
    else
      cout << "not found";
  }
  cout << "\n=======\n";

  //
  // Generic Algorithms
  //

  // 14. Generic algorithms: find
  cout << "Task 14:\n";
  {
    list<int>::const_iterator it = find(l.begin(), l.end(), 3);
    if (it != l.end())
      cout << *it;
    else
      cout << "not found";
  }
  cout << "\n=======\n";

  // 15. Generic algorithms: find_if
  cout << "Task 15:\n";
  {
    list<int>::const_iterator it = find_if(l.begin(), l.end(), predicate);
    if (it != l.end())
      cout << *it;
    else
      cout << "not found";
  }
  cout << "\n=======\n";

  // 16. Functor
  cout << "Task 16:\n";
  {
    list<int>::const_iterator it = find_if(l.begin(), l.end(), Predicate());
    if (it != l.end())
      cout << *it;
    else
      cout << "not found";
  }
  cout << "\n=======\n";

  // 17. Lambda
  cout << "Task 17:\n";
  {
    list<int>::const_iterator it =
        find_if(l.begin(), l.end(), [](int n) { return (n & 1) == 0; });
    if (it != l.end())
      cout << *it;
    else
      cout << "not found";
  }
  cout << "\n=======\n";

  // 18. Generic algorithms: copy to an array
  cout << "Task 18:\n";
  int *DA = new int[6];
  copy(l.begin(), l.end(), DA);
  for (size_t i = 0; i < 6; ++i) {
    cout << DA[i];
  }
  {
    int *found = find(DA, DA + 6, 3);
    if (found != DA + 6)
      cout << "\nFound in array: " << *found;
    else
      cout << "\nNot found in array";
  }
  delete[] DA;
  cout << "\n=======\n";

  //
  // Templated Functions
  //

  // 19. Implement find as a function for lists
  cout << "Task 19:\n";
  {
    list<int>::const_iterator it = ourFind(l.cbegin(), l.cend(), 3);
    if (it != l.cend())
      cout << *it;
    else
      cout << "not found";
  }
  cout << "\n=======\n";

  // 20. Implement find as a templated function
  cout << "Task 20:\n";
  {
    vector<int>::iterator it = ourFind(v.begin(), v.end(), 3);
    if (it != v.end())
      cout << *it;
    else
      cout << "not found";
  }
  cout << "\n=======\n";

  //
  // Associative collections
  //

  // 21. Using a vector of strings, print a line showing the number
  //     of distinct words and the words themselves.
  cout << "Task 21:\n";
  countDistinctWordVec("pooh-nopunc.txt");
  cout << "=======\n";

  // 22. Repeating previous step, but using the set
  cout << "Task 22:\n";
  countDistinctWordSet("pooh-nopunc.txt");
  cout << "=======\n";

  // 23. Word co-occurence using map
  cout << "Task 23:\n";
  countDistinctWordMap("pooh-nopunc.txt");
  cout << "=======\n";
}

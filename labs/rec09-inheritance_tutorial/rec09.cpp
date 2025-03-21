#include <iostream>
using namespace std;

class PrintedMaterial {
public:
    PrintedMaterial(unsigned num_pages)
    : num_of_pages(num_pages)
    {}
    
    void display_num_pages() const { cout << "Pages: " << num_of_pages << endl; }


private:
    unsigned num_of_pages;
};

class Magazine : public PrintedMaterial {
public:
    Magazine(unsigned num_pages)
    : PrintedMaterial(num_pages)
    {}
private:
};

class Book : public PrintedMaterial {
public:
    Book(unsigned num_pages)
    : PrintedMaterial(num_pages)
    {}
private:
};

class TextBook : public Book {
public:
    TextBook(unsigned num_pages, unsigned num_index_pages)
    : Book(num_pages), num_of_index_pages(num_index_pages) {}

    void display_num_pages() const {
        PrintedMaterial::display_num_pages();
        cout << "Index Pages: " << num_of_index_pages << endl;;
    }

private:
    unsigned num_of_index_pages;
};

class Novel : public Book {
public:
    Novel(unsigned num_pages)
    : Book(num_pages)
    {}
private:
};

// tester/modeler code
int main() {
    TextBook t(5430);
    Novel n(213);
    Magazine m(6);
}
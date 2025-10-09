#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <string>
#include <vector>

using namespace std;

// ---------- Definition of the Member class ----------
// Represents a library member with a unique incremental ID
class Member {
private:
    // ---------- Attributes ----------
    string name;        // Member's name
    int memberid;       // ID assigned to each member
    bool hasbook;       // Indicates if the member currently has a borrowed book
    static int nextid;  // Static counter for generating unique IDs
public:
    Member (string name, bool hasbook);  // Constructor
    void display();                      // Display member information
    int getid() const;                   // Returns member ID
    bool returnhasbook() const;          // Returns whether the member has a book
    void borrowbook();                   // Marks that the member has borrowed a book
    void returnbook();                   // Marks that the member has returned their book
};

// ---------- Definition of the Book class ----------
// Represents a book in the library with title, author, and unique ID
class Book {
private:
    // ---------- Attributes ----------
    string title;       // Book title
    string author;      // Book author
    int bookid;         // ID assigned to each book
    static int nextid;  // Static counter for generating book IDs
    bool borrowed;      // Indicates if the book is borrowed or not
public:
    Book (string title, string author, bool borrowed);  // Constructor
    void display();                        // Display book information
    int getid() const;                     // Returns the book ID
    string gettitle() const;               // Returns the book title
    bool getborrowed() const;              // Returns current borrow status
    void isborrowed(bool b);               // Sets borrow status of the book
};

// ---------- Definition of the Library class ----------
class Library {
public:
    //---------- Definition of vectors ----------
    vector<Book> booklist;
    vector<Member> memberlist;

    void borrow();               // Borrowing function
    void returnb();              // Returning function
    void addmember();            // Add a new member
    void addbook();              // Add a new book
    void showstatus();           // Show current library status
};

#endif
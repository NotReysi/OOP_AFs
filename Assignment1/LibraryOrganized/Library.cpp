#include "Library.hpp"
#include <iostream>
#include <string>

using namespace std;

// ---------- Member class ----------
int Member::nextid = 1;   // Initialize static counter for incremental ID

Member::Member (string name, bool hasbook){
    this -> name = name;
    this -> hasbook = hasbook;
    memberid = nextid++;   // Assigns incremental ID
}

void Member::display(){
    cout << "Name: " << name << "       ID: " << memberid << "      Has a book?: " << (hasbook ? "Yes" : "No") << "\n";
}

int Member::getid() const{
    return memberid;
}

bool Member::returnhasbook() const{
    return hasbook;
}

void Member::borrowbook(){
    hasbook = true;
}

void Member::returnbook(){
    hasbook = false;
}


// ---------- Book class ----------
int Book::nextid = 1;   // Initialize static counter for incremental ID

Book::Book (string title, string author, bool borrowed){
    this -> title = title;
    this -> author = author;
    this -> borrowed = borrowed;
    bookid = nextid++;   // Assigns incremental ID
}

void Book::display(){
    cout << "Title: " << title << "     Author: " << author << "        ID: " << bookid << "        Is borrowed?: " << (borrowed ? "Yes" : "No") << "\n";
}

int Book::getid() const{
    return bookid;
}

string Book::gettitle() const{
    return title;
}
    
bool Book::getborrowed() const{
    return borrowed;
}

void Book::isborrowed(bool b){
    borrowed = b;   // Changes borrow status of the book
}


// ---------- Library class ----------

void Library::borrow(){
    int memberid, bookid;
    int mi = -1;   // Index of member
    int bi = -1;   // Index of book
    cout << "\n----------------------BORROWING----------------------\n";
    cout << "\nEnter the following information:\n";
    cout << "Member's ID: ";
    cin >> memberid;
    cout << "Book's ID: ";
    cin >> bookid;

    // Search for the member by ID
    for (int i = 0; i < memberlist.size(); i++){
        if (memberlist[i].getid() == memberid){
            mi = i;
            break;
        }
    }
    // Search for the book by ID
    for (int i = 0; i < booklist.size(); i++){
        if (booklist[i].getid() == bookid){
            bi = i;
            break;
        }
    }

    // Error handling for invalid IDs
    if (mi == -1){
        cout << "\n############     I'm sorry. I couldn't find the member's ID in the system D:     ############\n";
        return;
    }
        
    if (bi == -1){
        cout << "\n############     I'm sorry. I couldn't find the book's ID in the system D:     ############\n";
        return;
    }

    // Check if book is already borrowed
    if (booklist[bi].getborrowed()){
        cout << "\n############     This book is already borrowed :o     ############\n";
        return;
    }

    // Check if member already has a book
    if (memberlist[mi].returnhasbook()){
        cout << "\n############     This member already have a book :o     ############\n";
        return;
    }

    // Update statuses: book borrowed and member has a book
    booklist[bi].isborrowed(true);
    memberlist[mi].borrowbook();

    cout << "\n----------------------------------------------------\n";
}

void Library::returnb(){
    int memberid, bookid;
    int mi = -1;   // Index of member
    int bi = -1;   // Index of book
    cout << "\n----------------------RETURNING---------------------\n";
    cout << "\nEnter the following information:\n";
    cout << "Member's ID: ";
    cin >> memberid;
    cout << "Book's ID: ";
    cin >> bookid;

    // Search for the member by ID
    for (int i = 0; i < memberlist.size(); i++){
        if (memberlist[i].getid() == memberid){
            mi = i;
            break;
        }
    }
    // Search for the book by ID
    for (int i = 0; i < booklist.size(); i++){
        if (booklist[i].getid() == bookid){
            bi = i;
            break;
        }
    }
        
    // Error handling for invalid IDs
    if (mi == -1){
        cout << "\n############     I'm sorry. I couldn't find the member's ID in the system D:     ############\n";
        return;
    }
        
    if (bi == -1){
        cout << "\n############     I'm sorry. I couldn't find the book's ID in the system D:     ############\n";
        return;
    }

    // Check if book is not borrowed
    if (!booklist[bi].getborrowed()){
        cout << "\n############     This book is not marked as borrowed :o     ############\n";
        return;
    }

    // Check if member has no book to return
    if (!memberlist[mi].returnhasbook()){
        cout << "\n############     This member has no book to return :o     ############\n";
        return;
    }

    // Update statuses: book returned and member no longer has a book
    booklist[bi].isborrowed(false);
    memberlist[mi].returnbook();
    cout << "\n----------------------------------------------------\n";
}

void Library::addmember(){
    string name;
    cout << "\n---------------------NEW MEMBER---------------------\n";
    cout << "Okay! Please enter the following information:\n" << 
            "Name: ";
    getline(cin >> ws,name);
    memberlist.push_back(Member(name,false));   // Adds new member with no book

    cout << "Okay! " << name << " is now part of us\n";
    cout << "\n----------------------------------------------------\n";
}

void Library::addbook(){
    cout << "\n----------------------NEW BOOK----------------------\n";
    string title;
    string author;
    cout << "Okay! Please enter the following information:\n" <<
            "Title: ";
    getline(cin >> ws,title);
    cout << "Author: ";
    getline(cin >> ws,author);
    booklist.push_back(Book(title,author,false));  // Adds new book as available
        
    cout << "Okay! " << title << " from " << author << " is now in our library!\n";
    cout << "\n----------------------------------------------------\n";
}

void Library::showstatus(){
    cout << "\n-----------------------STATUS-----------------------\n" << 
            "Total of members: " << memberlist.size() << 
            "\nTotal of books: " << booklist.size() << 
            "\n\nList of members:\n";
    for (auto& m : memberlist) {
        m.display();   // Print member info
    }
        
    cout << "\nList of books:\n";
    for (auto& b : booklist) {
        b.display();   // Print book info
    }
    cout << "------------------------------------------------------\n";
}
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ---------- Definition of the Member class ----------
class Member {
private:
    //---------- Atributes ----------
    string name;
    int memberid;
    bool hasbook;
    static int nextid;  // Static counter for generating unique IDs
public:
    // Constructor
    Member (string name, bool hasbook){
        this -> name = name;
        this -> hasbook = hasbook;
        memberid = nextid++;   // Assigns incremental ID
    }

    // Display member information
    void display(){
        cout << "Name: " << name << "       ID: " << memberid << "      Has a book?: " << (hasbook ? "Yes" : "No") << "\n";
    }

    // Getters
    int getid() const{
        return memberid;
    }

    bool returnhasbook() const{
        return hasbook;
    }

    // Setters to change the hasbook status
    void borrowbook(){
        hasbook = true;
    }

    void returnbook(){
        hasbook = false;
    }
};
int Member::nextid = 1;   // Initialize static counter for incremental ID

// ---------- Definition of the Book class ----------
class Book {
private:
    //---------- Atributes ----------
    string title;
    string author;
    int bookid;
    static int nextid;   // Static counter for generating unique book IDs
    bool borrowed;

public:
    // Constructor
    Book (string title, string author, bool borrowed){
        this -> title = title;
        this -> author = author;
        this -> borrowed = borrowed;
        bookid = nextid++;   // Assigns incremental ID
    }

    // Display book information
    void display(){
        cout << "Title: " << title << "     Author: " << author << "        ID: " << bookid << "        Is borrowed?: " << (borrowed ? "Yes" : "No") << "\n";
    }

    // Getters
    int getid() const{
        return bookid;
    }

    string gettitle() const{
        return title;
    }
    
    bool getborrowed() const{
        return borrowed;
    }

    // Setter
    void isborrowed(bool b){
        borrowed = b;           // Changes borrow status of the book
    }
};
int Book::nextid = 1;   // Initialize static counter

// ---------- Definition of the Library class ----------
class Library {
public:
    //---------- Definition of vectors ----------
    vector<Book> booklist;
    vector<Member> memberlist;
    
    // ---- Borrowing function ----
    void borrow(){
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

    // ---- Returning function ----
    void returnb(){
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

    // ---- Add a new member ----
    void addmember(){
        string name;
        cout << "\n---------------------NEW MEMBER---------------------\n";
        cout << "Okay! Please enter the following information:\n" << 
                "Name: ";
        getline(cin >> ws,name);
        memberlist.push_back(Member(name,false));   // Adds new member with no book

        cout << "Okay! " << name << " is now part of us\n";
        cout << "\n----------------------------------------------------\n";
    }

    // ---- Add a new book ----
    void addbook(){
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

    // ---- Show current library status ----
    void showstatus(){
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
};

// ---------- Main function ----------
int main () {
    Library lib;   // Create library instance

    // Default books and a member
    lib.booklist.push_back(Book("A flor de piel", "Javier Moro", false));
    lib.booklist.push_back(Book("Primer Plano", "Antonio Malpica", false));
    lib.memberlist.push_back(Member("Orlando", false));

    int selection;
    do {
        cout << "\n                   Tilin Library\n" << 
                "----------------------WELCOME----------------------\n" << 
                "\nPick a number to select any of this options:\n" <<
                "1) Borrow a book.\n" <<
                "2) Return a book.\n" <<
                "3) Register a new member.\n" <<
                "4) Register a new book.\n" <<
                "5) See the library status.\n" << 
                "0) Exit the System.\n";
        cin >> selection;

        // Handle user selection
        switch (selection){
            case 0:{
                cout << "\nHave a good day!!!\n";
                break;
            }
            case 1:{
                lib.borrow();
                break;
            }
            case 2:{
                lib.returnb();
                break;
            }
            case 3:{
                lib.addmember();
                break;
            }
            case 4:{
                lib.addbook();
                break;
            }
            case 5:{
                lib.showstatus();
                break;
            }
            default:{       // Invalid input guard for numbers outside the expected range
                cout << "\n############     Please select a number between 0 and 5  >:(     ############\n";
            }
        }

    } while (selection != 0);   // Repeat until user select exit
    return 0;
}
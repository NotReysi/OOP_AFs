#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Member {
private:
    string name;
    int memberid;
    bool hasbook;
    static int nextid;
public:
    Member (string name, bool hasbook) : name(name), hasbook(hasbook){
        memberid = nextid++;
    }

    void display(){
        cout << "Name: " << name << "       ID: " << memberid << "      Has a book?: " << (hasbook ? "Yes" : "No") << "\n";
    }

    int getid() const{
        return memberid;
    }

    bool returnhasbook() const{
        return hasbook;
    }

    void borrowbook(){
        hasbook = true;
    }

    void returnbook(){
        hasbook = false;
    }
};
int Member::nextid = 1;

class Book {
private:
    string title;
    string author;
    int bookid;
    static int nextid;
    bool borrowed;

public:
    Book (string title, string author, bool borrowed) : title(title), author(author), borrowed(borrowed){
        bookid = nextid++;
    }

    void display(){
        cout << "Title: " << title << "     Author: " << author << "        ID: " << bookid << "        Is borrowed?: " << (borrowed ? "Yes" : "No") << "\n";
    }

    int getid() const{
        return bookid;
    }

    string gettitle() const{
        return title;
    }
    
    bool getborrowed() const{
        return borrowed;
    }

    void isborrowed(bool b){
        borrowed = b;
    }
};
int Book::nextid = 1;

class Library {
public:
    vector<Book> booklist;
    vector<Member> memberlist;
    
    void borrow(){
        int memberid, bookid;
        int mi = -1;
        int bi = -1;
        cout << "\n----------------------BORROWING----------------------\n";
        cout << "\nEnter the following information:\n";
        cout << "Member's ID: ";
        cin >> memberid;
        cout << "Book's ID: ";
        cin >> bookid;

        for (int i = 0; i < memberlist.size(); i++){
            if (memberlist[i].getid() == memberid){
                mi = i;
                break;
            }
        }
        for (int i = 0; i < booklist.size(); i++){
            if (booklist[i].getid() == bookid){
                bi = i;
                break;
            }
        }

        if (mi == -1){
            cout << "\n############     I'm sorry. I couldn't find the member's ID in the system D:     ############\n";
            return;
        }
        
        if (bi == -1){
            cout << "\n############     I'm sorry. I couldn't find the book's ID in the system D:     ############\n";
            return;
        }

        if (booklist[bi].getborrowed()){
            cout << "\n############     This book is already borrowed :o     ############\n";
            return;
        }

        if (memberlist[mi].returnhasbook()){
            cout << "\n############     This member already have a book :o     ############\n";
            return;
        }

        booklist[bi].isborrowed(true);
        memberlist[mi].borrowbook();

        cout << "\n----------------------------------------------------\n";
    }

    void returnb(){
        int memberid, bookid;
        int mi = -1;
        int bi = -1;
        cout << "\n----------------------RETURNING---------------------\n";
        cout << "\nEnter the following information:\n";
        cout << "Member's ID: ";
        cin >> memberid;
        cout << "Book's ID: ";
        cin >> bookid;

        for (int i = 0; i < memberlist.size(); i++){
            if (memberlist[i].getid() == memberid){
                mi = i;
                break;
            }
        }
        for (int i = 0; i < booklist.size(); i++){
            if (booklist[i].getid() == bookid){
                bi = i;
                break;
            }
        }
        
        if (mi == -1){
            cout << "\n############     I'm sorry. I couldn't find the member's ID in the system D:     ############\n";
            return;
        }
        
        if (bi == -1){
            cout << "\n############     I'm sorry. I couldn't find the book's ID in the system D:     ############\n";
            return;
        }

        if (!booklist[bi].getborrowed()){
            cout << "\n############     This book is not marked as borrowed :o     ############\n";
            return;
        }

        if (!memberlist[mi].returnhasbook()){
            cout << "\n############     This member has no book to return :o     ############\n";
            return;
        }

        booklist[bi].isborrowed(false);
        memberlist[mi].returnbook();
        cout << "\n----------------------------------------------------\n";
    }

    void addmember(){
        string name;
        cout << "\n---------------------NEW MEMBER---------------------\n";
        cout << "Okay! Please enter the following information:\n" << 
                "Name: ";
        getline(cin >> ws,name);
        memberlist.push_back(Member(name,false));

        cout << "Okay! " << name << " is now part of us\n";
        cout << "\n----------------------------------------------------\n";

    }

    void addbook(){
        cout << "\n----------------------NEW BOOK----------------------\n";
        string title;
        string author;
        cout << "Okay! Please enter the following information:\n" <<
                "Title: ";
        getline(cin >> ws,title);
        cout << "Author: ";
        getline(cin >> ws,author);
        booklist.push_back(Book(title,author,false));
        
        cout << "Okay! " << title << " from " << author << " is now in our library!\n";
        cout << "\n----------------------------------------------------\n";
    }

    

    void showstatus(){
        cout << "\n-----------------------STATUS-----------------------\n" << 
                "Total of members: " << memberlist.size() << 
                "\nTotal of books: " << booklist.size() << 
                "\n\nList of members:\n";
        for (auto& m : memberlist) {
            m.display();
        }
        
        cout << "\nList of books:\n";
        for (auto& b : booklist) {
            b.display();
        }
        cout << "------------------------------------------------------\n";
    }
};

int main () {
    Library lib;
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
            default:{
                cout << "\n############     Please select a number between 0 and 5  >:(     ############\n";
            }
        }

    } while (selection != 0);
    return 0;
}
/* 
• Define classes for Book, Member, and Library.
• Allow adding new books and members to the library.
• Implement functionality for borrowing and returning books.
• Ensure that a book cannot be borrowed if it is already checked out.
• Display the list of available books and the borrowing status.
• Use appropriate methods and attributes for each class.
*/
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Book {
private:
    string title;
    string author;
    int bookid;
    bool borrowed;

public:
    
};

class Member {
private:
    string name;
    int memberid;
    vector<int> borrowedbooks;
};

class Library {
private:
    int totalbooks;
    int totalmembers;
};

int main () {

    return 0;
}
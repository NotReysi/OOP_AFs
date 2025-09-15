#include "Library.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

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
            default:{
                cout << "\n############     Please select a number between 0 and 5  >:(     ############\n";
            }
        }
    } while (selection != 0);   // Repeat until user select exit
    return 0;
}
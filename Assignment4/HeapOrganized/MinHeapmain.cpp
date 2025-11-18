#include "MinHeap.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ---------- Main function ----------
int main(){
    Schedule task;  // Create heap instance
    int selection;
    do{ // Menu loop
        // Print menu options
        cout << "\n\n----------------------SCHEDULE----------------------\n";
        cout << "\nWhat would you like to do?\n" <<
                "1) Add a Task.\n" << 
                "2) Remove a Task.\n" << 
                "3) See the Agenda.\n" << 
                "0) Exit the System.\n";
        cout << "\nSelection: "; 
        cin >> selection;

        switch(selection){  // Handle selection
            case 0:{        // Exit
                cout << "\nHave a good day!!!\n";
                break;
            }
            case 1:{        // Add Task
                int priority;
                string description;
                cout << "\n----------------------NEW TASK----------------------\n";
                cout << "\nEnter the new Task: ";
                getline(cin >> ws, description);    // Read full line (skip whitespace)
                cout << "Select the task priority:\n" <<
                        "1) Due Today\n" <<
                        "2) Due Tomorrow\n" <<
                        "3 -> 7) Due this week\n" <<
                        "8 -> ...) Other priority\n";
                cout << "\nPriority: ";
                cin >> priority;
                cin.ignore();   // Clear newline from input
                task.insert(priority, description); // Call heap insert
                cout << "\n----------------------------------------------------\n";
                break;
            }   
            case 2:{        // Remove Task
                cout << "\n---------------------REMOVE TASK--------------------\n";
                if (task.isEmpty()){    // Check if empty
                    cout << "\nThere is nothing in the Schedule D:\n";
                    cout << "\n----------------------------------------------------\n";
                    break;
                }
                else{
                    Task removed = task.extract();  // Call heap extract
                    cout << "\n...Removing Max-Priority Task...\n";
                    cout << "\nTask -> ";
                    removed.display();  // Show what was removed
                    cout << "Successfully removed :D\n";
                    cout << "\n----------------------------------------------------\n";
                    break;
                }
                
            }
            case 3:{        // Display Agenda
                cout << "\n-----------------------AGENDA-----------------------\n";
                if (task.isEmpty()){
                    cout << "\nThere is nothing in the Schedule D:\n";
                    cout << "\n----------------------------------------------------\n";
                    break;
                }
                else{
                    task.display();
                    cout << "\n----------------------------------------------------\n";
                    break;
                }
            }
            default:{       // Invalid input guard for numbers outside the expected range
                cout << "\n############     Please select a number between 0 and 4  >:(     ############\n";
            }
        }
    }while(selection != 0); // Repeat until user selects 0

    return 0;
}
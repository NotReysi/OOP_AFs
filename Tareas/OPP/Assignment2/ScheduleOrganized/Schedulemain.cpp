#include "Schedule.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ---------- Main function ----------
int main (){
    Queue task;          // Instance managing all tasks
    int selection;
    do{
        cout << "\n----------------------SCHEDULE----------------------\n";
        cout << "\nWhat would you like to do?\n" <<
                "1) Add a Task.\n" << 
                "2) Remove a Task.\n" << 
                "3) See the Agenda.\n" << 
                "4) Clear the Agenda.\n" << 
                "0) Exit the System.\n";
        cin >> selection;

        // Handle user selection
        switch (selection){
            case 0:{
                cout << "\nHave a good day!!!\n";
                break;
            }
            case 1:{
                task.addtask();
                break;
            }
            case 2:{
                task.removetask();
                break;
            }
            case 3:{
                task.agenda();
                break;
            }
            case 4:{
                task.clear();
                break;
            }
            default:{       // Invalid input guard for numbers outside the expected range
                cout << "\n############     Please select a number between 0 and 4  >:(     ############\n";
            }
        }
    } while (selection != 0);  // Repeat until user select exit
    return 0;
}
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ---------- Definition of the Task class ----------
class Task{
private:
    string taskname;   // Task description
    float time;        // Estimated time in minutes
    int tasknum;       // Sequential number assigned to each task
    static int nextnum; // Static counter to assign task numbers
public:
    // Constructor
    Task (string taskname, float time){
        this -> taskname = taskname;
        this -> time = time;
        tasknum = nextnum++;  // Assign number and then increment the counter
    };

    // Display Task information
    void display() const{
        cout << tasknum << "    " << taskname << "    Time: " << time << " minutes \n";
    }

    // Return task name
    string getname() const{
        return taskname;
    }

    // Return estimated time in minutes
    float gettime() const{
        return time;
    }
};
int Task::nextnum = 1;  // Initialize static counter for Task numbering

// ---------- Definition of the Queue class ----------
class Queue{
private:   
    //---------- Definition of vector ----------
    vector<Task> list;
public:
    // ---- Add a new task ----
    void addtask(){
        string name;
        float time;
        cout << "\n----------------------NEW TASK----------------------\n";
        cout << "\nWhat are you going to schedule?: ";
        getline(cin >> ws,name);          // Read a full line (skips leading whitespace)
        cout << "What is the estimated time in minutes?: ";
        cin >> time;                      // Read numeric estimate
        cin.ignore();                     // Discard the leftover newline to keep next getline clean
        list.push_back(Task(name,time));  // Append new Task to the vector
        cout << "\n----------------------------------------------------\n";
    }

    // ---- Remove a task ----
    void removetask(){
        int num;
        cout << "\n---------------------REMOVE TASK--------------------\n";
        if (list.empty()){
            cout << "\n############  There is no task to remove :o  ############\n";
            return;                       // Early exit if there are no tasks
        }

        cout << "\n Enter the task number you want to remove: ";
        cin >> num;                       // Read the 1-based task number
        cin.ignore();                     // Clear newline from input buffer
        
        if (num>0 && num<=list.size()){
            // Convert from 1-based input to 0-based index and erase
            list.erase(list.begin()+(num-1));
            cout << "\nTask " << num << " successfully removed :D";
            cout << "\n----------------------------------------------------\n";
        }
        else{
            // Guard against out-of-range numbers
            cout << "\nPlease enter a number between 1 and " << list.size() << "\n";
            return;
        }
    }

    // ---- Display all the agenda ----
    void agenda() const{
        cout << "\n-----------------------AGENDA-----------------------\n";
        if (list.empty()){
            cout << "\n############  There is no task to do :)  ############\n";
            return;                       // Nothing to list
        }

        // Iterate by index to show each task in insertion order
        for (int i = 0; i < list.size(); i++){
            list[i].display();            // Uses Task::display() to print each task
        }
        cout << "\n----------------------------------------------------\n";
    }

    // ---- Clear all tasks from the agenda ----
    void clear(){
        cout << "\n----------------------------------------------------\n";
        if (list.empty()){
            cout << "\n############  There is no task to clear  ############\n";
            return;                       // Already empty
        }

        list.clear();                     // Erase all elements from the vector
        // Visual separator to confirm the clear action
        cout << "\n####################################################\n";
        cout << "\n================ CLEANING THE AGENDA ===============\n";
        cout << "\n####################################################\n";
        cout << "\n----------------------------------------------------\n";
    }
};


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
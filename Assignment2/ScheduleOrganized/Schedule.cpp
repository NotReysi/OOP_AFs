#include "Schedule.hpp"
#include <iostream>
#include <string>

using namespace std;

// ---------- Task class ----------
int Task::nextnum = 1;  // Initialize static counter for Task numbering
    // Constructor
Task::Task (string taskname, float time){
    this -> taskname = taskname;
    this -> time = time;
    tasknum = nextnum++;  // Assign number and then increment the counter
}

void Task::display() const{
    cout << tasknum << "    " << taskname << "    Time: " << time << " minutes \n";
}

string Task::getname() const{
    return taskname;
}

float Task::gettime() const{
    return time;
}


// ---------- Queue class ----------

void Queue::addtask(){
    string name;
    float time;
    cout << "\n----------------------NEW TASK----------------------\n";
    cout << "\nWhat are you going to schedule?: ";
    getline(cin >> ws,name);          // Read a full line (skips leading whitespace)
    cout << "What is the estimated time in minutes?: ";
    cin >> time;                      // Read estimated time in minutes
    cin.ignore();                     // Clear newline from input buffer
    list.push_back(Task(name,time));  // Append new Task to the vector
    cout << "\n----------------------------------------------------\n";
}

void Queue::removetask(){
    int num;
    cout << "\n---------------------REMOVE TASK--------------------\n";
    if (list.empty()){
        cout << "\n############  There is no task to remove :o  ############\n";
        return;                       // Early exit if there are no tasks
    }

    cout << "\n Enter the task number you want to remove: ";
    cin >> num;                       // Read the task number
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

void Queue::agenda() const{
    cout << "\n-----------------------AGENDA-----------------------\n";
    if (list.empty()){
        cout << "\n############  There is no task to do :)  ############\n";
        return;                       // Early exit if nothing to list
    }

    // Displays each task in the list
    for (int i = 0; i < list.size(); i++){
        list[i].display();
    }
    cout << "\n----------------------------------------------------\n";
}

void Queue::clear(){
    cout << "\n----------------------------------------------------\n";
    if (list.empty()){
        cout << "\n############  There is no task to clear  ############\n";
        return;                       // Early exit if already empty
    }

    list.clear();                     // Erase all elements from the vector
    cout << "\n####################################################\n";
    cout << "\n================ CLEANING THE AGENDA ===============\n";
    cout << "\n####################################################\n";
    cout << "\n----------------------------------------------------\n";
}
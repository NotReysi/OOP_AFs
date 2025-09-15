#ifndef TASKQUEUE_HPP
#define TASKQUEUE_HPP

#include <string>
#include <vector>

using namespace std;

// ---------- Definition of the Task class ----------
// Represents a single scheduled task with a name and time
class Task{
private:
    string taskname;    // Task description
    float time;         // Estimated time in minutes
    int tasknum;        // Sequential number assigned to each task
    static int nextnum; // Static counter to assign task numbers
public:
    Task (string taskname, float time); // Constructor
    void display() const;               // Display Task information
    string getname() const;             // Return task name
    float gettime() const;              // Return estimated time in minutes
};

// ---------- Definition of the Queue class ----------
// Manages a list of Task
class Queue{
private:   
    //---------- Definition of vector ----------
    vector<Task> list;
public:
    void addtask();     // Add a new task
    void removetask();  // Remove a task
    void agenda() const;// Display all the agenda
    void clear();       //Clear all tasks from the agenda
};

#endif
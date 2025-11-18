#ifndef MINHEAP_HPP
#define MINHEAP_HPP

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ---------- Definition of the Task structure ----------
struct Task{
    //---------- Atributes ----------
    int priority;       // Lower number means higher priority
    string description; // Description of the task
    Task(int priority, string description); // Constructor
    void display();     // Display Task information
    int getPriority();  // Return Priority
};

// ---------- Definition of the Schedule class ----------
class Schedule{
    private:
        vector<Task> heap;          // Definition of the vector that stores the elements 
        void heapify_Up(int i);     // -- Move a node UP to its correct spot after insert --
        void heapify_Down(int i);   // -- Move a node DOWN to its correct spot after extract --
    public:
        void insert(int priority, string description);  // ---- Add a new task ----
        bool isEmpty();     // -- Check if heap is empty --
        Task extract();     // ---- Remove a task ----
        void display();     // ---- Display all the agenda ----
};

#endif
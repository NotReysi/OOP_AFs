#include "MinHeap.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ---------- Task structure ----------
Task::Task(int priority, string description){
        this->priority = priority;
        this->description = description;
}

void Task::display(){
    cout << priority << "  -  " << description << endl;
}

int Task::getPriority(){
    return priority;
}

// ---------- Schedule class ----------
void Schedule::heapify_Up(int i){
    // While not at the root AND parent is bigger than me...
    while (i > 0 && heap[(i-1)/2].getPriority() > heap[i].getPriority()){
        // ...swap me with my parent
        swap(heap[(i-1)/2], heap[i]);
        i = (i-1)/2;    // Move up to the parent's index
    }
}

void Schedule::heapify_Down(int i){
    int n = heap.size();    // Total number of elements
    // While the node has at least one child (left child)
    while (2*i + 1 < n){
        int j = 2*i + 1;    // Get left child index
        // If a right child exists AND it's smaller than the left...
        if (j + 1 < n && heap[j+1].getPriority() < heap[j].getPriority()){
            j++;    // ...then 'j' becomes the index of the right child
        }
        // 'j' is now the index of the SMALLEST child
        // If I am already smaller than my smallest child...
        if (heap[i].getPriority() <= heap[j].getPriority()){
            break;  // ...my position is correct. Stop.
        }
        // Swap me with my smallest child
        swap(heap[i], heap[j]);
        i = j;  // Move down to the child's index and repeat
    }
}

void Schedule::insert(int priority, string description){
    heap.push_back(Task(priority, description));    // Add task to the very end of the vector
    heapify_Up(heap.size()-1);                      // Bubble it up to its correct position
}

bool Schedule::isEmpty(){
    return heap.empty();
}

Task Schedule::extract(){
    Task minPriority = heap[0]; // Save the root (min value) to return later
    heap[0] = heap.back();      // Move the LAST element to the root
    heap.pop_back();            // Remove the last element (which is now duplicated at the root)
    heapify_Down(0);            // Bubble the new root down to its correct spot
    return minPriority;         // Return the task we saved
}

void Schedule::display(){
    for(int i = 0; i < heap.size(); i++){
        heap[i].display();
    }
}
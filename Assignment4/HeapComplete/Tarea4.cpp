#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ---------- Definition of the Task structure ----------
struct Task{
    //---------- Atributes ----------
    int priority;       // Lower number means higher priority
    string description; // Description of the task
    
    // Constructor
    Task(int priority, string description){
        this->priority = priority;
        this->description = description;
    }

    // Display Task information
    void display(){
        cout << priority << "  -  " << description << endl;
    }

    // Return Priority
    int getPriority(){
        return priority;
    }
};

// ---------- Definition of the Schedule class ----------
class Schedule{
    private:
        vector<Task> heap;  // Definition of the vector that stores the elements

        // -- Move a node UP to its correct spot after insert --
        void heapify_Up(int i){
            // While not at the root AND parent is bigger than me...
            while (i > 0 && heap[(i-1)/2].getPriority() > heap[i].getPriority()){
                // ...swap me with my parent
                swap(heap[(i-1)/2], heap[i]);
                i = (i-1)/2;    // Move up to the parent's index
            }
        }

        // -- Move a node DOWN to its correct spot after extract --
        void heapify_Down(int i){
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

    // --- Public Interface ---
    public:
        // ---- Add a new task ----
        void insert(int priority, string description){
            heap.push_back(Task(priority, description));    // Add task to the very end of the vector
            heapify_Up(heap.size()-1);                      // Bubble it up to its correct position
        }

        // -- Check if heap is empty --
        bool isEmpty(){
            return heap.empty();
        }

        // ---- Remove a task ----
        Task extract(){
            Task minPriority = heap[0]; // Save the root (min value) to return later
            heap[0] = heap.back();      // Move the LAST element to the root
            heap.pop_back();            // Remove the last element (which is now duplicated at the root)
            heapify_Down(0);            // Bubble the new root down to its correct spot
            return minPriority;         // Return the task we saved
        }

        // ---- Display all the agenda ----
        void display(){
            for(int i = 0; i < heap.size(); i++){
                heap[i].display();
            }
        }
};

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
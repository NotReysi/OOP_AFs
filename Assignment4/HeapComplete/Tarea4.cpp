#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Task{
    int priority;
    string description;
    
    Task(int priority, string description){
        this->priority = priority;
        this->description = description;
    }
    void display(){
        cout << priority << "  -  " << description << endl;
    }

    int getPriority(){
        return priority;
    }
};

class Schedule{
    private:
        vector<Task> heap;

        void heapify_Up(int i){
            while (i > 0 && heap[(i-1)/2].getPriority() > heap[i].getPriority()){
                swap(heap[(i-1)/2], heap[i]);
                i = (i-1)/2;
            }
        }

        void heapify_Down(int i){
            int n = heap.size();

            while (2*i + 1 < n){
                int j = 2*i + 1;
                if (j + 1 < n && heap[j+1].getPriority() < heap[j].getPriority()){
                    j++;
                }
                if (heap[i].getPriority() <= heap[j].getPriority()){
                    break;
                }

                swap(heap[i], heap[j]);
                i = j;
            }
        }

    public:
        void insert(int priority, string description){
            heap.push_back(Task(priority, description));
            heapify_Up(heap.size()-1);
        }

        bool isEmpty(){
            return heap.empty();
        }

        Task extract(){
            Task minPriority = heap[0];
            heap[0] = heap.back();
            heap.pop_back();
            heapify_Down(0);
            return minPriority;
        }

        void display(){
            for(int i = 0; i < heap.size(); i++){
                heap[i].display();
            }
        }
};

int main(){
    Schedule task;
    int selection;
    do{
        cout << "\n\n----------------------SCHEDULE----------------------\n";
        cout << "\nWhat would you like to do?\n" <<
                "1) Add a Task.\n" << 
                "2) Remove a Task.\n" << 
                "3) See the Agenda.\n" << 
                "0) Exit the System.\n";
        cout << "\nSelection: "; 
        cin >> selection;

        switch(selection){
            case 0:{
                cout << "\nHave a good day!!!\n";
                break;
            }
            case 1:{
                int priority;
                string description;
                cout << "\n----------------------NEW TASK----------------------\n";
                cout << "\nEnter the new Task: ";
                getline(cin >> ws, description);
                cout << "Select the task priority:\n" <<
                        "1) Due Today\n" <<
                        "2) Due Tomorrow\n" <<
                        "3 -> 7) Due this week\n" <<
                        "8 -> ...) Other priority\n";
                cout << "\nPriority: ";
                cin >> priority;
                cin.ignore();
                task.insert(priority, description);
                cout << "\n----------------------------------------------------\n";
                break;
            }
            case 2:{
                cout << "\n---------------------REMOVE TASK--------------------\n";
                if (task.isEmpty()){
                    cout << "\nThere is nothing in the Schedule D:\n";
                    cout << "\n----------------------------------------------------\n";
                    break;
                }
                else{
                    Task removed = task.extract();
                    cout << "\n...Removing Max-Priority Task...\n";
                    cout << "\nTask -> ";
                    removed.display();
                    cout << "Successfully removed :D\n";
                    cout << "\n----------------------------------------------------\n";
                    break;
                }
                
            }
            case 3:{
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
    }while(selection != 0);

    return 0;
}
#include "AVLTree.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iterator>

using namespace std;

// ---------- Main function ----------
int main(){
    Tree tree;  // Create tree instance

    // Menu variables
    int selection;
    double val;

    do{ // Menu loop
        // Print menu options
        cout << "\n                   Little Garden\n"<<
                "----------------------WELCOME----------------------\n" <<
                "\nPick a number to select any of this options:\n" <<
                "1) Insert a new number.\n" <<
                "2) Search a number.\n" <<
                "3) Delete a number.\n" <<
                "4) See the tree in order.\n" <<
                "5) Merge to another tree.\n" <<
                "0) Exit the system\n";
        cout << "\nSelection: "; 
        cin >> selection;

        switch (selection){     // Handle selection
            case 0:{            // Exit
                cout << "\nHave a good day!!!\n";
                cout << "\n=====================    CLOSING SYSTEM    =====================\n";
                break;
            }
            case 1:{            // Insert
                cout << "\n----------------------NEW VALUE----------------------\n";
                cout << "\nPlease enter the value: ";
                cin >> val;

                tree.insert(val);
                cout << "\n-----------------------------------------------------\n";
                break;
            }
            case 2:{            // Search
                cout << "\n------------------------SEARCH-----------------------\n";
                cout << "Enter the value you want to search: ";
                cin >> val;
                cout << "\n...Searching...\n";
                if (tree.search(val)){
                    cout << val << " exists in the Tree :D\n";
                }
                else{
                    cout << val << " does not exist in the Tree D:\n";
                }
                cout << "\n-----------------------------------------------------\n";
                break;
            }
            case 3:{            // Delete
                cout << "\n--------------------DELETE VALUES--------------------\n";
                cout << "Enter the value you want to errase: ";
                cin >> val;
                if (!tree.search(val)){     // Check if value exists
                    cout << val << " does not exist in the Tree D:\n";
                }
                else {
                    tree.erase(val);
                    cout << "\n...Deleting value...\n";
                }
                cout << "\n-----------------------------------------------------\n";
                break;
            }
            case 4:{            // Display
                cout << "\n---------------------INSIDE TREE---------------------\n";
                cout << "Tree inorder: " << endl;
                cout << "   ";
                tree.inorder();
                cout << "\nTree preorder: " << endl;
                cout << "   ";
                tree.preorder();
                cout << "\nTree postorder: " << endl;
                cout << "   ";
                tree.postorder();
                cout << "\n-----------------------------------------------------\n";
                break;
            }
            case 5:{            // Merge
                cout << "\n-----------------------MERGING-----------------------\n";
                Tree otherTree; // Create a temporary tree
                int amount;
                int merge_selection;
                cout << "\nPlease enter the amount of values: ";
                cin >> amount;

                // Fill the temp tree
                for (int i = 0; i < amount; i++){
                    cout << "Value " << i + 1 << " : ";
                    cin >> val;
                    otherTree.insert(val);
                }

                // Confirm the temp tree
                cout << "\nThanks, this is the Tree inorder about to merge: " << endl;
                cout << "   ";
                otherTree.inorder();

                cout << "\nIs it okay to continue?\n" <<
                        "1) Yes\n" <<
                        "2) No\n";
                cout << "Selection: ";
                cin >> merge_selection;

                // Merge Trees
                if (merge_selection == 1){
                    cout << "\n...Merging Trees...\n";
                    tree.merge(otherTree);
                    cout << "\nTrees merged :D\n";
                    cout << "\n-----------------------------------------------------\n";
                    break;
                }
                else if(merge_selection == 2){
                    cout << "\nOkay, try again.\n";
                    cout << "\n-----------------------------------------------------\n";
                    break;
                }
                else{
                    cout << "\n############     Please select a number between 1 and 2  >:(     ############\n";
                    cout << "\nTry again.\n";
                    cout << "\n-----------------------------------------------------\n";
                    break;
                }
                cout << "\n-----------------------------------------------------\n";
                break;
            }
            default:{       // Invalid input guard for numbers outside the expected range
                cout << "\n############     Please select a number between 0 and 5  >:(     ############\n";
            }
        }
    }while(selection != 0); // Repeat until user selects 0

    return 0;
}

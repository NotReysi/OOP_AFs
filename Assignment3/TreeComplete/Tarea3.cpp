#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iterator>

using namespace std;

//Defined a global constant "e" (epsilon) to compare double values
//This helps to get rid of the imprecision
const double e = 1e-9;

// ---------- Definition of the Node structure ----------
struct Node{
    //---------- Atributes ----------
    double value;  // The value stored in the node
    int height;    // The height of the subtree rooted at this node
    Node* left;    // Pointer to the left child
    Node* right;   // Pointer to the right child
    // Constructor
    Node(double val){
        value = val;
        height = 1;
        left = nullptr;
        right = nullptr;
    }
};

// ---------- Definition of the Tree class ----------
class Tree{
    private:
        Node* root; // The main root of the tree

        // -- Get height of a node --
        int getHeight(Node* node){
            if(node == nullptr){
                return 0;
            }
            else{
                return node->height;
            }
        }
        
        // -- Get Balance Factor (FE) --
        int getFE(Node* node){
            if(node == nullptr){
                return 0;
            }
            else{
                return getHeight(node->left) - getHeight(node->right);
            }
        }

        // -- Performs a right rotation --
        Node* rightRotate(Node* y){
            Node* x = y->left;
            Node* aux = x->right;

            // Perform rotation
            x->right = y;
            y->left = aux;  // 'aux' becomes the left child of 'y'

            // Update heights
            x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
            y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
            return x;
        }

        // -- Performs a left rotation --
        Node* leftRotate(Node* x){
            Node* y = x->right;
            Node* aux = y->left;

            // Perform rotation
            y->left = x;
            x->right = aux; // 'aux' becomes the right child of 'x'

            // Update heights
            x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
            y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
            return y;
        }

        // -- Recursive function to insert a node -- 
        Node* insert(Node* node, double value){
            if (node == nullptr){   // Find leaf position and insert
                return new Node(value);
            }

            if(abs(value - node->value) < e){   // Check for duplicates
                return node;
            }
            else if (value < node->value){  // Go left or right
                node->left = insert(node->left, value);
            }
            else {
                node->right = insert(node->right, value);
            }
            
            // Update height of this ancestor node
            node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
            int balance = getFE(node);  // Get balance factor

            // -- Rebalance if needed (4 cases) -- 
            if (balance > 1 && getFE(node->left) >= 0){     // Left-Left Case
                return rightRotate(node);
            }
            if (balance < -1 && getFE(node->right) <= 0){   // Right-Right Case
                return leftRotate(node);
            }
            if (balance > 1 && getFE(node->left) < 0){      // Left-Right Case
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
            if (balance < -1 && getFE(node->right) > 0){    // Right-Left Case
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }

            return node;
        }

        // -- Recursive function to search a node -- 
        Node* search(Node* node, double value){
            if (node == nullptr){               // Not found
                return nullptr;
            }
            if(abs(value - node->value) < e){   // Found
                return node;
            }
            else if (value < node->value){      // Go left
                return search(node->left, value);
            }
            else {                              // Go right
                return search(node->right, value);
            }
        }

        // -- Recursive function to erase a node -- 
        Node* erase(Node* node, double value){
            if (node == nullptr){   // Find the node
                return nullptr;
            }
            
            if (value < node->value){
                node->left = erase(node->left, value);
            }
            else if (value > node->value){
                node->right = erase(node->right, value);
            }
            // Node found, start deletion logic
            else if(abs(value - node->value) < e){
                // Case 1: No children (leaf node)
                if (node->left == nullptr && node->right == nullptr){
                    delete node;
                    return nullptr;
                }
                // Case 2: Two children
                else if(node->left != nullptr && node->right != nullptr){
                    // Find smallest node in right subtree
                    Node* current = node->right;
                    while (current->left != nullptr) {
                        current = current->left;
                    }
                    node->value = current->value;   // Copy successor's value
                    node->right = erase(node->right, current->value);  // Delete the successor from the right subtree
                }
                // Case 3: One child
                else{
                    // Get the single child
                    if (node->left != nullptr){
                        Node* temp = node->left;
                        delete node;
                        return temp;    // Return child to parent
                    }
                    else{
                        Node* temp = node->right;
                        delete node;
                        return temp;    // Return child to parent
                    }
                }
            }
            
            // Rebalance (Same as insert function)
            if (node == nullptr){
                return nullptr;
            }

            node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
            int balance = getFE(node);

            if (balance > 1 && getFE(node->left) >= 0){
                return rightRotate(node);
            }
            if (balance < -1 && getFE(node->right) <= 0){
                return leftRotate(node);
            }
            if (balance > 1 && getFE(node->left) < 0){
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
            if (balance < -1 && getFE(node->right) > 0){
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }

            return node;
        }
    
        // -- Inorder Traversal (L, Root, R) --
        void inorder(Node* node){
            if (node == nullptr){
                return;
            }
            else{
                inorder(node->left);
                cout << node->value << "  ";
                inorder(node->right);
            }
        }
        
        // -- Preorder Traversal (Root, L, R) --
        void preorder(Node*node){
            if (node == nullptr){
                return;
            }
            else{
                cout << node->value << "  ";
                preorder(node->left);
                preorder(node->right);
            }
        }

        // -- Postorder Traversal (L, R, Root) --
        void postorder(Node* node){
            if (node == nullptr){
                return;
            }
            else{
                postorder(node->left);
                postorder(node->right);
                cout << node->value << "  ";
            }
        }
        
        // -- Destroy tree (free memory) --
        void destroy(Node* node){
            if (node == nullptr){
                return;
            }
            else{
                destroy(node->left);
                destroy(node->right);
                delete node;    // Delete after children
            }
        }

        // -- Convert the Tree to a vector --
        void to_vector(Node* node, vector<double>& current_tree){
            if (node == nullptr){
                return;
            }
            else{
                to_vector(node->left, current_tree);
                current_tree.push_back(node->value);
                to_vector(node->right, current_tree);
            }
        }

        // -- Build a tree from a vector --
        Node* from_vector(const vector<double>& vec, int start, int end){
            if (start > end){
                return nullptr;
            }
            int mid = start + (end - start) / 2;    // Find middle
            Node* node = new Node(vec[mid]);        // Middle is root

            // Build subtrees
            node->left = from_vector(vec, start, mid - 1);  
            node->right = from_vector(vec, mid + 1, end);

            // Update height
            node->height = 1 + max(getHeight(node->left), getHeight(node->right));

            return node;
        }
    
    // --- Public Interface ---
    public:
        // Constructor
        Tree(){
            root = nullptr;
        }
        
        // Destructor
        ~Tree(){
            destroy(root);
        }

        // -- Public insert --
        void insert(double value){
            root = insert(root, value);
        }

        // -- Public inorder --
        void inorder(){
            inorder(root);
            cout << endl;
        }

        // -- Public preorder --
        void preorder(){
            preorder(root);
            cout << endl;
        }

        // -- Public postorder --
        void postorder(){
            postorder(root);
            cout << endl;
        }

        // -- Public search --
        bool search(double value){
            return search(root, value) != nullptr;  // Return true if found
        }

        // -- Public erase --
        void erase(double value){
            root = erase(root, value);
        }

        // -- Merge two trees --
        void merge(Tree& otherTree){
            // Save this tree to vec1
            vector<double> vec1;
            to_vector(this->root, vec1);

            // Save other tree to vec2
            vector<double> vec2;
            to_vector(otherTree.root, vec2);

            // Merge sorted vectors
            vector<double> merged;
            std::merge(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), back_inserter(merged));

            // Destroy and rebuild this tree
            destroy(this->root);
            this->root = from_vector(merged, 0, merged.size() - 1);

            // Empty the other tree
            otherTree.destroy(otherTree.root);
            otherTree.root = nullptr;
        }
};

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

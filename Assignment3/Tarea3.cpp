#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iterator>

using namespace std;

const double e = 1e-9;

struct Node{
    double value;
    int height;
    Node* left;
    Node* right;
    Node(double val){
        value = val;
        height = 1;
        left = nullptr;
        right = nullptr;
    }
};

class Tree{
    private:
        Node* root;

        int getHeight(Node* node){
            if(node == nullptr){
                return 0;
            }
            else{
                return node->height;
            }
        }

        int getFE(Node* node){
            if(node == nullptr){
                return 0;
            }
            else{
                return getHeight(node->left) - getHeight(node->right);
            }
        }

        Node* rightRotate(Node* y){
            Node* x = y->left;
            Node* aux = x->right;
            x->right = y;
            y->left = aux;

            x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
            y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
            return x;
        }

        Node* leftRotate(Node* x){
            Node* y = x->right;
            Node* aux = y->left;
            y->left = x;
            x->right = aux;

            x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
            y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
            return y;
        }

        Node* insert(Node* node, double value){
            if (node == nullptr){
                return new Node(value);
            }

            if(abs(value - node->value) < e){
                return node;
            }
            else if (value < node->value){
                node->left = insert(node->left, value);
            }
            else {
                node->right = insert(node->right, value);
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

        void destroy(Node* node){
            if (node == nullptr){
                return;
            }
            else{
                destroy(node->left);
                destroy(node->right);
                delete node;
            }
        }

        Node* search(Node* node, double value){
            if (node == nullptr){
                return nullptr;
            }
            if(abs(value - node->value) < e){
                return node;
            }
            else if (value < node->value){
                return search(node->left, value);
            }
            else {
                return search(node->right, value);
            }
        }

        Node* errase(Node* node, double value){
            if (node == nullptr){
                return nullptr;
            }
            
            if (value < node->value){
                node->left = errase(node->left, value);
            }
            else if (value > node->value){
                node->right = errase(node->right, value);
            }
            else if(abs(value - node->value) < e){
                if (node->left == nullptr && node->right == nullptr){
                    delete node;
                    return nullptr;
                }
                else if(node->left != nullptr && node->right != nullptr){
                    Node* current = node->right;
                    while (current->left != nullptr) {
                        current = current->left;
                    }
                    node->value = current->value;
                    node->right = errase(node->right, current->value);
                }
                else{
                    if (node->left != nullptr){
                        Node* temp = node->left;
                        delete node;
                        return temp;
                    }
                    else{
                        Node* temp = node->right;
                        delete node;
                        return temp;
                    }
                }
            }
            
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

        Node* from_vector(const vector<double>& vec, int start, int end){
            if (start > end){
                return nullptr;
            }
            int mid = start + (end - start) / 2;
            Node* node = new Node(vec[mid]);

            node->left = from_vector(vec, start, mid - 1);
            node->right = from_vector(vec, mid + 1, end);

            node->height = 1 + max(getHeight(node->left), getHeight(node->right));

            return node;
        }

    public:
        Tree(){
            root = nullptr;
        }
        
        ~Tree(){
            destroy(root);
        }

        void insert(double value){
            root = insert(root, value);
        }

        void inorder(){
            inorder(root);
            cout << endl;
        }

        void preorder(){
            preorder(root);
            cout << endl;
        }

        void postorder(){
            postorder(root);
            cout << endl;
        }

        bool search(double value){
            return search(root, value) != nullptr;
        }

        void errase(double value){
            root = errase(root, value);
        }

        void merge(Tree& otherTree){
            vector<double> vec1;
            to_vector(this->root, vec1);

            vector<double> vec2;
            to_vector(otherTree.root, vec2);

            vector<double> merged;
            std::merge(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), back_inserter(merged));

            destroy(this->root);

            this->root = from_vector(merged, 0, merged.size() - 1);

            otherTree.destroy(otherTree.root);
            otherTree.root = nullptr;
        }
};

int main(){
    Tree tree;

    tree.insert(15);
    tree.insert(0.5);
    tree.insert(5);
    tree.insert(1.32);
    tree.insert(7.3);
    tree.insert(0.0000003);

    int selection;
    double val;

    do{
        cout << "\n                   Little Garden\n"<<
                "----------------------WELCOME----------------------\n" <<
                "\nPick a number to select any of this options:\n" <<
                "1) Insert a new number.\n" <<
                "2) Search a number.\n" <<
                "3) Delete a number.\n" <<
                "4) See the tree in order.\n" <<
                "5) Merge to another tree.\n" <<
                "0) Exit the system\n";
        cout << "Selection: "; 
        cin >> selection;

        switch (selection){
            case 0:{
                cout << "\nHave a good day!!!\n";
                cout << "\n=====================    CLOSING SYSTEM    =====================\n";
                break;
            }
            case 1:{
                cout << "\n----------------------NEW VALUE----------------------\n";
                cout << "\nPlease enter the value: ";
                cin >> val;

                tree.insert(val);
                break;
            }
            case 2:{
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
                break;
            }
            case 3:{
                cout << "\n--------------------DELETE VALUES--------------------\n";
                cout << "Enter the value you want to errase: ";
                cin >> val;
                if (!tree.search(val)){
                    cout << val << " does not exist in the Tree D:\n";
                }
                else {
                    tree.errase(val);
                    cout << "\n...Deleting value...\n";
                }
                break;
            }
            case 4:{
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
                break;
            }
            case 5:{
                cout << "\n-----------------------MERGING-----------------------\n";
                Tree otherTree;
                int amount;
                int merge_selection;
                cout << "\nPlease enter the amount of values: ";
                cin >> amount;

                for (int i = 0; i < amount; i++){
                    cout << "Value " << i + 1 << " : ";
                    cin >> val;
                    otherTree.insert(val);
                }

                cout << "\nThanks, this is the Tree inorder about to merge: " << endl;
                cout << "   ";
                otherTree.inorder();

                cout << "\nIs it okay to continue?\n" <<
                        "1) Yes\n" <<
                        "2) No\n";
                cout << "Selection: ";
                cin >> merge_selection;

                if (merge_selection == 1){
                    cout << "\n...Merging Trees...\n";
                    tree.merge(otherTree);
                    cout << "\nTrees merged :D\n";
                    break;
                }
                else if(merge_selection == 2){
                    cout << "\nOkay, try again.\n";
                    break;
                }
                else{
                    cout << "\n############     Please select a number between 1 and 2  >:(     ############\n";
                    cout << "\nTry again.\n";
                    break;
                }
                break;
            }
            default:{       // Invalid input guard for numbers outside the expected range
                cout << "\n############     Please select a number between 0 and 5  >:(     ############\n";
            }
        }
    }while(selection != 0);

    return 0;
}

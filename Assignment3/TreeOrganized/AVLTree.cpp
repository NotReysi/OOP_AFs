#include "AVLTree.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iterator>

using namespace std;

// ---------- Node structure ----------
Node::Node(double val){
    value = val;
    height = 1;
    left = nullptr;
    right = nullptr;
}

// ---------- Tree class ----------
int Tree::getHeight(Node* node){
    if(node == nullptr){
        return 0;
    }
    else{
        return node->height;
    }
}

int Tree::getFE(Node* node){
    if(node == nullptr){
        return 0;
    }
    else{
        return getHeight(node->left) - getHeight(node->right);
    }
}

Node* Tree::rightRotate(Node* y){
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

Node* Tree::leftRotate(Node* x){
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

Node* Tree::insert(Node* node, double value){
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

Node* Tree::search(Node* node, double value){
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

Node* Tree::erase(Node* node, double value){
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

void Tree::inorder(Node* node){
    if (node == nullptr){
        return;
    }
    else{
        inorder(node->left);
        cout << node->value << "  ";
        inorder(node->right);
    }
}

void Tree::preorder(Node*node){
    if (node == nullptr){
        return;
    }
    else{
        cout << node->value << "  ";
        preorder(node->left);
        preorder(node->right);
    }
}

void Tree::postorder(Node* node){
    if (node == nullptr){
        return;
    }
    else{
        postorder(node->left);
        postorder(node->right);
        cout << node->value << "  ";
    }
}

void Tree::destroy(Node* node){
    if (node == nullptr){
        return;
    }
    else{
        destroy(node->left);
        destroy(node->right);
        delete node;    // Delete after children
    }
}

void Tree::to_vector(Node* node, vector<double>& current_tree){
    if (node == nullptr){
        return;
    }
    else{
        to_vector(node->left, current_tree);
        current_tree.push_back(node->value);
        to_vector(node->right, current_tree);
    }
}

Node* Tree::from_vector(const vector<double>& vec, int start, int end){
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

Tree::Tree(){
    root = nullptr;
}

Tree::~Tree(){
    destroy(root);
}

void Tree::insert(double value){
    root = insert(root, value);
}

void Tree::inorder(){
    inorder(root);
    cout << endl;
}

void Tree::preorder(){
    preorder(root);
    cout << endl;
}

void Tree::postorder(){
    postorder(root);
    cout << endl;
}

bool Tree::search(double value){
    return search(root, value) != nullptr;  // Return true if found
}

void Tree::erase(double value){
    root = erase(root, value);
}

void Tree::merge(Tree& otherTree){
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
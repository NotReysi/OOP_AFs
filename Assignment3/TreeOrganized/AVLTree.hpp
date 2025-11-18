#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iterator>

using namespace std;

//Defined a global constant "e" (epsilon) to compare double values
//This helps to get rid of the imprecision
inline constexpr double e = 1e-9;

// ---------- Definition of the Node structure ----------
struct Node{
    //---------- Atributes ----------
    double value;       // The value stored in the node
    int height;         // The height of the subtree rooted at this node
    Node* left;         // Pointer to the left child
    Node* right;        // Pointer to the right child
    Node(double val);   // Constructor
};

// ---------- Definition of the Tree class ----------
class Tree{
    private:
        Node* root;                     // The main root of the tree
        int getHeight(Node* node);      // -- Get height of a node --
        int getFE(Node* node);          // -- Get Balance Factor (FE) --
        Node* rightRotate(Node* y);     // -- Performs a right rotation --
        Node* leftRotate(Node* x);      // -- Performs a left rotation --
        Node* insert(Node* node, double value); // -- Recursive function to insert a node -- 
        Node* search(Node* node, double value); // -- Recursive function to search a node -- 
        Node* erase(Node* node, double value);  // -- Recursive function to erase a node -- 
        void inorder(Node* node);       // -- Inorder Traversal (L, Root, R) --
        void preorder(Node*node);       // -- Preorder Traversal (Root, L, R) --
        void postorder(Node* node);     // -- Postorder Traversal (L, R, Root) --
        void destroy(Node* node);       // -- Destroy tree (free memory) --
        void to_vector(Node* node, vector<double>& current_tree);   // -- Convert the Tree to a vector --
        Node* from_vector(const vector<double>& vec, int start, int end);   // -- Build a tree from a vector --
    public:
        Tree();     // Constructor
        ~Tree();    // Destructor
        void insert(double value);  // -- Public insert --
        void inorder();     // -- Public inorder --
        void preorder();    // -- Public preorder --
        void postorder();   // -- Public postorder --
        bool search(double value);      // -- Public search --
        void erase(double value);       // -- Public erase --
        void merge(Tree& otherTree);    // -- Merge two trees --
};

#endif
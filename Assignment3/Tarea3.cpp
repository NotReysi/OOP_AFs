#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

//search(root, value)	    Función/Método privado para buscar un valor en el árbol.
//search(value)	            Método público que inicia la búsqueda.
//inOrder(root)	            Recorre el árbol en orden: izquierda -> nodo -> derecha.
//preOrder(root)	        Recorre el árbol en pre-orden: nodo -> izquierda -> derecha.
//postOrder(root)	        Recorre el árbol en post-orden: izquierda -> derecha -> nodo.
//deleteNode(root, value)	Implementa la eliminación de un nodo y el rebalanceo posterior. ¡El más complejo!
//merge(tree1, tree2)	    El método que encapsula el proceso de fusión de dos árboles AVL.

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
                cout << node->value << "";
                inorder(node->right);
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

        void search(Node* node, double value){
            
        }

        void errase(Node* node, double value){
            
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

        void search(double value){
            search(value);
        }

        void errase(double value){
            errase(root, value);
        }
};


//falta:
//Borrar valores
//Buscar valores
//Fusionar 2 arboles

int main(){
    Tree tree;

}
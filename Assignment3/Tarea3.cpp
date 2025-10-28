#include <iostream>

//<algorithm>	Útil para funciones como std::max (para calcular la altura de subárboles) o potencialmente para la etapa de fusión de arreglos.
//<vector>	Muy útil para almacenar temporalmente los elementos durante los recorridos y especialmente necesaria para la etapa de fusión de árboles (convertir el árbol a un array/vector ordenado).
//<cmath>	Podría ser necesaria si decides usar alguna función matemática específica para el manejo de la precisión de double      (aunque a menudo se maneja con constantes y lógica booleana). 


using namespace std;

//max(a, b)	                Función auxiliar (o usando std::max) para obtener el mayor de dos valores (necesario para calcular la altura).
//getHeight(node)	        Calcula la altura de un subárbol o nodo. ¡Debe ser eficiente! (generalmente se guarda en el nodo).
//getBalanceFactor(node)	Calcula el factor de balanceo de un nodo (diferencia de alturas de subárboles izquierdo y derecho).
//rightRotate(y)	        Implementa la rotación simple a la derecha para rebalancear.
//leftRotate(x)	            Implementa la rotación simple a la izquierda para rebalancear.
//insert(root, value)	    Función/Método privado que inserta recursivamente un valor y luego realiza las rotaciones necesarias para rebalancear.
//insert(value)	            Método público que inicia la inserción llamando a la función privada.
//search(root, value)	    Función/Método privado para buscar un valor en el árbol.
//search(value)	            Método público que inicia la búsqueda.
//inOrder(root)	            Recorre el árbol en orden: izquierda -> nodo -> derecha.
//preOrder(root)	        Recorre el árbol en pre-orden: nodo -> izquierda -> derecha.
//postOrder(root)	        Recorre el árbol en post-orden: izquierda -> derecha -> nodo.
//deleteNode(root, value)	Implementa la eliminación de un nodo y el rebalanceo posterior. ¡El más complejo!
//merge(tree1, tree2)	    El método que encapsula el proceso de fusión de dos árboles AVL.


class Node{
    private:
        //  ATRIBUTES
        double value;
        int height;
        Node* left;
        Node* right;

    public:
        Node(double val){ //    CONSTRUCTOR
            value = val;
            height = 1;
            left = nullptr;
            right = nullptr;
        }
};

class Tree{
    private:
        //  ATRIBUTES
        Node* root;



    public:
        Tree(){ //    CONSTRUCTOR
            root = nullptr;
        }

        double insert(double value){

        }

        double search(double value){
            
        }

        void order(){

        }

        int getHeight(){
            
        }

        void leftRotate(){

        }

        void _insert(Node* node, double value){

        }

};





int main(){

}
#include <iostream> 
#include <stack>    // para usar la estructura std::stack pila
#include <algorithm> // para std::max para la altura del arbol

using namespace std; 

// hacemos la estructura del nodo con atributos valor , punteros left y right para sus respectivos subarboles
struct Nodo {
    int valor;      
    Nodo* r_left;   
    Nodo* r_right;  

    
    Nodo(int v) {
        valor = v;          
        r_left = nullptr;   
        r_right = nullptr;  
    }
};




// clase ArbolBST para el arbol binarioa de busqueda con metodo para insertar, eliminar, 
// recorrido in-order y calcular altura

class ArbolBST {
private:
    Nodo* r; // putnero a raiz

public:
    
    ArbolBST() {
        r = nullptr; // incializamos una raiz nula cuando cremos el arbol
    }

    
    // metodo insertar_iterativo para insertar un valor en el arbol de forma iterativa

    void insertar_iterativo(int valor) {
        Nodo* nuevo_nodo = new Nodo(valor); //creamos nuevo nodo con un valor
        
        // si el arbol esta vacio, el nuevo nodo se convierte en la raiz
        if (r == nullptr) { 
            r = nuevo_nodo; 
            return;         
        }

        // creamos un puntero para recorrer el arbol "actual" y otro para recordar al padre del nodo actual "padre"
        Nodo* actual = r;      
        Nodo* padre = nullptr; 

        
        // el while "actual" diferente nulo, seguimos buscando la posicion correcta para insertar el nuevo nodo
        while (actual != nullptr) {
            padre = actual; // copiamos el nodo actual al padre antes de avanzar
            

            //si el valor a insertar es menor que el valor del nodo actual, vamos por la rama izquierda
            //sino vamos por la rama derecha

            if (valor < actual->valor) { 
                actual = actual->r_left; 
            } else {                     
                actual = actual->r_right;
            }
        }

        // cuando encontramos la posicion de la hoja, conectamos el nuevo nodo al padre correspondiente
        // si el valor es menor que el del padre lo conectamos a la izquierda, sino a la derecha
        if (valor < padre->valor) {      
            padre->r_left = nuevo_nodo;  
        } else {                         
            padre->r_right = nuevo_nodo; 
        }
    }

    // ahora el metodo eliminar_iterativo sirve para eliminar un nodo con un valor especifico de forma iterativa
    void eliminar_iterativo(int valor) {
        Nodo* actual = r;      // puntero "actual"para buscar el nodo a eliminar, lo iniciamos en la raiz
        Nodo* padre = nullptr; // puntero "padre" para recordar al padre del nodo actual, lo iniciamos en nulo para el caso de eliminar la raiz




        // hacemos el bucle para encontrar el nodo con el valor a eliminar, actualizamos el padre en cada iteracion
        // si el valor buscado es menor que el valor del nodo actual avanzamos por la izquierda, sino por la derecha

        while (actual != nullptr && actual->valor != valor) {
            padre = actual; // cuando entra al while se actualiza el padre al nodo actual 
            if (valor < actual->valor) { 
                actual = actual->r_left; 
            } else {                     
                actual = actual->r_right;
            }
        }

        if (actual == nullptr) return; // si no encontramos el valor salimos del metodo


        // entramos al if si el nodo a eliminar tiene al menos un hijo nulo 0 o 1 hijo
        if (actual->r_left == nullptr || actual->r_right == nullptr) {

            // creamos el puntero "hijo_sustituto" que apuntara al hijo no nulo del nodo a eliminar, si ambos hijos son nulos, el sustituto sera nulo
            Nodo* hijo_sustituto = (actual->r_left == nullptr) ? actual->r_right : actual->r_left;

        
            
            // si el padre es nulo  eliminamos la raiz, luego actualizamos la raiz al hijo sustituto
            
            if (padre == nullptr) {     
                r = hijo_sustituto;     
            } else if (actual == padre->r_left) { 
                padre->r_left = hijo_sustituto;   // si el nodo a eliminar es el hijo izquierdo del padre, conectamos el hijo sustituto a la izquierda del padre
            } else {                              
                padre->r_right = hijo_sustituto;  // analogamente  cuando se elimina el hijo derecho del padre, conectamos el hijo sustituto a la derecha del padre
            }
            delete actual;
        } 

        // ahora cuando el nodo a eliminar tiene dos hijos
        else {
            Nodo* sucesor_padre = actual;        // puntero para recordar al padre del sucesor "sucesor_padre", lo iniciamos en el nodo actual
            Nodo* sucesor = actual->r_right;     // el puntero sucesor se inicia en el hijo derecho del nodo a eliminar, ya que el sucesor es el nodo mas a la izquierda del sub-árbol derecho

            // hacemos el while para encontrar el sucesor y avanzamos hacia la izquierda extrema del sub-árbol derecho, actualizando el padre del sucesor en cada iteracion
            while (sucesor->r_left != nullptr) {
                sucesor_padre = sucesor;         // se actualiza el padre_sucesor antes de avanzar
                sucesor = sucesor->r_left;       // avanza hacia la izquierda extrema
            }

            actual->valor = sucesor->valor;      // reemplazamos el valor del nodo actual por el del sucesor

            // ahora reconectamos los hijos del sucesor para poder eliminar el nodo sucesor fisico
            // si el sucesor es un hijo izquierdo del nodo a eliminar, el padre del sucesor adopta al hijo derecho del sucesor
            if (sucesor_padre->r_left == sucesor) { 
                sucesor_padre->r_left = sucesor->r_right; 
            } else { 
                sucesor_padre->r_right = sucesor->r_right; // de lo contrario, si el sucesor es un hijo derecho del nodo a eliminar, el padre del sucesor adopta al hijo derecho del sucesor
            }
            delete sucesor; // liberamos memoria del nodo sucesor que se ha elimando del arbol
        }
    }

    
    // metodo recorrido_in_order para recorrer el arbol en orden de forma iterativa utilizando una pila 
    void recorrido_in_order() {
        stack<Nodo*> pila;  // creamos una pila para almacenar los nodos 
        Nodo* actual = r;   // iniciamos desde la raiz 

        // hacemos el bucle iterativo mientras haya nodos por visitar
        while (actual != nullptr || !pila.empty()) {
            
            // hacemos un subbucle para llegar al nodo mas a la izquierda del subarbol actual, apilando los nodos en el camino
            while (actual != nullptr) {
                pila.push(actual);       // hacemos un push del nodo actual a la pila antes de avanzar
                actual = actual->r_left; // movemos el hijo izquierdo r_left
            }

            actual = pila.top(); // hacmeos el actual al tope de la pila
            pila.pop();          // popeamos el tope

            cout << actual->valor << " ";

            actual = actual->r_right; // evaluamos el sub arbol derecho r_right
        }
        cout << endl; 
    }


    // ahora el metodo "calcular_altura" para calcular la altura del arbol de forma recursiva

    int calcular_altura(Nodo* nodo_actual) {

        // si es nulo retorna 0
        if (nodo_actual == nullptr) { 
            return 0;                 
        }
        // aqui retornamos el maximo entre la altura del subarbol izquierdo y derecho mas 1 para contar el nodo actual
        return max(calcular_altura(nodo_actual->r_left), calcular_altura(nodo_actual->r_right)) + 1;
    }

    // metodo para exponer el valor de altura desde la raiz
    int obtener_altura() {
        return calcular_altura(r); 
    }
};


int main() {
    ArbolBST arbol; // instanciamos un ArbolBST.

    // insertamos 20 elementos con el metodo insertar_iterativo , con valores del 1 al 20
    cout << "Insertandose 20 elementos" << endl; 
    

    for (int i = 1; i <= 20; i++) {
        arbol.insertar_iterativo(i); 
    }

    // eliminamos el 5 y el 15 con eliminar_iterativo
    cout << "Eliminando el 5 y el 15" << endl; 
    arbol.eliminar_iterativo(5);  
    arbol.eliminar_iterativo(15); 

    // recorremos el arbol en orden con recorrido_in_order
    cout << "Recorrido in-order: "; 
    arbol.recorrido_in_order();    // imprime los valores del arbol en orden

    // calculamos la altura del arbol
    cout << "Altura final del arbol: " << arbol.obtener_altura() << endl; 

    return 0;
}
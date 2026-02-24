#include <iostream> 
#include <stack>    // para usar pilas
#include <vector>   
#include <algorithm> // para el std::reverse

using namespace std; 



// estructura del nodo
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

// funcion principal que busca el camino que sume K
vector<int> buscar_camino_suma(Nodo* r, int K) {
    stack<Nodo*> pila;       // almacenara los punteros a los nodos del camino actual
    vector<int> resultado;   // para guardar y retornar el camino encontrado
    

    // si vaicio retornar resultado vacio
    if (r == nullptr) {      
        return resultado;    
    }

    Nodo* actual = r;                 // para descender por el arbol
    Nodo* ultimo_visitado = nullptr;  // puntero auxiliar para recordar que nodo procesamos justo antes 
    int suma_actual = 0;              // acumulador de suma del camino en la pila

    // hacemos el bucle para que se ejecuta mientras haya nodos por explorar o elementos en la pila
    while (!pila.empty() || actual != nullptr) {
        
        // fase de descenso, aqui nos vamos lo más a la izquierda posible
        if (actual != nullptr) {
            pila.push(actual);             // apilamos el nodo actual
            suma_actual += actual->valor;  // acumularmos su valor
            actual = actual->r_left;       // avanzamos al hijo izquierdo
        } 
        // ahora la fase de evalucion cuando ya no podemos bajar mas a la izquierda

        else {
            Nodo* nodo_tope = pila.top();  // miramos el nodo en la cima de la pila sin sacarlo

            // verificamos si es un nodo hoja 
            if (nodo_tope->r_left == nullptr && nodo_tope->r_right == nullptr) {


                //Si la suma acumulada coincide con el valor K
                if (suma_actual == K) {    
                    
                    // entramos al bucle si encontramos el camino correcto, sacamos los nodos de la pila para guardarlos en el vector resultado
                    while (!pila.empty()) {
                        resultado.push_back(pila.top()->valor); 
                        pila.pop();                             
                    }
                    
                    // como los sacamos al reves, invertimos el vector para que quede de raiz a hoja
                    reverse(resultado.begin(), resultado.end());
                    return resultado; // retornamos  el camino encontrado
                }
            }

            // si el nodo en la cima de la pila tiene un hijo derecho que no hemos visitado aun , cambiamos nuestra ruta hacia ese hijo derecho
            if (nodo_tope->r_right != nullptr && ultimo_visitado != nodo_tope->r_right) {
                actual = nodo_tope->r_right; 
            } 
            // si no tiene hijo derecho o ya lo visitamos antes, retrocedemos, es decir sacamos el nodo de la pila y restamos su valor de la suma acumulada
            else {
                suma_actual -= nodo_tope->valor; 
                ultimo_visitado = nodo_tope;     // marcamos este nodo como ultimo procesado
                pila.pop();                      // eliminamos definitivamente de la pila
            }
        }
    }

    return resultado; // si terminamos el bucle sin encontrar un camino que sume K, retornamos el vacio
}

/*


PORQUE USAR DFS PARA ESTE PROBLEMA?

Use DFS  porque es la forma mas logica y natural de buscar un camino desde la raiz hasta una hoja
El DFS es explorar una rama completa hasta llegar al fondo antes de retroceder y probar otra.
Como el problema nos pide evaluar la suma de un camino continuo es decir de arriba a abajo, DFS hace exactamente eso, va bajando nodo por nodo, sumando los valores, hasta chocar con una hoja.

Ademas, al usar una pila, el manejo de la memoria y del camino es  eficiente. La pila  representa la ruta exacta en la que estamos parados en ese instante. 
Si llegamos a una hoja y la suma no es igual a K, simplemente damos un paso atras esto es, desapilamos el último nodo, le restamos su valor a nuestro acumulador, y probamos por el otro lado. 

*/
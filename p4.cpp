#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;


// el nodo
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

class AnalizadorArbolBFS {
public:
    // revisa si el arbol es completo (lleno de izq a der sin huecos)
    bool es_arbol_completo(Nodo* raiz) {
        if (raiz == nullptr) return true; // un arbol vacio cuenta como completo

        queue<Nodo*> cola; // usamos cola porque es bfs 
        cola.push(raiz); // arrancamos con la raiz
        
        bool se_encontro_nulo = false; // flag para avisar si vimos un espacio vacio

        while (!cola.empty()) {
            Nodo* nodo_actual = cola.front(); // leemos el primero en la fila
            cola.pop(); // lo sacamos de la cola

            if (nodo_actual == nullptr) {

                // si es nulo, no deberia haber mas nodos despues de esto
                se_encontro_nulo = true; 
            } else {

                // si ya habiamos visto un nulo y ahora hay un nodo real despues, entonces no es completo
                if (se_encontro_nulo == true) {
                    return false; 
                }
                

                // metemos los hijos a la cola para seguir revisando 
                cola.push(nodo_actual->r_left);  
                cola.push(nodo_actual->r_right); 
            }
        }

        return true; // si sobrevivio al bucle, esta todito completo
    }

    // calcula cual es el nivel que tiene mas nodos
    int calcular_ancho_maximo(Nodo* raiz) {
        if (raiz == nullptr) return 0; // si no hay raiz, el ancho es 0

        queue<Nodo*> cola;
        cola.push(raiz);
        
        int ancho_maximo = 0; // variable para guardar el record

        while (!cola.empty()) {
            int tamanio_nivel = cola.size(); // vemos cuantos nodos hay en este nivel exacto
            
            // actualizamos el record si este nivel tiene mas nodos que los anteriores
            ancho_maximo = max(ancho_maximo, tamanio_nivel);


            // este for se asegura de procesar SOLO los nodos del nivel actual
            for (int i = 0; i < tamanio_nivel; i++) {
                Nodo* nodo_actual = cola.front(); // sacamos el nodo
                cola.pop();


                // si tiene hijos, los metemos a la fila para el siguiente nivel
                if (nodo_actual->r_left != nullptr) {
                    cola.push(nodo_actual->r_left);
                }


                if (nodo_actual->r_right != nullptr) {
                    cola.push(nodo_actual->r_right);
                }
            }
        }


        return ancho_maximo; // devolvemos el ancho maximo encontrado
    }

    // busca la hoja mas cerquita a la raiz
    int calcular_profundidad_minima(Nodo* raiz) {
        if (raiz == nullptr) return 0; // si esta vacio, no hay profundidad

        queue<Nodo*> cola;
        cola.push(raiz); // empezamos en la raiz
        
        int profundidad_actual = 1; // la raiz cuenta como el nivel 1

        while (!cola.empty()) {
            int tamanio_nivel = cola.size(); // cantidad de nodos a revisar en este nivel

            // revisamos todos los de este piso
            for (int i = 0; i < tamanio_nivel; i++) {
                Nodo* nodo_actual = cola.front();
                cola.pop();

                // comprobamos si es una hoja 
                if (nodo_actual->r_left == nullptr && nodo_actual->r_right == nullptr) {
                    // como el bfs va nivel por nivel, la primera hoja que tocamos 
                    // siempre es la mas superficial. cortamos todo y devolvemos la profundidad aca mismo
                    return profundidad_actual; 
                }

                // si no es hoja, encolamos sus hijos para que se revisen en el nivel de abajo
                if (nodo_actual->r_left != nullptr) cola.push(nodo_actual->r_left);
                if (nodo_actual->r_right != nullptr) cola.push(nodo_actual->r_right);
            }


            // si terminamos de revisar este nivel y no hubo hojas, bajamos un piso
            profundidad_actual++; 
        }
        return profundidad_actual; // retornamos la profundidad minima encontrada
    }
};

int main() {
    AnalizadorArbolBFS analizador;

    // armando un arbol manual chiquito para probar que todo corra bien
    Nodo* raiz = new Nodo(1);
    raiz->r_left = new Nodo(2);
    raiz->r_right = new Nodo(3);
    raiz->r_left->r_left = new Nodo(4);
    raiz->r_left->r_right = new Nodo(5);
    // el nodo 3 se queda sin hijos

    // imprimimos los resultados llamando a las funciones
    cout << "Es arbol completo?: " << analizador.es_arbol_completo(raiz) << endl;
    cout << "ncho maximo: " << analizador.calcular_ancho_maximo(raiz) << endl;
    cout << "Profundidad minima: " << analizador.calcular_profundidad_minima(raiz) << endl;

    return 0; 
}
#include <iostream> 
#include <algorithm> // para el std:max en la altura del arbol

using namespace std; 

// definir los colores del nodo para el RBT
enum Color { ROJO, NEGRO };


// estructura del nodo
struct Nodo {
    int valor;      
    Color color;    // almacena el color
    Nodo* r_left;   // puntero subarbol izquierda
    Nodo* r_right;  // puntero subarbol derecho
    Nodo* padre;    // puntero al nodo padre para las rotaciones

    
    // construimos todo en nulo
    Nodo() : valor(0), color(NEGRO), r_left(nullptr), r_right(nullptr), padre(nullptr) {}
};

// clase del Red-Black Tree
class RedBlackTree {
private:
    Nodo* r;         // raiz
    Nodo* nodo_nulo; // node que representa las hojas nulas

    // metodo rotacion izquierda
    void rotacion_izquierda(Nodo* x) {

        Nodo* y = x->r_right; // 'y' es el hijo derecho de 'x'.
        x->r_right = y->r_left; // el hijo izquierdo de 'y' pasa a ser el hijo derecho de 'x'
        

        // si el hijo izquierdo de 'y' no es nulo su nuevo padre es 'x'
        if (y->r_left != nodo_nulo) { 
            y->r_left->padre = x;     
        }
        
        y->padre = x->padre; // el padre de 'x' ahora es el padre de 'y'.
        


        // si el 'x' era la raiz, ahora 'y' es la nuevo raiz, si 'x' era hijo izquierdo 'y' ocupa su lugar, si 'x' era hijo drecho, 'y' ocupa su lugar
        if (x->padre == nullptr) { 
            r = y;                 
        } else if (x == x->padre->r_left) { 
            x->padre->r_left = y;           
        } else {                            
            x->padre->r_right = y;          
        }
        

        // luego 'x' se convierte en el hijo izquierdo de 'y' y 'y' se convierte en el nuevo padre de 'x'
        y->r_left = x; 
        x->padre = y;  
    }

    // ahora metodo para rotacion derecha, es simetrico a la izquierda
    void rotacion_derecha(Nodo* y) {

        Nodo* x = y->r_left; // 'x' es el hijo izquierdo de 'y'.
        y->r_left = x->r_right; // el hijo derecho de 'x' pasa a ser el hijo izquierdo de 'y'
        

        // simetrico a la rotacion izquierda
        if (x->r_right != nodo_nulo) { 
            x->r_right->padre = y;     
        }
        
        x->padre = y->padre; // el padre de 'y' ahora es el padre de 'x'.
        

        // simetrico a la rotacion izquierda
        if (y->padre == nullptr) { 
            r = x;                 
        } else if (y == y->padre->r_right) { 
            y->padre->r_right = x;           
        } else {                             
            y->padre->r_left = x;            
        }
        
        x->r_right = y; // 'y' se convierte en el hijo derecho de 'x'
        y->padre = x;   // ahora el nuevo padre de 'y' es 'x'
    }

    // metodo privado "corregir_insercion" para corregir la insercion y mantener las propiedades del RBT
    void corregir_insercion(Nodo* k) {

        Nodo* tio; // puntero para el tio del nodo 'k' durante el proceso de correccion
   
        
        // mientras el padre exista y sea ROJO, se pueden violar las propiedades del RBT, por lo que se necesita corregir
       
        while (k->padre != nullptr && k->padre->color == ROJO) {

            // si el padre de 'k' es hijo izquierdo del abuelo, el tio es el hijo derecho del abuelo
            if (k->padre == k->padre->padre->r_left) { 
                tio = k->padre->padre->r_right; 
                
                // primer caso cuando el tio es ROJO, se recolorean el padre y el tio a
                if (tio->color == ROJO) {
                    k->padre->color = NEGRO;          // volvemos al padre NEGRO
                    tio->color = NEGRO;               //  volvemos al tio NEGRO
                    k->padre->padre->color = ROJO;    // el abuelo se vuelve ROJO
                    k = k->padre->padre;              // actualizamos 'k' con el abuelo
                } else {
                    // segudno caso si el tio es NEGRO y el nodo es hijo derecho

                    if (k == k->padre->r_right) {
                        k = k->padre;           // movemos 'k' al padre
                        rotacion_izquierda(k);  // hacemos rotación izquierda sobre 'k'
                    }
                    // tercer caso cuando el tio es NEGRO y el nodo es hijo izquierdo
                    k->padre->color = NEGRO;          // volvemos al padre NEGRO
                    k->padre->padre->color = ROJO;    // el abuelo se vuelve ROJO
                    rotacion_derecha(k->padre->padre);  // rotamos derecha sobre el abuelo
                }
            } else { // de lo contrario, hacemos el simetrico, si el padre es hijo derecho del abuelo...
                tio = k->padre->padre->r_left; // ...el tio es el hijo izquierdo



                if (tio->color == ROJO) { // simetricamente al if
                    k->padre->color = NEGRO;
                    tio->color = NEGRO;
                    k->padre->padre->color = ROJO;
                    k = k->padre->padre;
                } else {


                    if (k == k->padre->r_left) { // el segundo caso tambien simetrico al if, esta vez se da rotacion derecha
                        k = k->padre;
                        rotacion_derecha(k);
                    }
                    // tercer caso de la misma manera
                    k->padre->color = NEGRO;
                    k->padre->padre->color = ROJO;
                    rotacion_izquierda(k->padre->padre);
                }
            }
        }
        r->color = NEGRO; // luego por la regla 2 la raiz sea siempre es negra
    }

    // recorrido pre_orden_aux recursivo auxiliar
    void pre_orden_aux(Nodo* nodo) {

        // si no es el nodo nulo, imprimos su color para visualizar, luego recorremos el subarbol izquierdo y el derecho
        if (nodo != nodo_nulo) { 
            
            cout << nodo->valor << (nodo->color == ROJO ? "(R) " : "(N) ");
            pre_orden_aux(nodo->r_left);  
            pre_orden_aux(nodo->r_right); 
        }
    }

    // metodo auxiliar para calcular altura
    int calcular_altura_aux(Nodo* nodo) {

        // si es nulo retorno altura 0, de lo contrario se hace una iteracion entre el maximo del lado izquierdo con el derecho mas 1
        if (nodo == nodo_nulo) return 0; 
        return 1 + max(calcular_altura_aux(nodo->r_left), calcular_altura_aux(nodo->r_right));
    }

    // metodo auxiliar para verificar si la cantidad de nodos negros en cada camino es igual 
    int verificar_altura_negra(Nodo* nodo) {
        if (nodo == nodo_nulo) return 1; // las hojas nulas son negras

        int altura_izq = verificar_altura_negra(nodo->r_left);  
        int altura_der = verificar_altura_negra(nodo->r_right);

        // si alguna rama falla o las ramas tienen distinta cantidad de nodos negros, retorna -1, error
        if (altura_izq == -1 || altura_der == -1 || altura_izq != altura_der) {
            return -1;
        }

        // retorna la altura acumulada ,suma 1 si el nodo actual es negro
        return altura_izq + (nodo->color == NEGRO ? 1 : 0);
    }

public:
    // Constructor
    RedBlackTree() {
        nodo_nulo = new Nodo(); // instancia del nodo nulo
        nodo_nulo->color = NEGRO; // hacemos su color NEGRO
        r = nodo_nulo;          // apuntamo la razi al nodo nulo
    }

    // metodo para la insercion en el arbol
    void insertar(int valor) {
        Nodo* nuevo = new Nodo();   
        nuevo->valor = valor;       
        nuevo->r_left = nodo_nulo;  // sus hijos inician apuntando  nulo
        nuevo->r_right = nodo_nulo;
        nuevo->color = ROJO;        // las nuevas inserciones SIEMPRE nacen rojas por defecto

        Nodo* y = nullptr; // putnero auxiliar
        Nodo* x = r;       // puntero para descender desde la raiz


        // hacemos el bucle de insercion en BST

        while (x != nodo_nulo) { 
            y = x;
            if (nuevo->valor < x->valor) {
                x = x->r_left;
            } else {
                x = x->r_right;
            }
        }

        nuevo->padre = y; // enlazamos el padre
        


        //si el arbol estaba vacío el nuevo nodo es la raíz.
        if (y == nullptr) { 
            r = nuevo;      
        // si el nuevo nodo es menor que su padre, se convierte en el hijo izquierdo, de lo contrario, en el derecho
        } else if (nuevo->valor < y->valor) {
            y->r_left = nuevo;
        } else {
            y->r_right = nuevo;
        }

        // si el nuevo nodo es la raíz, simplemente se pinta de negro
        if (nuevo->padre == nullptr) { 
            nuevo->color = NEGRO;      
            return;
        }


        //si el abuelo no existe, salimos

        if (nuevo->padre->padre == nullptr) { 
            return;
        }

        corregir_insercion(nuevo); // lamamos a la funcion para balancear e iterar colores
    }



    // metodo publico para recorrido re-orden
    void recorrido_pre_orden() {
        pre_orden_aux(r); // llama al metood auxiliar con la raiz
        cout << endl;     
    }

    // metodo public para obtener la altura
    int obtener_altura() {
        return calcular_altura_aux(r); 
    }

    // metodo para verificar las propiedades
    bool verificar_propiedades() {
        if (r->color != NEGRO) { // por la propiedad 2 la raiz debe ser NEGRO
            cout << "Fallo: La raiz no es negra." << endl;
            return false;
        }
        
        if (verificar_altura_negra(r) == -1) { // los caminos deben tener el mismo numero de nodos negros
            cout << "Fallo: Las rutas tienen distinta cantidad de nodos negros." << endl;
            return false;
        }
        cout << "El arbol cumple todas las propiedades formales del RBT." << endl;
        return true;
    }
};

int main() {
    RedBlackTree rbt; // instancemos el arbol

    cout << "Insertandose 20 elementos en orden ascendente en RBT" << endl;
    for (int i = 1; i <= 20; i++) {
        rbt.insertar(i); // Inserta los valores del 1 al 20 secuencialmente[cite: 54].
    }

    cout << "Recorrido Pre-Orden, R=Rojo, N=Negro:" << endl;
    rbt.recorrido_pre_orden(); // mostramos la estructura


    // imprimimos la altura y verificamos las propiedades
    cout << "Altura del Red-Black Tree: " << rbt.obtener_altura() << endl; 
    rbt.verificar_propiedades(); 

    return 0;
}
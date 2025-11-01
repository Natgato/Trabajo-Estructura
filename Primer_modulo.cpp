#include <iostream>
#include <string>
using namespace std;


// Estructuras para productos, clientes y ventas (listas enlazadas)
struct Producto {
 int codigo;
 string nombre;
 float precio;
 Producto* sig;
};
struct Cliente {
 string nombre;
 Cliente* sig;
};
struct Venta {
 string detalle;
 Venta* sig;
};


// Agrega un producto al inicio de la lista
void agregarProducto(Producto*& lista) {
 Producto* nuevo = new Producto();
 cout << "Codigo: "; cin >> nuevo->codigo;
 cin.ignore();
 cout << "Nombre: "; getline(cin, nuevo->nombre);
 cout << "Precio: "; cin >> nuevo->precio;
 nuevo->sig = lista;
 lista = nuevo;
 cout << "Producto agregado.\n";
}


// Muestra todos los productos
void mostrarProductos(Producto* lista) {
 Producto* aux = lista;
 while (aux != NULL) {
 cout << aux->codigo << " - " << aux->nombre << " - S/ " << aux->precio << endl;
 aux = aux->sig;
 }
}


// Ingresa un cliente al final de la cola

void encolarCliente(Cliente*& frente, Cliente*& final) {
 Cliente* nuevo = new Cliente();
 cin.ignore();
 cout << "Nombre del cliente: ";
 getline(cin, nuevo->nombre);
 nuevo->sig = NULL;
 if (final == NULL) {
 frente = final = nuevo;
 } else {
 final->sig = nuevo;
 final = nuevo;
 }
 cout << "Cliente registrado.\n";
}

// Registra una venta en la pila
void registrarVenta(Venta*& tope) {
 Venta* nueva = new Venta();
 cin.ignore();
 cout << "Detalle de la venta: ";
 getline(cin, nueva->detalle);
 nueva->sig = tope;
 tope = nueva;
 cout << "Venta registrada.\n";
}



// Menú principal
void menu() {
 Producto* lista = NULL;
 Cliente* frente = NULL;
 Cliente* final = NULL;
 Venta* tope = NULL;
 int opcion;
 do {
 cout << "\n1. Agregar producto\n2. Mostrar productos\n3. Registrar cliente\n4. Registrar venta\n0.
Salir\n";
 cout << "Opcion: ";
 cin >> opcion;
 switch (opcion) {
 case 1: agregarProducto(lista); break;
 case 2: mostrarProductos(lista); break;
 case 3: encolarCliente(frente, final); break;
 case 4: registrarVenta(tope); break;
 case 0: cout << "Fin del programa.\n"; break;
 }
 } while (opcion != 0);
}
int main() {
 menu();
 return 0;
}
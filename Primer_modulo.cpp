#include <iostream>
#include <string>
using namespace std;
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
void mostrarProductos(Producto* lista) {
 Producto* aux = lista;
 while (aux != NULL) {
 cout << aux->codigo << " - " << aux->nombre << " - S/ " << aux->precio << endl;
 aux = aux->sig;
 }
}
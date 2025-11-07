#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// --------- MODELO ---------
struct Producto
{
    int id;
    string nombre, categoria, unidad, ubicacion;
    double precio;
    int stock, stockMin;
    bool activo; // siempre true en esta versión 
    Producto *sig;
};

struct Pedido
{
    int idPedido, idProd, cant;
    string obs;
    Pedido *sig;
};

// --------- LISTA: productos ---------
Producto *buscarProducto(Producto *head, int id)
{
    for (Producto *p = head; p; p = p->sig)
        if (p->id == id)
            return p;
    return NULL;
}

bool agregarProducto(Producto *&head, const Producto &in)
{
    if (in.id <= 0 || in.precio < 0 || in.stock < 0 || in.stockMin < 0)
        return false;
    if (buscarProducto(head, in.id))
        return false; // id único
    Producto *n = new Producto(in);
    n->sig = head;
    head = n; // inserción O(1)
    return true;
}

void listarProductos(Producto *head)
{
    cout << left << setw(6) << "ID" << setw(18) << "Nombre" << setw(12) << "Cat"
         << setw(6) << "Und" << setw(7) << "Stock" << setw(7) << "Min"
         << setw(9) << "Precio" << "Ubic\n";
    for (Producto *p = head; p; p = p->sig)
    {
        if (!p->activo)
            continue;
        cout << left << setw(6) << p->id
             << setw(18) << p->nombre.substr(0, 17)
             << setw(12) << p->categoria.substr(0, 11)
             << setw(6) << p->unidad
             << setw(7) << p->stock
             << setw(7) << p->stockMin
             << setw(9) << fixed << setprecision(2) << p->precio
             << p->ubicacion << "\n";
    }
}

// --------- COLA: pedidos ---------
void encolar(Pedido *&frente, Pedido *&fin, const Pedido &x)
{
    Pedido *n = new Pedido(x);
    n->sig = NULL;
    if (!fin)
    {
        frente = fin = n;
    }
    else
    {
        fin->sig = n;
        fin = n;
    }
}

bool desencolar(Pedido *&frente, Pedido *&fin, Pedido &out)
{
    if (!frente)
        return false;
    Pedido *n = frente;
    out = *n;
    frente = frente->sig;
    if (!frente)
        fin = NULL;
    delete n;
    return true;
}

bool colaVacia(Pedido *frente) { return frente == NULL; }
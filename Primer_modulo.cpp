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

// --------- DOMINIO ---------
bool ingreso(Producto *productos, int idProd, int cant)
{
    if (cant <= 0)
        return false;
    Producto *p = buscarProducto(productos, idProd);
    if (!p || !p->activo)
        return false;
    p->stock += cant;
    return true;
}

bool ajuste(Producto *productos, int idProd, int cant)
{
    Producto *p = buscarProducto(productos, idProd);
    if (!p || !p->activo)
        return false;
    int nuevo = p->stock + cant;
    if (nuevo < 0)
        return false;
    p->stock = nuevo;
    return true;
}

bool atenderPedido(Producto *productos, Pedido *&frente, Pedido *&fin)
{
    if (colaVacia(frente))
    {
        cout << "[WARN] Cola vacia\n";
        return false;
    }
    Pedido ped;
    desencolar(frente, fin, ped);
    Producto *p = buscarProducto(productos, ped.idProd);
    if (!p || !p->activo)
    {
        cout << "[ERR] Producto invalido\n";
        return false;
    }
    if (p->stock < ped.cant)
    {
        cout << "[ERR] Stock insuficiente\n";
        return false;
    }
    p->stock -= ped.cant;
    cout << "[OK] Pedido " << ped.idPedido << " atendido. " << ped.cant << " und descontadas.\n";
    return true;
}

// --------- MAIN ---------
int main()
{

    Producto *catalogo = NULL;
    Pedido *frente = NULL;
    Pedido *fin = NULL;
    int op = -1, autPed = 1;

    // Semilla
    agregarProducto(catalogo, {101, "Cemento", "cemento", "bolsa", "A1", 32.5, 20, 5, true, NULL});
    agregarProducto(catalogo, {202, "Pintura CPP", "pintura", "gal", "B3", 85.9, 12, 3, true, NULL});
    agregarProducto(catalogo, {303, "Tubo PVC 110", "tuberia", "m", "C2", 12.0, 50, 10, true, NULL});

    while (true)
    {
        cout << "\n=== Menu ===\n"
             << "1 Agregar producto\n2 Listar productos\n"
             << "3 Ingreso stock\n4 Ajuste stock (+/-)\n"
             << "5 Encolar pedido\n6 Atender pedido\n0 Salir\n> ";
        if (!(cin >> op))
            break;
        if (op == 0)
            break;

        if (op == 1)
        {
            Producto p{};
            cin.ignore();
            cout << "nombre:";
            getline(cin, p.nombre);
            cout << "id:";
            cin >> p.id;
            cin.ignore();
            cout << "categoria:";
            getline(cin, p.categoria);
            cout << "unidad:";
            getline(cin, p.unidad);
            cout << "ubicacion:";
            getline(cin, p.ubicacion);
            cout << "precio:";
            cin >> p.precio;
            cout << "stock:";
            cin >> p.stock;
            cout << "stockMin:";
            cin >> p.stockMin;
            p.activo = true;
            p.sig = NULL;
            cout << (agregarProducto(catalogo, p) ? "[OK] agregado\n" : "[ERR] datos invalidos o id duplicado\n");
        }
        else if (op == 2)
        {
            listarProductos(catalogo);
        }
        else if (op == 3)
        {
            int id, c;
            cout << "idProd:";
            cin >> id;
            cout << "cant:";
            cin >> c;
            cout << (ingreso(catalogo, id, c) ? "[OK] ingreso\n" : "[ERR] ingreso invalido\n");
        }
        else if (op == 4)
        {
            int id, c;
            cout << "idProd:";
            cin >> id;
            cout << "ajuste (+/-):";
            cin >> c;
            cout << (ajuste(catalogo, id, c) ? "[OK] ajuste\n" : "[ERR] ajuste invalido\n");
        }
        else if (op == 5)
        {
            int id, c;
            string obs;
            cout << "idProd:";
            cin >> id;
            cout << "cant:";
            cin >> c;
            cin.ignore();
            cout << "obs:";
            getline(cin, obs);
            encolar(frente, fin, {autPed++, id, c, obs, NULL});
            cout << "[OK] pedido en cola\n";
        }
        else if (op == 6)
        {
            atenderPedido(catalogo, frente, fin);
        }
    }
    return 0;
}
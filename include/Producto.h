#ifndef PRODUCTO_H
#define PRODUCTO_H
#include <iostream>
using namespace std;
#include <clocale>
#include <cstring>

class Producto{
    private:
        int _idProducto;
        int _stock;
        char _descripcion[30];
        float _precio;
        bool _estado;

    public:
        //CONSTRUCTOR
        Producto();
        //GETTERS:
        int getID();
        int getStock();
        char *getDesc();
        float getPrecio();
        bool getEstado();
        //SETTERS:
        void setID(int);
        void setStock(int);
        void setDesc(char *);
        void setPrecio(float);
        void setEstado(bool);
        //OTROS MÉTODOS:
        void cargar();
        void mostrar();
        bool escribirDisco();
        bool leerDeDisco(int);
        bool modificarEnDisco(int);
};

bool agregarRegistro();
bool listarRegistros();
bool listarRegistros2();
bool eliminarRegistro();
int buscarProducto(int);
int contarProductos();
void buscarProductosxRangoPrecio();
void rankingProductosMasVendidos();
void leerProductos(Producto *, int);


#endif // PRODUCTO_H

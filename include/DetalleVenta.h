#ifndef DETALLEVENTA_H
#define DETALLEVENTA_H
#include <iostream>
using namespace std;
#include <clocale>
#include <cstring>
#include "Fecha.h"
#include "Persona.h"



class DetalleVenta
{
     private:
        int _idVenta;
        int _idProducto;
        int _cantidad;
        float _precioU;
        bool _estado;

    public:
        DetalleVenta();
        int getIDProducto();
        int getIDVenta();
        int getCantidad();
        float getPrecio();
        bool getEstado();
        void setIDProducto(int);
        void setIDVenta(int);
        void setCantidad(int);
        void setPrecio(float);
        void setEstado(bool);
        void cargar();
        void mostrar();
        bool escribirDisco();
        bool leerDisco(int);
        bool modificarEnDisco(int);

};

void nuevaVenta();
void listarDetalleVentas();
void cancelarVentaActual(int);
bool devolucionVenta();
void ventasPorDia();
void cajaDiaria();
void productosXClientes();
int sumarProductos(int id);



#endif // DETALLEVENTA_H

#ifndef COMPRAS_H
#define COMPRAS_H
#include <iostream>
using namespace std;
#include <clocale>
#include <cstring>


class Compras{
    private:
        int _idCompra;
        Fecha _fechaCompra;
        float _importeCompra;
        char _motivo[50];
        bool _estado;

    public:
        Compras();
        int getIDCompra();
        Fecha getFechaCompra();
        float getImporteCompra();
        char * getMotivo();
        bool getEstado();
        void setIDCompra(int);
        void setFechaCompra(Fecha);
        void setImporteCompra(float);
        void setMotivo(char *);
        void setEstado(bool);
        void cargar();
        void mostrar();
        bool escribirDisco();
        bool leerDisco(int);
        bool modificarEnDisco(int);
};

void nuevaCompra();
int contarCompras();
bool devolucionCompra();
void gastosPorFecha();

#endif // COMPRAS_H

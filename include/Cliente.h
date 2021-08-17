#ifndef CLIENTE_H
#define CLIENTE_H
#include <iostream>
using namespace std;
#include <clocale>
#include <cstring>
#include "Fecha.h"
#include "Persona.h"


class Cliente:public Persona{

    private:
        bool _clubPremium;
        char _telefono[12];
        char _direccion[21];

    public:
        Cliente();
        bool getClubPremium();
        char * getTel();
        char * getDirec();
        void setClubPremium (bool);
        void setTel(char *);
        void setDirec(char *);
        void cargar();
        void mostrar();
        bool escribirDisco();
        bool leerDeDisco(int);
        bool modificarEnDisco(int);

};

bool agregarCliente();
bool eliminarCliente();
int buscarCliente(int id);
int buscarClientePorTel(char * tel);
int contarClientes();
bool listarClientes();
void buscarClientexDNI();
int validarCliente(char *);

#endif // CLIENTE_H

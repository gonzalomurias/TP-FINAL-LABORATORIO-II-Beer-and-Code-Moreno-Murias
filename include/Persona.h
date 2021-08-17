#ifndef PERSONA_H
#define PERSONA_H
#include <iostream>
using namespace std;
#include <clocale>
#include <cstring>


class Persona{
    protected:
        char _dni[9];
        char _nombre[21];
        char _apellido[21];
        bool _estado;
        int _idPersona;
    public:
        //CONSTRUCTOR
        Persona();
        //GETTERS:
        char *getDNI();
        char *getNombre();
        char *getApellido();
        bool getEstado();
        int getIDP();
        //SETTERS:
        void setDNI(char *);
        void setNombre(char *);
        void setApellido(char *);
        void setEstado(bool);
        void setIDP(int);
        //OTROS MÉTODOS:
        void cargar();
        void mostrar();
        /*
        bool escribirDisco();
        bool leerDeDisco(int);
        bool modificarEnDisco(int);
        */
};
/*
bool agregarPersona();
bool listarRegistros();
bool eliminarRegistro();
int buscarProducto(int);
*/

#endif // PERSONA_H

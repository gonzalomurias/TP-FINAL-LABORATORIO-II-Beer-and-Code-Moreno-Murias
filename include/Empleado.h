#ifndef EMPLEADO_H
#define EMPLEADO_H
#include <iostream>
using namespace std;
#include <clocale>
#include <cstring>
#include "Fecha.h"
#include "Persona.h"

class Empleado:public Persona{
    private:
        float _sueldo;
        Fecha _fechaIngreso;

    public:
        Empleado();
        float getSueldo();
        Fecha getFecha();
        //SETTERS:
        void setSueldo(float);
        void setFecha(Fecha);
        //OTROS MÉTODOS:
        void cargar();
        void mostrar();
        bool escribirDisco();
        bool leerDeDisco(int);
        bool modificarEnDisco(int);

};

bool agregarEmpleado();
bool listarEmpleados();
bool eliminarEmpleado();
int buscarEmpleado(int);
int buscarEmpleado2(char *);
int contarEmpleados();

#endif // EMPLEADO_H

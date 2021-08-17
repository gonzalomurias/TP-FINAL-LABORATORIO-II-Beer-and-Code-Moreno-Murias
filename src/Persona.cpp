#include <iostream>
using namespace std;
#include <clocale>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include "rlutil.h"
using namespace rlutil;
#include "Persona.h"

//CONSTRUCTOR
Persona::Persona(){

}

//GETTERS
char * Persona::getDNI(){
    return _dni;
}

char * Persona::getNombre(){
    return _nombre;
}

char * Persona::getApellido(){
    return _apellido;
}

bool Persona::getEstado(){
    return _estado;
}

int Persona::getIDP(){
    return _idPersona;
}

//SETTERS
void Persona::setDNI(char *dni){
    strcpy(_dni, dni);
}

void Persona::setNombre(char *nombre){
    strcpy(_nombre, nombre);
}

void Persona::setApellido(char *apellido){
    strcpy(_apellido, apellido);
}

void Persona::setEstado(bool estado){
    _estado = estado;
}

void Persona::setIDP(int idP){
    _idPersona = idP;
}

//OTROS MÉTODOS
void Persona::cargar(){
    cout << "INGRESAR DATOS: " << endl;
    cout << "-------------------------" << endl;
    cin.ignore();
    cout << "DNI: ";
    cin.getline(_dni, 8);
    cin.ignore();
    cout << "NOMBRE: ";
    cin.getline(_nombre, 20);
    cin.ignore();
    cout << "APELLIDO: ";
    cin.getline(_apellido, 20);
    cout << "ID: ";
    cin >> _idPersona;
    cout << endl;
}

void Persona::mostrar(){
    if(_estado != 0){
        cout << left;
        cout << setw(5)  << _idPersona;
        cout << setw(10) << _dni;
        cout << setw(21) << _nombre;
        cout << setw(21)  << _apellido;
    }
}



#include <iostream>
using namespace std;
#include <clocale>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include "rlutil.h"
using namespace rlutil;
#include "Empleado.h"
#include "Fecha.h"

//CONSTRUCTOR
Empleado::Empleado(){

}

//GETTERS
float Empleado::getSueldo(){
    return _sueldo;
}

Fecha Empleado::getFecha(){
    return _fechaIngreso;
}
//SETTERS

void Empleado::setSueldo(float sueldo){
    _sueldo = sueldo;
}

void Empleado::setFecha(Fecha fech){
    _fechaIngreso = fech;
}
// OTROS METODOS
void Empleado::cargar(){
    Fecha obj;

    Persona::cargar();
    cout << "SUELDO: $" << endl;
    cin >> _sueldo;
    cout << "FECHA DE INGRESO: ";
    _fechaIngreso.cargar();


    while(_fechaIngreso.getDia()==0){
    cout << "Fecha inválida, ingrese nuevamente la fecha de ingreso del empleado:" << endl;
    _fechaIngreso.cargar();
    _fechaIngreso.validarFecha();
    }

    while(_fechaIngreso.getAnio() > obj.getAnio()){
        cout << "Fecha de ingreso no puede ser posterior a hoy." << endl;
        _fechaIngreso.cargar();
        _fechaIngreso.validarFecha();
    }

    while(_fechaIngreso.getAnio() == obj.getAnio() && _fechaIngreso.getMes() > obj.getMes()){
        cout << "Fecha de ingreso no puede ser posterior a hoy." << endl;
        _fechaIngreso.cargar();
        _fechaIngreso.validarFecha();
    }

    while(_fechaIngreso.getAnio() == obj.getAnio() && _fechaIngreso.getMes() == obj.getMes() && _fechaIngreso.getDia() > obj.getDia()){
        cout << "Fecha de ingreso no puede ser posterior a hoy." << endl;
        _fechaIngreso.cargar();
        _fechaIngreso.validarFecha();
    }


}

void Empleado::mostrar(){
    if(_estado != 0){
        Persona::mostrar();
        cout << left;
        cout << "$" <<setw(10) << _sueldo;
        _fechaIngreso.mostrar();
    }
}

bool Empleado::escribirDisco(){
    FILE *p;
    p=fopen("Empleados.dat", "ab");
    if(p==NULL){
        return false;
    }
    bool escribio=fwrite(this, sizeof(Empleado),1,p);
    fclose(p);
    return escribio;
}

bool Empleado::leerDeDisco(int pos){
    FILE *p;
    p = fopen("Empleados.dat", "rb");
    if (p == NULL){
        return false;
    }
    bool ok;
    fseek(p, sizeof(Empleado) * pos , 0);
    ok = fread(this, sizeof(Empleado), 1, p);
    fclose(p);
    return ok;
}

bool Empleado::modificarEnDisco(int pos){
    FILE *p;
    p=fopen("Empleados.dat", "rb+");
    if(p==NULL) return false;
    fseek(p, pos*sizeof(Empleado),0);
    bool escribio=fwrite(this, sizeof(Empleado),1,p);
    fclose(p);
    return escribio;
}

int buscarEmpleado(int id){
Empleado obj;
int pos=0;
while(obj.leerDeDisco(pos)==true){
if(obj.getIDP()==id){
	return pos;
}
pos++;
}
return -1;
}

int buscarEmpleado2(char * dni){
Empleado obj;
int pos=0;
while(obj.leerDeDisco(pos)==true){
if(strcmp(obj.getDNI(), dni)==0){
	return pos;
}
pos++;
}
return -1;
}

bool eliminarEmpleado(){
    cls();
    int id;

    gotoxy(50,15);
    cout << "INGRESE EL ID DEL EMPLEADO A ELIMINAR: ";
    cin >> id;

    Empleado reg;

    int pos=0;

    while(reg.leerDeDisco(pos))
    {

        if(id==reg.getIDP()){
           reg.setEstado(false);
           return reg.modificarEnDisco(pos);
        }
        pos++;
    }
    return false;
}

int contarEmpleados(){
    int bytes, cr;
    FILE *p;
    p = fopen("Empleados.dat", "rb");
    if (p == NULL){
        return 0;
    }
    fseek(p, 0, SEEK_END);
    bytes = ftell(p);
    cr = bytes / sizeof(Empleado);
    fclose(p);
    return cr;

}

bool agregarEmpleado(){
    bool anduvoBien;
    int id;
    char dni[8], nombre[20], apellido[20];
    float sueldo;
    Fecha fechaing, obj;

    gotoxy(50,10);
    cout << "INGRESAR NUEVO EMPLEADO: " << endl;
    gotoxy(50,11);
    cout << "-------------------------" << endl;
    id = contarEmpleados()+1;
    gotoxy(50,12);
    cout << "DNI: ";
    cin.getline(dni, 9);
    if(buscarEmpleado2(dni)!=-1){
        gotoxy(50,13);
        cout << "EMPLEADO YA REGISTRADO.";
        return false;
    }
    gotoxy(50,13);
    cout << "                                                ";
    gotoxy(50,13);
    cout << "NOMBRE: ";
    cin.getline(nombre, 20);
    gotoxy(50,14);
    cout << "APELLIDO: ";
    cin.getline(apellido, 20);
    gotoxy(50,15);
    cout << "SUELDO: $";
    cin >> sueldo;
    while(sueldo <= 0){
    gotoxy(50,16);
    cout << "SUELDO DEBE SER MAYOR A $0." << endl;
    gotoxy(59,15);
    cout << "             ";
    gotoxy(50,15);
    cout << "SUELDO: $";
    cin >> sueldo;
    }
    gotoxy(50,16);
    cout << "                                                                   ";
    gotoxy(50,16);
    cout << "FECHA DE INGRESO: ";
    fechaing.cargar2();
    fechaing.validarFecha();

    while(fechaing.getAnio() > obj.getAnio()){
        gotoxy(50,17);
        cout << "          ";
        gotoxy(50,18);
        cout << "          ";
        gotoxy(50,19);
        cout << "          ";
        gotoxy(40,21);
        cout << "Fecha de ingreso no puede ser posterior a hoy." << endl;
        fechaing.cargar2();
        fechaing.validarFecha();
    }

    while(fechaing.getAnio() == obj.getAnio() && fechaing.getMes() > obj.getMes()){
        gotoxy(50,17);
        cout << "          ";
        gotoxy(50,18);
        cout << "          ";
        gotoxy(50,19);
        cout << "          ";
        gotoxy(40,21);
        cout << "Fecha de ingreso no puede ser posterior a hoy." << endl;
        fechaing.cargar2();
        fechaing.validarFecha();
    }

    while(fechaing.getAnio() == obj.getAnio() && fechaing.getMes() == obj.getMes() && fechaing.getDia() > obj.getDia()){
        gotoxy(50,17);
        cout << "          ";
        gotoxy(50,18);
        cout << "          ";
        gotoxy(50,19);
        cout << "          ";
        gotoxy(40,21);
        cout << "Fecha de ingreso no puede ser posterior a hoy." << endl;
        fechaing.cargar2();
        fechaing.validarFecha();
    }

    while(fechaing.getDia()==0){
        gotoxy(50,17);
        cout << "          ";
        gotoxy(50,18);
        cout << "          ";
        gotoxy(50,19);
        cout << "          ";
        gotoxy(40,21);
        cout << "Fecha inválida, ingrese nuevamente la fecha de ingreso del empleado." << endl;
        fechaing.cargar2();
        fechaing.validarFecha();

    while(fechaing.getAnio() > obj.getAnio()){
        gotoxy(50,17);
        cout << "          ";
        gotoxy(50,18);
        cout << "          ";
        gotoxy(50,19);
        cout << "          ";
        gotoxy(40,21);
        cout << "Fecha de ingreso no puede ser posterior a hoy." << endl;
        fechaing.cargar2();
        fechaing.validarFecha();
    }

    while(fechaing.getAnio() == obj.getAnio() && fechaing.getMes() > obj.getMes()){
        gotoxy(50,17);
        cout << "          ";
        gotoxy(50,18);
        cout << "          ";
        gotoxy(50,19);
        cout << "          ";
        gotoxy(40,21);
        cout << "Fecha de ingreso no puede ser posterior a hoy." << endl;
        fechaing.cargar2();
        fechaing.validarFecha();
    }

    while(fechaing.getAnio() == obj.getAnio() && fechaing.getMes() == obj.getMes() && fechaing.getDia() > obj.getDia()){
        gotoxy(50,17);
        cout << "          ";
        gotoxy(50,18);
        cout << "          ";
        gotoxy(50,19);
        cout << "          ";
        gotoxy(40,21);
        cout << "Fecha de ingreso no puede ser posterior a hoy." << endl;
        fechaing.cargar2();
        fechaing.validarFecha();
    }
}


    cout << endl;

    Empleado emple;
    emple.setIDP(id);
    emple.setNombre(nombre);
    emple.setApellido(apellido);
    emple.setDNI(dni);
    emple.setEstado(1);
    emple.setSueldo(sueldo);
    emple.setFecha(fechaing);
    anduvoBien=emple.escribirDisco();
    return anduvoBien;
}

bool listarEmpleados(){
    Empleado obj;
    int pos = 0;

    gotoxy(25,8);
    cout << left;
    cout << setw(5)  << "ID";
    cout << setw(10) << "DNI";
    cout << setw(21) << "NOMBRE";
    cout << setw(21)  << "APELLIDO";
    cout << setw(11) << "SUELDO";
    cout << setw(11) << "FECHA DE INGRESO" << endl;
    gotoxy(25,9);
    cout << "--------------------------------------------------------------------------------------" << endl;
    int j = 10;

    while(obj.leerDeDisco(pos++) == 1){
    gotoxy(25,j);
    obj.mostrar();
    if (obj.getEstado() != 0){
        j++;
    }
    }
    return true;
}




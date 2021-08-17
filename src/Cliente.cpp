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
#include "Producto.h"
#include "Venta.h"
#include "Persona.h"
#include "Cliente.h"

Cliente::Cliente(){

}

bool Cliente::getClubPremium(){
    return _clubPremium;
}

char * Cliente::getTel(){
    return _telefono;
}

char * Cliente::getDirec(){
    return _direccion;

}

void Cliente::setClubPremium (bool clubP){
    _clubPremium = clubP;
}

void Cliente::setTel(char * telef){
    strcpy(_telefono, telef);
}

void Cliente::setDirec(char * direc){
    strcpy(_direccion, direc);
}

void Cliente::cargar(){
    Persona::cargar();
    cout << "TELEFONO: " << endl;
    cin >> _telefono; // VALIDAR
    cout << "DIRECCION: " << endl;
    cin.ignore();
    cin.getline(_direccion, 40);
    cout << "DESEA SER CLUB PREMIUM? 1- SI / 0- NO" << endl; // VALIDAR
    cin >> _clubPremium;
}

void Cliente::mostrar(){
    if(_estado != 0){
        Persona::mostrar();
        cout << left;
        cout <<setw(13) << _telefono;
        cout <<setw(21) << _direccion;
        if (_clubPremium == 1){
            cout <<setw(3) << "©";
        }
        else{
            cout <<setw(3) << "-";
        }
    }
}

bool Cliente::escribirDisco(){
    FILE *p;
    p=fopen("Clientes.dat", "ab");
    if(p==NULL){
        return false;
    }
    bool escribio=fwrite(this, sizeof(Cliente),1,p);
    fclose(p);
    return escribio;
}

bool Cliente::leerDeDisco(int pos){
    FILE *p;
    p = fopen("Clientes.dat", "rb");
    if (p == NULL){
        return false;
    }
    bool ok;
    fseek(p, sizeof(Cliente) * pos , 0);
    ok = fread(this, sizeof(Cliente), 1, p);
    fclose(p);
    return ok;
}

bool Cliente::modificarEnDisco(int pos){
    FILE *p;
    p=fopen("Clientes.dat", "rb+");
    if(p==NULL) return false;
    fseek(p, pos*sizeof(Cliente),0);
    bool escribio=fwrite(this, sizeof(Cliente),1,p);
    fclose(p);
    return escribio;
}

int contarClientes(){
int bytes, cr;
    FILE *p;
    p = fopen("Clientes.dat", "rb");
    if (p == NULL){
        return 0;
    }
    fseek(p, 0, SEEK_END);
    bytes = ftell(p);
    cr = bytes / sizeof(Cliente);
    fclose(p);
    return cr;
}


bool agregarCliente(){

    Cliente obj;
    bool anduvoBien;
    int id;
    char dni[9], nombre[20], apellido[20], telefono[12], direccion[20];
    bool clubPremium;

    gotoxy(50,8);
    cout << "INGRESAR NUEVO CLIENTE";
    gotoxy(50,9);
    cout << "-------------------------";
    id=1+contarClientes()+1;
    gotoxy(50,10);
    cout << "DNI: ";
    cin.getline(dni, 9);
    if(validarCliente(dni)!=-1){
    gotoxy(50,11);
    cout<<"EL CLIENTE YA SE ENCUENTRA REGISTRADO.";
    anykey();
     return false;
    }
    gotoxy(50,11);
    cout << "NOMBRE: ";
    cin.getline(nombre, 20);
    gotoxy(50,12);
    cout << "APELLIDO: ";
    cin.getline(apellido, 20);
    gotoxy(50,13);
    cout << "TELEFONO: ";
    cin >> telefono;
    gotoxy(50,14);
    cout << "DIRECCION: ";
    cin.ignore();
    cin.getline(direccion, 20);
    gotoxy(50,15);
    cout << "DESEA SER CLUB PREMIUM? 1- SI / 0- NO > ";
    cin >> clubPremium;
    cout << endl;

    obj.setIDP(id);
    obj.setNombre(nombre);
    obj.setApellido(apellido);
    obj.setDNI(dni);
    obj.setEstado(1);
    obj.setTel(telefono);
    obj.setDirec(direccion);
    obj.setClubPremium(clubPremium);
    anduvoBien=obj.escribirDisco();
    return anduvoBien;
}

int buscarCliente(int id){

Cliente obj;
int pos=0;
while(obj.leerDeDisco(pos)==true){
if(obj.getIDP()==id){
	return pos;
}
pos++;
}
return -1;
}


int validarCliente(char *dni){

Cliente obj;
int pos=0;
while(obj.leerDeDisco(pos)==true){
if(strcmp(obj.getDNI(),dni)==0){
	return pos;
}
pos++;
}
return -1;
}

int buscarClientePorTel(char * tel){

Cliente obj;
int pos=0;
while(obj.leerDeDisco(pos)==true){
if(strcmp(obj.getTel(), tel)==0){
	return pos;
}
pos++;
}
return -1;
}


bool eliminarCliente(){
    cls();
    int id;

    gotoxy(50,15);
    cout << "INGRESE EL ID DEL CLIENTE A ELIMINAR: ";
    cin >> id;

    Cliente reg;

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

bool listarClientes(){
    Cliente obj;
    int pos = 0;

    gotoxy(7,3);
    cout << left;
    cout << setw(5)  << "ID";
    cout << setw(10) << "DNI";
    cout << setw(21) << "NOMBRE";
    cout << setw(21)  << "APELLIDO";
    cout << setw(13) << "TELEFONO";
    cout << setw(21) << "DIRECCION";
    cout << setw(3) << "CLUB PREMIUM?";
    gotoxy(7,4);
    cout << "-----------------------------------------------------------------------------------------------------------" << endl;
    int j = 5;

    while(obj.leerDeDisco(pos++) == 1){
    gotoxy(7,j);
    obj.mostrar();
    if (obj.getEstado() != 0){
        j++;
    }
    }
    return true;
}

void buscarClientexDNI(){
Cliente obj;
int pos=0;
char dni[9];
gotoxy(40,8);
cout<< "INGRESE DNI DEL CLIENTE: ";
cin>>dni;

while(obj.leerDeDisco(pos)==true){
if(strcmp(obj.getDNI(), dni)==0){
    gotoxy(7,15);
    cout << left;
    cout << setw(5)  << "ID";
    cout << setw(10) << "DNI";
    cout << setw(21) << "NOMBRE";
    cout << setw(21)  << "APELLIDO";
    cout << setw(13) << "TELEFONO";
    cout << setw(21) << "DIRECCION";
    cout << setw(3) << "CLUB PREMIUM?";
    gotoxy(7,16);
    cout << "-----------------------------------------------------------------------------------------------------------" << endl;
    gotoxy(7,17);
	obj.mostrar();
	return;
}
pos++;
}
gotoxy(45,15);
cout<< "NO SE ENCONTRÓ EL CLIENTE.";
anykey();
return;
}



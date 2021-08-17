#include <iostream>
using namespace std;
#include <clocale>
#include <cstdlib>
#include <cstring>
#include <conio.h>
#include <iomanip>
#include "rlutil.h"
using namespace rlutil;
#include "Fecha.h"
#include <ctime>
#include "Usuarios.h"

Usuarios::Usuarios(){

}

char * Usuarios::getUser(){
    return _user;
}

char * Usuarios::getPass(){
    return _passw;
}

int Usuarios::getIDUser(){
    return _idUser;
}

void Usuarios::setUser(char * usuario){
    strcpy(_user, usuario);
}

void Usuarios::setPass(char * contrasenia){
    strcpy(_passw, contrasenia);
}

void Usuarios::setIDUser(int id){
    _idUser = id;
}

void Usuarios::cargar(){
    cout << "INGRESE NUEVO USUARIO (MÁXIMO 10 CARACTERES): ";
    cin >> _user;
    cout << "INGRESE CONTRASEÑA (MÁXIMO 10 CARACTERES): ";
    cin >> _passw;
    _idUser = contarUsuarios()+1;
}

void Usuarios::mostrar(){
    cout << "ID USER: " << _idUser << endl;
    cout << "USUARIO: " << _user << endl;
    cout << "CONTRASEÑA: " << _passw << endl;
}
bool Usuarios::escribirDisco(){
    FILE *p;
    p=fopen("Usuarios.dat", "ab");
    if(p==NULL){
        return false;
    }
    bool escribio=fwrite(this, sizeof(Usuarios),1,p);
    fclose(p);
    return escribio;
}

bool Usuarios::leerDeDisco(int pos){
    FILE *p;
    p = fopen("Usuarios.dat", "rb");
    if (p == NULL){
        return false;
    }
    bool ok;
    fseek(p, sizeof(Usuarios) * pos , 0);
    ok = fread(this, sizeof(Usuarios), 1, p);
    fclose(p);
    return ok;
}

bool Usuarios::modificarEnDisco(int pos){
    FILE *p;
    p=fopen("Usuarios.dat", "rb+");
    if(p==NULL) return false;
    fseek(p, pos*sizeof(Usuarios),0);
    bool escribio=fwrite(this, sizeof(Usuarios),1,p);
    fclose(p);
    return escribio;
}

int contarUsuarios(){
    int bytes, cr;
    FILE *p;
    p = fopen("Usuarios.dat", "rb");
    if (p == NULL){
        return 0;
    }
    fseek(p, 0, SEEK_END);
    bytes = ftell(p);
    cr = bytes / sizeof(Usuarios);
    fclose(p);
    return cr;
}

bool agregarUsuario(){

    Usuarios user;
    char usuario[10], contrasenia[10], contrasenia2[10];
    bool anduvoBien;
    int IDUser;

    gotoxy(40,15);
    cout << "INGRESE NUEVO USUARIO (MÁXIMO 10 CARACTERES): ";
    cin.getline(usuario, 10);
    gotoxy(40,16);
    cout << "INGRESE CONTRASEÑA (MÁXIMO 10 CARACTERES): ";
    cin.getline(contrasenia, 10);
    gotoxy(40,17);
    cout << "REINGRESE CONTRASEÑA (MÁXIMO 10 CARACTERES): ";
    cin.getline(contrasenia2,10);

    while(strcmp(contrasenia, contrasenia2)!=0){
    cls();
    gotoxy(40,15);
    cout << "CONTRASEÑAS NO COINCIDEN ";
    gotoxy(40,16);
    cout << "INGRESE CONTRASEÑA (MÁXIMO 10 CARACTERES): ";
    cin.getline(contrasenia, 10);
    gotoxy(40,17);
    cout << "REINGRESE CONTRASEÑA (MÁXIMO 10 CARACTERES): ";
    cin.getline(contrasenia2,10);
    }

    IDUser = contarUsuarios()+1;
    user.setIDUser(IDUser);
    user.setUser(usuario);
    user.setPass(contrasenia);

    anduvoBien = user.escribirDisco();
    return anduvoBien;
}

bool listarUsuarios(){

    Usuarios obj;
    int pos = 0;
    char usAux[10];
    int id;

    gotoxy(50,8);
    cout << left;
    cout << setw(5)  << "ID";
    cout << setw(11) << "USUARIO";
    gotoxy(50,9);
    cout << "---------------" << endl;
    int j = 10;

    while(obj.leerDeDisco(pos++) == 1){
    gotoxy(50,j);
    cout << setw(5) << obj.getIDUser();
    cout << setw(11) << obj.getUser();
    j++;
    }
    return true;

}

bool buscarUsuario(char *user, char *pass){
Usuarios obj;
int pos=0;

while(obj.leerDeDisco(pos++)){
    if((strcmp(obj.getUser(),user)==0) && (strcmp(obj.getPass(),pass)==0)){
        return true;
    }
}
return false;
}

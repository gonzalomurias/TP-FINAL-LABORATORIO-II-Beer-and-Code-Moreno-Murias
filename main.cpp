#include <iostream>
using namespace std;
#include <clocale>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <conio.h>
#include "rlutil.h"
using namespace rlutil;
#include "Producto.h"
#include "Funciones.h"
#include "Usuarios.h"

int main(){
setlocale(LC_ALL, "Spanish");

Usuarios obj;
char usuario[10];
char contrasenia[10];
bool ingresa = false;
int pos;
int ok;

presentacion();
anykey();

do{
    pos = 0;
    cls();
    gotoxy(50,12);

    cout << "INGRESE USUARIO: ";
    cin.getline(usuario, 10);
    gotoxy(50,13);
    cout << "INGRESE CONTRASEÑA: ";
    leerPass(contrasenia);
    //cin>> contrasenia;

    ok=buscarUsuario(usuario, contrasenia);

    if(ok==true){
    ingresa=true;
    menuPrincipal();
    }
    else{
    gotoxy(30,20);
    cout << "Usuario y/o Contraseña incorrecta. Vuelva a ingresar los datos." << endl;;
    }
    anykey();
    cin.ignore();
}while(ingresa == false);



return 0;
}

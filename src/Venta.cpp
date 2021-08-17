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
#include "Cliente.h"


Venta::Venta(){
}

int Venta::getID(){
return _idVenta;
}
Fecha Venta::getFecha(){
return _fechaVenta;
	}

int Venta::getIDC(){
return _idCliente;
}

int Venta::getFormaP(){
return _formaPago;
}
bool Venta::getDelivery(){
return _delivery;
}

float Venta::getTotal(){
return _total;
}

bool Venta::getEstado(){
return _estado;
}

void Venta::setEstado(bool est){
    _estado = est;
}

void Venta::setID(int id){
_idVenta=id;
}
void Venta::setFecha(Fecha f){
_fechaVenta=f;
}
void Venta::setIDC(int idc){
_idCliente=idc;

}

void Venta::setFormaP(int fp){
_formaPago=fp;
}

void Venta::setDelivery(bool d){
_delivery=d;
}

void Venta::setTotal(float total){
_total=total;

}

void Venta::mostrar(){
    if(_estado == 1){
    cout << _idVenta << endl;
    _fechaVenta.mostrar();
    cout << _idCliente << endl;
    cout << _formaPago << endl;
    cout << _delivery << endl;
    cout << "$ " << _total << endl;
}
}
bool Venta::escribirDisco(){
 FILE *p;
    p=fopen("Ventas.dat", "ab");
    if(p==NULL){
        return false;
    }
    bool escribio=fwrite(this, sizeof(Venta),1,p);
    fclose(p);
    return escribio;
}

bool Venta::leerDisco(int pos){
FILE *p;
    p = fopen("Ventas.dat", "rb");
    if (p == NULL){
        return false;
    }
    bool ok;
    fseek(p, sizeof(Venta) * pos , 0);
    ok = fread(this, sizeof(Venta), 1, p);
    fclose(p);
    return ok;
}

bool Venta::modificarEnDisco(int pos){
    FILE *p;
    p=fopen("Ventas.dat", "rb+");
    if(p==NULL) return false;
    fseek(p, pos*sizeof(Venta),0);
    bool escribio=fwrite(this, sizeof(Venta),1,p);
    fclose(p);
    return escribio;
}

int contarVentas(){
int bytes, cr;
    FILE *p;
    p = fopen("Ventas.dat", "rb");
    if (p == NULL){
        return 0;
    }
    fseek(p, 0, SEEK_END);
    bytes = ftell(p);
    cr = bytes / sizeof(Venta);
    fclose(p);
    return cr;
}

void listarVentas(){
Venta obj;
int pos=0;

while(obj.leerDisco(pos++)==1){
    obj.mostrar();
}
}

void leerVentas(Venta *vec, int cant){

    int i;
    for (i=0; i<cant; i++){
        vec[i].leerDisco(i);
    }

}

void ventasPorCliente(){
Venta reg;
Cliente obj;
int pos=0;
int id=-1;
char dni[9];
char formaPago[13];

    gotoxy(45,8);
    cout<< "INGRESE DNI DEL CLIENTE: ";
    cin>> dni;

    while(obj.leerDeDisco(pos)==true){
        if(strcmp(obj.getDNI(), dni)==0){
        id=obj.getIDP();
        }
        pos++;
    }

    if(id!=-1){
        cls();
        gotoxy(45,8);
        cout << left;
        cout << setw(5)  << "ID";
        cout << setw(25) << "FORMA DE PAGO";
        cout << setw(15)  << "TOTAL VENTA";
        gotoxy(45,9);
        cout << "-------------------------------------------";
        pos=0;
        int j=10;
        while(reg.leerDisco(pos++)){
            if(reg.getIDC()==id){
                if(reg.getFormaP() == 1){
                    strcpy(formaPago, "EFECTIVO");
            }
            if(reg.getFormaP() == 2){
                strcpy(formaPago, "MERCADOPAGO");
            }
            if(reg.getFormaP() == 3){
                strcpy(formaPago, "CRÉDITO");
            }
            if(reg.getFormaP() == 4){
                strcpy(formaPago, "DÉBITO");
            }
        gotoxy(45,j);
        cout << left;
        cout << setw(5)  << reg.getID();
        cout << setw(25) << formaPago;
        cout << setw(1)  << "$" << setw(7) << reg.getTotal() << endl;
        j++;
    }
}
    anykey();
    return;
}

gotoxy(45,15);
cout<< "NO SE ENCONTRÓ EL CLIENTE.";
anykey();
return;
}



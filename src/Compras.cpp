#include <iostream>
using namespace std;
#include <clocale>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include "rlutil.h"
using namespace rlutil;
#include "Fecha.h"
#include <ctime>
#include "Compras.h"
#include "Funciones.h"

Compras::Compras(){
}

int Compras::getIDCompra(){
    return _idCompra;
}

Fecha Compras::getFechaCompra(){
    return _fechaCompra;
}

float Compras::getImporteCompra(){
    return _importeCompra;
}

char * Compras::getMotivo(){
    return _motivo;
}

bool Compras::getEstado(){
    return _estado;
}

void Compras::setIDCompra(int id){
    _idCompra = id;
}

void Compras::setFechaCompra(Fecha f){
    _fechaCompra = f;
}

void Compras::setImporteCompra(float importe){
    _importeCompra = importe;
}

void Compras::setMotivo(char * motivo){
    strcpy(_motivo, motivo);
}

void Compras::setEstado(bool est){
    _estado = est;
}

void Compras::cargar(){

}

void Compras::mostrar(){

}

bool Compras::escribirDisco(){
    FILE *p;
    p=fopen("Compras.dat", "ab");
    if(p==NULL){
        return false;
    }
    bool escribio=fwrite(this, sizeof(Compras),1,p);
    fclose(p);
    return escribio;
}

bool Compras::leerDisco(int pos){
    FILE *p;
    p = fopen("Compras.dat", "rb");
    if (p == NULL){
        return false;
    }
    bool ok;
    fseek(p, sizeof(Compras) * pos , 0);
    ok = fread(this, sizeof(Compras), 1, p);
    fclose(p);
    return ok;
}

bool Compras::modificarEnDisco(int pos){
    FILE *p;
    p=fopen("Compras.dat", "rb+");
    if(p==NULL) return false;
    fseek(p, pos*sizeof(Compras),0);
    bool escribio=fwrite(this, sizeof(Compras),1,p);
    fclose(p);
    return escribio;
}

int contarCompras(){
    int bytes, cr;
    FILE *p;
    p = fopen("Compras.dat", "rb");
    if (p == NULL){
        return 0;
    }
    fseek(p, 0, SEEK_END);
    bytes = ftell(p);
    cr = bytes / sizeof(Compras);
    fclose(p);
    return cr;
}

void nuevaCompra(){
    Compras obj;
    int opc;
    bool seguir=1;
    int idCompra;
    float importeCompra;
    char motivo[50];

    cls();
    idCompra=contarCompras()+1;
    obj.setIDCompra(idCompra);
    gotoxy(40,10);
    cout << "MOTIVO DE LA COMPRA (MÁX 50 CARACTERES): ";
    cin.getline(motivo,50);
    gotoxy(40,11);
    cout << "IMPORTE: $";
    cin >> importeCompra;
    while(importeCompra <= 0){
        gotoxy(40,14);
        cout << "IMPORTE DEBE SER MAYOR A 0." << endl;
        anykey();
        return nuevaCompra();
    }
    obj.setMotivo(motivo);
    obj.setImporteCompra(importeCompra);
    obj.escribirDisco();
}

bool devolucionCompra(){

    cls();
    int id;
    int opc;

    gotoxy(50,8);
    cout << "    ELIMINAR COMPRA";
    gotoxy(50,9);
    cout << "-------------------------";
    gotoxy(50,10);
    cout << "INGRESE ID DE COMPRA: ";
    gotoxy(50,11);
    cout << "> ";
    cin >> id;

    Compras reg;
    int pos=0;

    pos = 0;
    while(reg.leerDisco(pos)){
    if(reg.getIDCompra() == id){
        if (reg.getEstado()!=0){
            gotoxy(30,15);
            cout << left;
            cout << setw(5)  << "ID";
            cout << setw(17) << "FECHA DE COMPRA";
            cout << setw(50) << "DESCRIPCION";
            cout << setw(7)  << "TOTAL";
            gotoxy(30,16);
            cout << "-----------------------------------------------------------------------------" << endl;
            gotoxy(30,17);
            cout << left;
            cout << setw(5)  << reg.getIDCompra();
            cout << setw(2) << reg.getFechaCompra().getDia();
            cout << setw(1) << "/";
            cout << setw(2) << reg.getFechaCompra().getMes();
            cout << setw(1) << "/";
            cout << setw(11) << reg.getFechaCompra().getAnio();
            cout << setw(50) << reg.getMotivo();
            cout << setw(1)  << "$" << setw(7) << reg.getImporteCompra() << endl;

            gotoxy(30,19);
            cout << "DESEA ELIMINAR LA COMPRA? 1-SI / 0-NO > ";
            cin >> opc;

            if(opc != 1){
                menuCompras();
            }

            reg.setEstado(0);
            return reg.modificarEnDisco(pos);
        }
        else{
            return false;
        }
    }
    pos++;
    }
}

void gastosPorFecha(){
Fecha primer, actual;
Compras obj;

    gotoxy(35,10);
    cout << "Ingresar fecha de inicio en formato DD/MM/AAAA" << endl;
    primer.cargar();
    primer.validarFecha();

    while(primer.getAnio() > actual.getAnio()){
        cls();
        gotoxy(35,10);
        cout << "Fecha ingresada no puede ser posterior a hoy." << endl;;
        primer.cargar();
        primer.validarFecha();
    }

    while(primer.getAnio() == actual.getAnio() && primer.getMes() > actual.getMes()){
        cls();
        gotoxy(35,10);
        cout << "Fecha ingresada no puede ser posterior a hoy." << endl;;
        primer.cargar();
        primer.validarFecha();
    }

    while(primer.getAnio() == actual.getAnio() && primer.getMes() == actual.getMes() && primer.getDia() > actual.getDia()){
        cls();
        gotoxy(35,10);
        cout << "Fecha ingresada no puede ser posterior a hoy." << endl;;
        primer.cargar();
        primer.validarFecha();
    }

    while(primer.getDia()==0){
    cls();
    gotoxy(35,10);
    cout << "Fecha inválida, ingrese nuevamente la fecha de inicio en formato DD/MM/AAAA:" << endl;
    primer.cargar();
    primer.validarFecha();

    while(primer.getAnio() > actual.getAnio()){
        cls();
        gotoxy(35,10);
        cout << "Fecha ingresada no puede ser posterior a hoy." << endl;;
        primer.cargar();
        primer.validarFecha();
    }

    while(primer.getAnio() == actual.getAnio() && primer.getMes() > actual.getMes()){
        cls();
        gotoxy(35,10);
        cout << "Fecha ingresada no puede ser posterior a hoy." << endl;;
        primer.cargar();
        primer.validarFecha();
    }

    while(primer.getAnio() == actual.getAnio() && primer.getMes() == actual.getMes() && primer.getDia() > actual.getDia()){
        cls();
        gotoxy(35,10);
        cout << "Fecha ingresada no puede ser posterior a hoy." << endl;;
        primer.cargar();
        primer.validarFecha();
    }
}


    int pos = 0;
    float totalDelDia = 0;

    cls();
    gotoxy(50,3);
    cout << "GASTOS DEL DÍA " << primer.getDia() << "/" << primer.getMes() << "/" << primer.getAnio();
    gotoxy(50,4);
    cout << "-------------------------";

    int j = 9;

    gotoxy(25,7);
    cout << left;
    cout << setw(5)  << "ID";
    cout << setw(17) << "FECHA DE COMPRA";
    cout << setw(50) << "DESCRIPCION";
    cout << setw(7)  << "TOTAL";
    gotoxy(25,8);
    cout << "------------------------------------------------------------------------------" << endl;

    while(obj.leerDisco(pos++)==true){
        if(obj.getFechaCompra()==primer){
            gotoxy(25,j);
            cout << left;
            cout << setw(5)  << obj.getIDCompra();
            cout << setw(2) << obj.getFechaCompra().getDia();
            cout << setw(1) << "/";
            cout << setw(2) << obj.getFechaCompra().getMes();
            cout << setw(1) << "/";
            cout << setw(11) << obj.getFechaCompra().getAnio();
            cout << setw(50) << obj.getMotivo();
            cout << setw(1)  << "$" << setw(7) << obj.getImporteCompra() << endl;
            totalDelDia += obj.getImporteCompra();
            j++;
        }
    }

    gotoxy(25,j);
    cout << "------------------------------------------------------------------------------" << endl;
    gotoxy(82,j+1);
    cout << "TOTAL GASTADO: $" << totalDelDia;


}

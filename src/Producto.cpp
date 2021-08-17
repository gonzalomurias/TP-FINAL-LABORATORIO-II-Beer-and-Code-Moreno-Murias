#include <iostream>
using namespace std;
#include <clocale>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include "rlutil.h"
using namespace rlutil;
#include "Producto.h"
#include "Funciones.h"
#include "DetalleVenta.h"
#include "RankingProductos.h"
#include <cstdio>
#include "Venta.h"

//CONSTRUCTOR
Producto::Producto(){

}

//GETTERS
int Producto::getID(){
    return _idProducto;
}

int Producto::getStock(){
    return _stock;
}

char * Producto::getDesc(){
    return _descripcion;
}

float Producto::getPrecio(){
    return _precio;
}

bool Producto::getEstado(){
    return _estado;
}

//SETTERS
void Producto::setID(int idProducto){
    _idProducto = idProducto;
}

void Producto::setStock(int stock){
    _stock = stock;
}

void Producto::setDesc(char *descripcion){
    strcpy(_descripcion, descripcion);
}

void Producto::setPrecio(float precio){
    _precio = precio;
}

void Producto::setEstado(bool estado){
    _estado = estado;
}

//OTROS MÉTODOS
void Producto::cargar(){
    cout << "INGRESAR NUEVO PRODUCTO: " << endl;
    cout << "-------------------------" << endl;
    cout << "ID: ";
    cin >> _idProducto;
    cin.ignore();
    cout << "DESCRIPCIÓN: ";
    cin.getline(_descripcion, 30);
    cout << "PRECIO: $";
    cin >> _precio;
    cout << "STOCK: ";
    cin >> _stock;
    cout << endl;
}

void Producto::mostrar(){
    if(_estado != 0){
        cout << left;
        cout << setw(5)  << _idProducto;
        cout << setw(31) << _descripcion;
        cout << "$" << setw(10) << _precio;
        cout << setw(10)  << _stock;
    }
}

bool Producto::escribirDisco(){
    FILE *p;
    p=fopen("Producto.dat", "ab");
    if(p==NULL){
        return false;
    }
    bool escribio=fwrite(this, sizeof(Producto),1,p);
    fclose(p);
    return escribio;
}

bool Producto::leerDeDisco(int pos){
    FILE *p;
    p = fopen("Producto.dat", "rb");
    if (p == NULL){
        return false;
    }
    bool ok;
    fseek(p, sizeof(Producto) * pos , 0);
    ok = fread(this, sizeof(Producto), 1, p);
    fclose(p);
    return ok;
}

bool Producto::modificarEnDisco(int pos){
    FILE *p;
    p=fopen("Producto.dat", "rb+");
    if(p==NULL) return false;
    fseek(p, pos*sizeof(Producto),0);
    bool escribio=fwrite(this, sizeof(Producto),1,p);
    fclose(p);
    return escribio;
}

int buscarProducto(int id){
Producto obj;
int pos=0;
while(obj.leerDeDisco(pos)==true){
if(obj.getID()==id){
	return pos;
}
pos++;
}
return -1;
}


bool eliminarRegistro(){

    cls();
    int id, pos;

    gotoxy(40,8);
    cout << "             ELIMINAR PRODUCTO " << endl;
    gotoxy(40,9);
    cout << "-------------------------------------------" << endl;
    gotoxy(40,10);
    cout << "INGRESE ID DEL PRODUCTO A ELIMINAR: ";
    cin >> id;
    cin.ignore();

    Producto reg;

    pos=0;

    while(reg.leerDeDisco(pos))
    {

        if(id==reg.getID() && reg.getEstado() == true){
           reg.setEstado(false);
           reg.setStock(0);
           return reg.modificarEnDisco(pos);
        }
        /*else{
                gotoxy(40, 15);
                cout << "PRODUCTO INEXISTENTE. REINGRESE ID.";
                return false;
        }*/

        pos++;
    }
    return false;
}

bool agregarRegistro(){
    bool anduvoBien;
    int id, stock;
    char descrip[30];
    float prec;

    gotoxy(40,8);
    cout << "          INGRESAR NUEVO PRODUCTO " << endl;
    gotoxy(40,9);
    cout << "-------------------------------------------" << endl;

    id = contarProductos()+1;
    gotoxy(40,10);
    cout << "DESCRIPCIÓN: ";
    cin.getline(descrip, 30);
    gotoxy(40,11);
    cout << "PRECIO: $";
    cin >> prec;
    cin.ignore();
    gotoxy(40,12);
    cout << "STOCK: ";
    cin >> stock;
    cout << endl;

    Producto obj;
    obj.setID(id);
    obj.setDesc(descrip);
    obj.setPrecio(prec);
    obj.setStock(stock);
    obj.setEstado(1);
    anduvoBien=obj.escribirDisco();
    return anduvoBien;
}

bool listarRegistros(){
    setlocale(LC_ALL, "Spanish");
    Producto obj;
    int pos = 0;

    gotoxy(30,8);
    cout << left;
    cout << setw(5)  << "ID";
    cout << setw(31) << "DESCRIPCION";
    cout << setw(10) << "PRECIO";
    cout << setw(10)  << "STOCK" << endl;
    gotoxy(30,9);
    cout << "---------------------------------------------------------" << endl;
    int j = 10;

    while(obj.leerDeDisco(pos++) == 1){
    gotoxy(30,j);
    obj.mostrar();
    if (obj.getEstado() != 0){
        j++;
    }
    }
    return true;
}

bool listarRegistros2(){
    setlocale(LC_ALL, "Spanish");
    Producto obj;
    int pos = 0;

    gotoxy(1,1);
    cout << left;
    cout << setw(5)  << "ID";
    cout << setw(31) << "DESCRIPCION";
    cout << setw(10) << "PRECIO";
    cout << setw(10)  << "STOCK" << endl;
    gotoxy(1,2);
    cout << "-----------------------------------------------------" << endl;
    int j = 3;

    while(obj.leerDeDisco(pos++) == 1){
    gotoxy(1,j);
    obj.mostrar();
    if (obj.getEstado() != 0){
        j++;
    }
    }
    return true;
}

int contarProductos(){
    int bytes, cr;
    FILE *p;
    p = fopen("Producto.dat", "rb");
    if (p == NULL){
        return 0;
    }
    fseek(p, 0, SEEK_END);
    bytes = ftell(p);
    cr = bytes / sizeof(Producto);
    fclose(p);
    return cr;
}

void buscarProductosxRangoPrecio(){

Producto obj;
int pos=0;
float precio1, precio2, aux;

gotoxy(40,8);
cout<< "INGRESE PRECIO INICIO: $";
cin>>precio1;

while(precio1<=0){
    cls();
    gotoxy(40,9);
    cout << "PRECIO DEBE SER MAYOR A 0" << endl;
    gotoxy(40,8);
    cout << "INGRESE PRECIO INICIO: $";
    cin >> precio1;
}
cls();

gotoxy(40,8);
cout<< "INGRESE PRECIO FIN: $";
cin>>precio2;

while(precio2<=0){
    cls();
    gotoxy(40,9);
    cout << "PRECIO DEBE SER MAYOR A 0" << endl;
    gotoxy(40,8);
    cout << "INGRESE PRECIO FIN: $";
    cin >> precio2;
}

if (precio1 > precio2){
    aux = precio1;
    precio1 = precio2;
    precio2 = aux;

}

cls();

gotoxy(40,5);
    cout << left;
    cout << setw(5)  << "ID";
    cout << setw(31) << "DESCRIPCION";
    cout << setw(10) << "PRECIO";
    cout << setw(10)  << "STOCK" << endl;
    gotoxy(40,6);
    cout << "-----------------------------------------------------" << endl;
    int j = 7;
while(obj.leerDeDisco(pos++)==true){
if(obj.getPrecio() >= precio1 && obj.getPrecio() <= precio2){
    gotoxy(40,j);
    obj.mostrar();
    if (obj.getEstado() != 0){
        j++;
    }
}
}
return;
}


void ordenarRanking(RankingProductos *vec, int tam){
 int i, j, posM;

    for(i=0; i<tam-1; i++){
        posM = i;
        for(j=i+1; j<tam; j++){
            if (vec[j].getCantidad() > vec[posM].getCantidad()){
                posM = j;
            }
        }
        RankingProductos aux = vec[i];
        vec[i] = vec[posM];
        vec[posM] = aux;
    }

}

void leerRanking(RankingProductos *vec, int tam){
int i;

for(i=0;i<tam;i++){
    vec[i].leerDeDisco(i);
}
}

int cantidadVentas(int ID){
DetalleVenta obj;
int pos=0;
int cantidad=0;

while(obj.leerDisco(pos++)){
    if(obj.getIDProducto()==ID){
        cantidad+=obj.getCantidad();
    }
}
 return cantidad;
}

void rankingProductosMasVendidos(){
RankingProductos obj;
Producto aux;
int CV;
int pos=0;




while(aux.leerDeDisco(pos++)){
    obj.setIDP(aux.getID());
    obj.setDesc(aux.getDesc());
    obj.setPrecioU(aux.getPrecio());
    CV=cantidadVentas(aux.getID());
    obj.setCantidad(CV);
    obj.grabarEnDisco();
}


RankingProductos *vec;
int cant=contarRegistros();

vec = new RankingProductos[cant];
if(vec==NULL){
    return;
}

leerRanking(vec, cant);
ordenarRanking(vec, cant);
gotoxy(55,5);
cout << "RANKING DE PRODUCTOS" << endl;
gotoxy(40,6);
cout << "-------------------------------------------------" << endl;
gotoxy(40,7);
cout << left;
cout << setw(30) << "DESCRIPCION";
cout << setw(12) << "CANTIDAD";
cout << setw(8) << "TOTAL";
gotoxy(40,8);
cout << "-------------------------------------------------";
int z = 9;
    for(int i=0; i<cant; i++){
        if(vec[i].getCantidad()>0){
        gotoxy(40, z);
        cout << left;
        cout << setw(30) << vec[i].getDesc();
        cout << setw(12) << vec[i].getCantidad();
        cout << "$" << setw(8) << (float)vec[i].getCantidad()*vec[i].getPrecioU();
        }
        z++;
    }

    remove("RankingProductos.dat");
 //remove("C:\\Users\\gonza\\Desktop\\beer&codeFINAL\\RankingProductos.dat"); //CAMBIARLO EN TU PC
delete vec;
}

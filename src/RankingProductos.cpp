
#include <iostream>
using namespace std;
#include <clocale>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include "rlutil.h"
using namespace rlutil;
#include "Producto.h"
#include "DetalleVenta.h"
#include "RankingProductos.h"


char *RankingProductos::getDesc(){
return _desc;}

float RankingProductos::getPrecioU(){
return _precio;}

int RankingProductos::getCantidad(){
return _cantidad;}

void RankingProductos::setIDP(int id){
_idP=id; }

void RankingProductos::setDesc(char *des){
strcpy(_desc,des);}

void RankingProductos::setCantidad(int cant){
_cantidad=cant;
}

void RankingProductos::setPrecioU(float precio){
_precio=precio;
}

bool RankingProductos::leerDeDisco(int pos){
 FILE *p;
    p = fopen("RankingProductos.dat", "rb");
    if (p == NULL){
        return false;
    }
    bool ok;
    fseek(p, sizeof(RankingProductos) * pos , 0);
    ok = fread(this, sizeof(RankingProductos), 1, p);
    fclose(p);
    return ok;

}

bool RankingProductos::grabarEnDisco(){
    FILE *p;
    p=fopen("RankingProductos.dat", "ab");
    if(p==NULL){
        return false;
    }
    bool escribio=fwrite(this, sizeof(RankingProductos),1,p);
    fclose(p);
    return escribio;
}

void RankingProductos::mostrar(){
cout<<_idP<<endl;
cout<<_desc<<endl;
cout<<_cantidad<<endl;
cout<<_precio<<endl;

}

int contarRegistros(){
int bytes, cr;
    FILE *p;
    p = fopen("RankingProductos.dat", "rb");
    if (p == NULL){
        return 0;
    }
    fseek(p, 0, SEEK_END);
    bytes = ftell(p);
    cr = bytes / sizeof(RankingProductos);
    fclose(p);
    return cr;
}

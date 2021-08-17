#include <iostream>
using namespace std;
#include <clocale>
#include <cstdlib>
#include <cstring>
#include <conio.h>
#include <iomanip>
#include "rlutil.h"
using namespace rlutil;
#include "Producto.h"
#include "Funciones.h"
#include "Fecha.h"
#include "Empleado.h"
#include "Persona.h"
#include "Venta.h"
#include "DetalleVenta.h"
#include "Cliente.h"
#include "Usuarios.h"
#include "Compras.h"

void menuPrincipal(){

    int opcion;

    do{

    cls();
    gotoxy(45,8);
    cout << "-       beer&code CERVECERÍA       -"<< endl;
    gotoxy(45,9);
    cout << "-----------------------------------"<< endl;
    gotoxy(45,10);
    cout << "MENÚ PRINCIPAL"<< endl;
    gotoxy(45,11);
    cout << "-----------------------------------"<< endl;
    gotoxy(45,12);
    cout << "1 - CARTA                           "<< endl;
    gotoxy(45,13);
    cout << "2 - VENTAS                   "<< endl;
    gotoxy(45,14);
    cout << "3 - COMPRAS                   "<< endl;
    gotoxy(45,15);
    cout << "4 - CLIENTES                      "<< endl;
    gotoxy(45,16);
    cout << "5 - USUARIOS                  "<< endl;
    gotoxy(45,17);
    cout << "6 - INFORMES                  "<< endl;
    gotoxy(45,18);
    cout << "7 - EMPLEADOS                 " << endl;
    gotoxy(45,19);
    cout << "-----------------------------------"<< endl;
    gotoxy(45,20);
    cout << "0 - SALIR"<< endl;
    gotoxy(45,23);
    cout  << "> ";
    gotoxy(46,23);
    cin>> opcion;
    cin.ignore();

    switch(opcion){

        case 1:
            cls();
            menuCarta();
        break;

        case 2:
            cls();
            menuVenta();
        break;

        case 3:
            cls();
            menuCompras();

        break;

        case 4:
            cls();
            menuClientes();
        break;

        case 5:
            cls();
            menuUsuarios();;
        break;

        case 6:
            cls();
            menuInformes();
        break;

        case 7:
            cls();
            menuEmpleados();
        break;

        case 0:
            char seguir;
            cls();
            gotoxy(40,15);
            cout << "Está seguro de que quiere salir? S/N:" << endl;
            gotoxy(40,16);
            cout << ">";
            gotoxy(41,16);
            cin >> seguir;

            switch(seguir){
                case 'S':
                case 's':
                    cls();
                    gotoxy(40,15);
                    msleep(500);
                    cout << "Saliendo  ";
                    gotoxy(50,15);
                    msleep(500);
                    cout << "... ";
                    gotoxy(54,15);
                    msleep(500);
                    cout << "...";
                    resetColor();
                    setBackgroundColor(0);
                    setColor(0);
                    exit(0);
                    cout << endl << endl << endl << endl;
                break;

                case 'N':
                case 'n':
                    cls();
                    return menuPrincipal();
                break;
            }

        break;

        default:
            cls();
            gotoxy(40,15);
            cout << "Ingresó una opción errónea.";
            gotoxy(40,16);
            system("pause");
            return menuPrincipal();
        break;
    }

    cin.ignore();
    anykey();

    }while(opcion != 0);

}

void menuCarta(){

    int opcion;
    do{
        cls();
        gotoxy(45,8);
        cout << "-       beer&code CERVECERÍA       -"<< endl;
        gotoxy(45,9);
        cout << "-----------------------------------"<< endl;
        gotoxy(45,10);
        cout << "MENÚ CARTA"<< endl;
        gotoxy(45,11);
        cout << "-----------------------------------"<< endl;
        gotoxy(45,12);
        cout << "1 - VER CARTA               "<< endl;
        gotoxy(45,13);
        cout << "2 - AGREGAR PRODUCTO                "<< endl;
        gotoxy(45,14);
        cout << "3 - ELIMINAR PRODUCTO          "<< endl;
        gotoxy(45,15);
        cout << "4 - MODIFICAR PRODUCTO          "<< endl;
        gotoxy(45,16);
        cout << "5 - PRODUCTOS X RANGO DE PRECIO" << endl;
        gotoxy(45,17);
        cout << "-----------------------------------"<< endl;
        gotoxy(45,18);
        cout << "0 - VOLVER AL MENÚ ANTERIOR"<< endl;
        gotoxy(45,22);
        cout  << "> ";
        gotoxy(46,22);
        cin>> opcion;
        cin.ignore();

        switch(opcion){

            case 1:
                cls();
                listarRegistros();
            break;

            case 2:
                cls();
                agregarRegistro();
            break;

            case 3:
                cls();
                if (eliminarRegistro() == true){
                        gotoxy(40, 15);
                        cout << "           PRODUCTO ELIMINADO." << endl;
                }
            break;

            case 4:
                cls();
                menuModificar();
            break;

            case 5:
                cls();
                buscarProductosxRangoPrecio();
            break;

            case 0:
                return menuPrincipal();
            break;

            default:
                cls();
                gotoxy(40,15);
                cout << "Ingresó una opción errónea.";
                gotoxy(40,16);
                system("pause");
                return menuCarta();
        break;
        }
        anykey();
        cin.ignore();

    }while(opcion != 0);


}

void menuModificar(){
 int opcion;
 int id, x;
 Producto reg;
 float precio;
 char desc [30];
 int stock;
    do{
        cls();
        gotoxy(45,8);
        cout << "-       beer&code CERVECERÍA       -"<< endl;
        gotoxy(45,9);
        cout << "-----------------------------------"<< endl;
        gotoxy(45,10);
        cout << "MENÚ DE MODIFICACIONES"<< endl;
        gotoxy(45,11);
        cout << "-----------------------------------"<< endl;
        gotoxy(45,12);
        cout << "1 - MODIFICAR PRECIO               "<< endl;
        gotoxy(45,13);
        cout << "2 - MODIFICAR DESCRIPCION                "<< endl;
        gotoxy(45,14);
        cout << "3 - MODIFICAR STOCK          "<< endl;
        gotoxy(45,15);
        cout << "-----------------------------------"<< endl;
        gotoxy(45,16);
        cout << "0 - VOLVER AL MENÚ ANTERIOR"<< endl;
        gotoxy(45,20);
        cout  << "> ";
        gotoxy(46,20);
        cin>> opcion;
        cin.ignore();

        switch(opcion){

            case 1:
                cls();
                gotoxy(40,8);
                cout << "             MODIFICAR PRECIO " << endl;
                gotoxy(40,9);
                cout << "-------------------------------------------" << endl;
                gotoxy(40,10);
                cout << "INGRESE ID DEL PRODUCTO: ";
                cin >> id;

                x=buscarProducto(id);
                while(x==-1){
                    gotoxy(40,12);
                    cout<< "NO EXISTE PRODUCTO CON ID INDICADO." << endl;
                    gotoxy(40,13);
                    cout << "REINGRESE ID DEL PRODUCTO: ";
                    cin >> id;
                    gotoxy(67,13);
                    cout << "   ";

                x=buscarProducto(id);
                }
                reg.leerDeDisco(x);
                cls();
                gotoxy(40,8);
                cout << "                  PRODUCTO" << endl;
                gotoxy(40,9);
                cout << "-------------------------------------------" << endl;
                gotoxy(40,10);
                cout << reg.getDesc() << endl;
                gotoxy(40,11);
                cout << "PRECIO: $";
                cout << reg.getPrecio() << endl;
                gotoxy(40,12);
                cout << "INGRESE NUEVO PRECIO: $";
                cin >> precio;
                reg.setPrecio(precio);
                if(reg.modificarEnDisco(x)==true){
                    gotoxy(40,14);
                    cout << "           PRODUCTO MODIFICADO"; }

            break;

            case 2:
                 cls();
                gotoxy(40,8);
                cout << "          MODIFICAR DESCRIPCION " << endl;
                gotoxy(40,9);
                cout << "-------------------------------------------" << endl;
                gotoxy(40,10);
                cout << "INGRESE ID DEL PRODUCTO: ";
                cin >> id;

                x=buscarProducto(id);
                while(x==-1){
                    gotoxy(40,12);
                    cout<< "NO EXISTE PRODUCTO CON ID INDICADO." << endl;
                    gotoxy(40,13);
                    cout << "REINGRESE ID DEL PRODUCTO: ";
                    cin >> id;
                    gotoxy(67,13);
                    cout << "   ";

                x=buscarProducto(id);
                }
                reg.leerDeDisco(x);
                cls();
                cin.ignore();
                gotoxy(40,8);
                cout << "                  PRODUCTO" << endl;
                gotoxy(40,9);
                cout << "-------------------------------------------" << endl;
                gotoxy(40,10);
                cout << reg.getDesc() << endl;
                gotoxy(40,11);
                cout << "INGRESE NUEVA DESCRIPCION: ";
                cin.getline(desc,30);
                reg.setDesc(desc);
                if(reg.modificarEnDisco(x)==true){
                    gotoxy(40,14);
                    cout << "           PRODUCTO MODIFICADO"; }

            break;

            case 3:
                cls();
                gotoxy(40,8);
                cout << "          MODIFICAR STOCK " << endl;
                gotoxy(40,9);
                cout << "-------------------------------------------" << endl;
                gotoxy(40,10);
                cout << "INGRESE ID DEL PRODUCTO: ";
                cin >> id;

                x=buscarProducto(id);
                while(x==-1){
                    gotoxy(40,12);
                    cout<< "NO EXISTE PRODUCTO CON ID INDICADO." << endl;
                    gotoxy(40,13);
                    cout << "REINGRESE ID DEL PRODUCTO: ";
                    cin >> id;
                    gotoxy(67,13);
                    cout << "   ";
                    x=buscarProducto(id);
                    }
                reg.leerDeDisco(x);
                cls();
                cin.ignore();
                gotoxy(40,8);
                cout << "                  PRODUCTO" << endl;
                gotoxy(40,9);
                cout << "-------------------------------------------" << endl;
                gotoxy(40,10);
                cout << reg.getDesc() << endl;
                gotoxy(40,11);
                cout << "STOCK ACTUAL: ";
                cout << reg.getStock() << endl;
                gotoxy(40,12);
                cout << "INGRESE NUEVO STOCK: ";
                cin >> stock;

                reg.setStock(stock);
                reg.setEstado(1);

                if(reg.modificarEnDisco(x)==true){
                    gotoxy(40,14);
                    cout << "           PRODUCTO MODIFICADO"; }

            break;

            case 0:
                return menuCarta();
            break;

            default:
                cls();
                gotoxy(40,15);
                cout << "Ingresó una opción errónea.";
                gotoxy(40,16);
                system("pause");
                return menuModificar();
        break;
        }
        anykey();
        cin.ignore();

    }while(opcion != 0);

}


void menuVenta(){

    int opcion;
    do{
        cls();
        gotoxy(45,8);
        cout << "-       beer&code CERVECERÍA       -"<< endl;
        gotoxy(45,9);
        cout << "-----------------------------------"<< endl;
        gotoxy(45,10);
        cout << "MENÚ VENTAS"<< endl;
        gotoxy(45,11);
        cout << "-----------------------------------"<< endl;
        gotoxy(45,12);
        cout << "1 - INGRESAR VENTA               "<< endl;
        gotoxy(45,13);
        cout << "2 - DEVOLUCION VENTA               "<< endl;
        gotoxy(45,14);
        cout << "3 - VENTAS X CLIENTE" << endl;
        gotoxy(45,15);
        cout << "-----------------------------------"<< endl;
        gotoxy(45,16);
        cout << "0 - VOLVER AL MENÚ ANTERIOR"<< endl;
        gotoxy(45,20);
        cout  << "> ";
        gotoxy(46,20);
        cin>> opcion;
        cin.ignore();

        switch(opcion){

            case 1:
                cls();
                nuevaVenta();
            break;

            case 2:
                cls();
                if(devolucionVenta()==true){
                    gotoxy(54,25);
                    cout << "VENTA ELIMINADA..." << endl;
                }
                else{
                    gotoxy(45,15);
                    cout << "VENTA NO ENCONTRADA O YA ELIMINADA" << endl;
                    anykey();
                    return menuVenta();
                }
            break;

            case 3:
                cls();
                ventasPorCliente();
            break;

            case 0:
                return menuPrincipal();
            break;

            default:
                cls();
                gotoxy(40,15);
                cout << "Ingresó una opción errónea.";
                gotoxy(40,16);
                system("pause");
                return menuPrincipal();
        break;
        }
        anykey();
        cin.ignore();

    }while(opcion != 0);


}

void menuClientes(){

    int opcion;
    do{
        cls();
        gotoxy(45,8);
        cout << "-       beer&code CERVECERÍA       -"<< endl;
        gotoxy(45,9);
        cout << "-----------------------------------"<< endl;
        gotoxy(45,10);
        cout << "MENÚ CLIENTES"<< endl;
        gotoxy(45,11);
        cout << "-----------------------------------"<< endl;
        gotoxy(45,12);
        cout << "1 - INGRESAR CLIENTE               "<< endl;
        gotoxy(45,13);
        cout << "2 - ELIMINAR CLIENTE             "<< endl;
        gotoxy(45,14);
        cout << "3 - MODIFICAR CLIENTE          "<< endl;
        gotoxy(45,15);
        cout << "4 - LISTAR CLIENTES" << endl;
        gotoxy(45,16);
        cout << "5 - BUSCAR CLIENTE POR DNI" << endl;
        gotoxy(45,17);
        cout << "-----------------------------------"<< endl;
        gotoxy(45,18);
        cout << "0 - VOLVER AL MENÚ ANTERIOR"<< endl;
        gotoxy(45,22);
        cout  << "> ";
        gotoxy(46,22);
        cin>> opcion;
        cin.ignore();

        switch(opcion){

            case 1:
                cls();
                if(agregarCliente()==true){
                    gotoxy(50,24);
                    cout << "CLIENTE AGREGADO CON ÉXITO.";
                }
                else{
                    gotoxy(50,24);
                    cout << "CLIENTE NO SE PUDO AGREGAR.";
                    anykey();
                    return menuClientes();
                };
            break;

            case 2:
                cls();
                if(eliminarCliente()==true){
                    gotoxy(50,24);
                    cout << "CLIENTE ELIMINADO CON ÉXITO.";
                }
                else{
                    gotoxy(50,24);
                    cout << "CLIENTE NO SE PUDO ELIMINAR.";
                    anykey();
                    return menuClientes();
                };

            break;

            case 3:
                cls();
                menuModificarClientes();
            break;

            case 4:
                cls();
                listarClientes();
            break;

            case 5:
                cls();
                buscarClientexDNI();
            break;
            case 0:
                return menuPrincipal();
            break;

            default:
                cls();
                gotoxy(40,15);
                cout << "Ingresó una opción errónea.";
                gotoxy(40,16);
                system("pause");
                return menuPrincipal();
        break;
        }
        anykey();
        cin.ignore();

    }while(opcion != 0);


}


void menuInformes(){
int opcion;
    do{
        cls();
        gotoxy(45,8);
        cout << "-       beer&code CERVECERÍA       -"<< endl;
        gotoxy(45,9);
        cout << "-----------------------------------"<< endl;
        gotoxy(45,10);
        cout << "MENÚ INFORMES"<< endl;
        gotoxy(45,11);
        cout << "-----------------------------------"<< endl;
        gotoxy(45,12);
        cout << "1 - CAJA DIARIA         "<< endl;
        gotoxy(45,13);
        cout << "2 - RECAUDACIÓN X DÍA               "<< endl;
        gotoxy(45,14);
        cout << "3 - RANKING PRODUCTOS MÁS VENDIDOS       "<< endl;
        gotoxy(45,15);
        cout << "4 - PRODUCTOS NO VENDIDOS X FECHA" << endl;
        gotoxy(45,16);
        cout << "-----------------------------------"<< endl;
        gotoxy(45,17);
        cout << "0 - VOLVER AL MENÚ ANTERIOR"<< endl;
        gotoxy(45,21);
        cout  << "> ";
        gotoxy(46,21);
        cin>> opcion;
        cin.ignore();

        switch(opcion){

            case 1:
                cls();
                cajaDiaria();
            break;

            case 2:
                cls();
                ventasPorDia();
            break;

            case 3:
                cls();
                rankingProductosMasVendidos();
            break;

            case 4:
                cls();
                productosNoVendidos();
            break;
            /*
            case 5:
                cls();
                recaudacionXProductoEnFecha();
            break;
            */
            case 0:
                return menuPrincipal();
            break;

            default:
                cls();
                gotoxy(40,15);
                cout << "Ingresó una opción errónea.";
                gotoxy(40,16);
                system("pause");
                return menuCarta();
        break;
        }
        anykey();
        cin.ignore();

    }while(opcion != 0);


}

void menuUsuarios(){

    int opcion;
    do{
        cls();
        gotoxy(45,8);
        cout << "-       beer&code CERVECERÍA       -"<< endl;
        gotoxy(45,9);
        cout << "-----------------------------------"<< endl;
        gotoxy(45,10);
        cout << "MENÚ USUARIOS"<< endl;
        gotoxy(45,11);
        cout << "-----------------------------------"<< endl;
        gotoxy(45,12);
        cout << "1 - AGREGAR USUARIO               "<< endl;
        gotoxy(45,13);
        cout << "2 - LISTAR USUARIOS                "<< endl;
        gotoxy(45,14);
        cout << "-----------------------------------"<< endl;
        gotoxy(45,15);
        cout << "0 - VOLVER AL MENÚ ANTERIOR"<< endl;
        gotoxy(45,19);
        cout  << "> ";
        gotoxy(46,19);
        cin>> opcion;
        cin.ignore();

        switch(opcion){

            case 1:
                cls();
                if(agregarUsuario()==true){
                    gotoxy(50,24);
                    cout << "USUARIO GENERADO CON ÉXITO.";
                }
                else{
                    gotoxy(50,24);
                    cout << "USUARIO NO SE PUDO CREAR.";
                }
            break;

            case 2:
                cls();
                listarUsuarios();
            break;

            case 0:
                return menuPrincipal();
            break;

            default:
                cls();
                gotoxy(40,15);
                cout << "Ingresó una opción errónea.";
                gotoxy(40,16);
                system("pause");
                return menuUsuarios();
        break;
        }
        anykey();
        cin.ignore();

    }while(opcion != 0);

}

void menuCompras(){

    int opcion;
    do{
        cls();
        gotoxy(45,8);
        cout << "-       beer&code CERVECERÍA       -"<< endl;
        gotoxy(45,9);
        cout << "-----------------------------------"<< endl;
        gotoxy(45,10);
        cout << "MENÚ COMPRAS"<< endl;
        gotoxy(45,11);
        cout << "-----------------------------------"<< endl;
        gotoxy(45,12);
        cout << "1 - INGRESAR COMPRA               "<< endl;
        gotoxy(45,13);
        cout << "2 - DEVOLUCION COMPRA               "<< endl;
        gotoxy(45,14);
        cout << "3 - LISTAR COMPRAS POR FECHA        "<< endl;
        gotoxy(45,15);
        cout << "-----------------------------------"<< endl;
        gotoxy(45,16);
        cout << "0 - VOLVER AL MENÚ ANTERIOR"<< endl;
        gotoxy(45,20);
        cout  << "> ";
        gotoxy(46,20);
        cin>> opcion;
        cin.ignore();

        switch(opcion){

            case 1:
                cls();
                nuevaCompra();
            break;

            case 2:
                cls();
                if(devolucionCompra()==true){
                    gotoxy(54,25);
                    cout << "COMPRA ELIMINADA..." << endl;
                }
                else{
                    gotoxy(45,15);
                    cout << "COMPRA NO ENCONTRADA O YA ELIMINADA" << endl;
                    anykey();
                    return menuCompras();
                }
            break;

            case 3:
                cls();
                gastosPorFecha();
            break;

            case 0:
                return menuPrincipal();
            break;

            default:
                cls();
                gotoxy(40,15);
                cout << "Ingresó una opción errónea.";
                gotoxy(40,16);
                system("pause");
                return menuPrincipal();
        break;
        }
        anykey();
        cin.ignore();

    }while(opcion != 0);


}

void menuEmpleados(){

    int opcion;
    do{
        cls();
        gotoxy(45,8);
        cout << "-       beer&code CERVECERÍA       -"<< endl;
        gotoxy(45,9);
        cout << "-----------------------------------"<< endl;
        gotoxy(45,10);
        cout << "MENÚ EMPLEADOS"<< endl;
        gotoxy(45,11);
        cout << "-----------------------------------"<< endl;
        gotoxy(45,12);
        cout << "1 - INGRESAR EMPLEADO               "<< endl;
        gotoxy(45,13);
        cout << "2 - ELIMINAR EMPLEADO             "<< endl;
        gotoxy(45,14);
        cout << "3 - MODIFICAR EMPLEADO          "<< endl;
        gotoxy(45,15);
        cout << "4 - LISTAR EMPLEADOS" << endl;
        gotoxy(45,16);
        cout << "-----------------------------------"<< endl;
        gotoxy(45,17);
        cout << "0 - VOLVER AL MENÚ ANTERIOR"<< endl;
        gotoxy(45,21);
        cout  << "> ";
        gotoxy(46,21);
        cin>> opcion;
        cin.ignore();

        switch(opcion){

            case 1:
                cls();
                if(agregarEmpleado()==true){
                    gotoxy(50,24);
                    cout << "EMPLEADO AGREGADO CON ÉXITO.";
                }
                else{
                    gotoxy(50,24);
                    cout << "EMPLEADO NO SE PUDO AGREGAR.";
                    anykey();
                    return menuEmpleados();
                };
            break;

            case 2:
                cls();
                if(eliminarEmpleado()==true){
                    gotoxy(50,24);
                    cout << "EMPLEADO ELIMINADO CON ÉXITO.";
                }
                else{
                    gotoxy(50,24);
                    cout << "EMPLEADO NO SE PUDO ELIMINAR.";
                    anykey();
                    return menuEmpleados();
                };
            break;

            case 3:
                cls();
                menuModificarEmpleados();
            break;

            case 4:
                cls();
                listarEmpleados();
            break;
            case 0:
                return menuPrincipal();
            break;

            default:
                cls();
                gotoxy(40,15);
                cout << "Ingresó una opción errónea.";
                gotoxy(40,16);
                system("pause");
                return menuPrincipal();
        break;
        }
        anykey();
        cin.ignore();

    }while(opcion != 0);


}

void menuModificarClientes(){
 int opcion;
 int id, x;
 Cliente reg;
 char dni[9];
 char nombre[21];
 char apellido[21];
 char telefono[12];
 char direccion[21];
    do{
        cls();
        gotoxy(45,8);
        cout << "-       beer&code CERVECERÍA       -"<< endl;
        gotoxy(45,9);
        cout << "-----------------------------------"<< endl;
        gotoxy(45,10);
        cout << "MENÚ DE MODIFICACIONES CLIENTES"<< endl;
        gotoxy(45,11);
        cout << "-----------------------------------"<< endl;
        gotoxy(45,12);
        cout << "1 - MODIFICAR DNI               "<< endl;
        gotoxy(45,13);
        cout << "2 - MODIFICAR NOMBRE Y APELLIDO              "<< endl;
        gotoxy(45,14);
        cout << "3 - MODIFICAR TELÉFONO          "<< endl;
        gotoxy(45,15);
        cout << "4 - MODIFICAR DIRECCIÓN         "<< endl;
        gotoxy(45,16);
        cout << "-----------------------------------"<< endl;
        gotoxy(45,17);
        cout << "0 - VOLVER AL MENÚ ANTERIOR"<< endl;
        gotoxy(45,21);
        cout  << "> ";
        gotoxy(46,21);
        cin>> opcion;
        cin.ignore();

        switch(opcion){

            case 1:
                cls();
                gotoxy(40,8);
                cout << "             MODIFICAR DNI " << endl;
                gotoxy(40,9);
                cout << "-------------------------------------------" << endl;
                gotoxy(40,10);
                cout << "INGRESE ID DEL CLIENTE: ";
                cin >> id;

                x=buscarCliente(id);
                while(x==-1){
                    gotoxy(40,12);
                    cout<< "NO EXISTE CLIENTE CON ID INDICADO." << endl;
                    gotoxy(40,13);
                    cout << "REINGRESE ID DEL CLIENTE: ";
                    cin >> id;
                    gotoxy(67,13);
                    cout << "   ";

                x=buscarProducto(id);
                }
                reg.leerDeDisco(x);
                cls();
                gotoxy(40,8);
                cout << "                  CLIENTE" << endl;
                gotoxy(40,9);
                cout << "-------------------------------------------" << endl;
                gotoxy(40,10);
                cout << reg.getNombre() << " " << reg.getApellido();
                gotoxy(40,11);
                cout << "DNI: ";
                cout << reg.getDNI() << endl;
                gotoxy(40,12);
                cout << "INGRESE NUEVO DNI: ";
                cin >> dni;
                reg.setDNI(dni);
                if(reg.modificarEnDisco(x)==true){
                    gotoxy(40,14);
                    cout << "           CLIENTE MODIFICADO"; }

            break;

            case 2:
                 cls();
                gotoxy(40,8);
                cout << "          MODIFICAR NOMBRE Y APELLIDO " << endl;
                gotoxy(40,9);
                cout << "-------------------------------------------" << endl;
                gotoxy(40,10);
                cout << "INGRESE ID DEL CLIENTE: ";
                cin >> id;

                x=buscarCliente(id);
                while(x==-1){
                    gotoxy(40,12);
                    cout<< "NO EXISTE CLIENTE CON ID INDICADO." << endl;
                    gotoxy(40,13);
                    cout << "REINGRESE ID DEL CLIENTE: ";
                    cin >> id;
                    gotoxy(67,13);
                    cout << "   ";

                x=buscarCliente(id);
                }
                reg.leerDeDisco(x);
                cls();
                gotoxy(40,8);
                cout << "                  CLIENTE" << endl;
                gotoxy(40,9);
                cout << "-------------------------------------------" << endl;
                gotoxy(40,10);
                cout << reg.getNombre() << " " << reg.getApellido();
                gotoxy(40,11);
                cin.ignore();
                cout << "INGRESE NUEVO NOMBRE: ";
                cin.getline(nombre,21);
                gotoxy(40,12);
                cout << "INGRESE NUEVO APELLIDO: ";
                cin.getline(apellido,21);
                reg.setNombre(nombre);
                reg.setApellido(apellido);
                if(reg.modificarEnDisco(x)==true){
                    gotoxy(40,14);
                    cout << "           CLIENTE MODIFICADO"; }

            break;

            case 3:
                cls();
                gotoxy(40,8);
                cout << "          MODIFICAR TELÉFONO " << endl;
                gotoxy(40,9);
                cout << "-------------------------------------------" << endl;
                gotoxy(40,10);
                cout << "INGRESE ID DEL CLIENTE: ";
                cin >> id;

                x=buscarCliente(id);
                while(x==-1){
                    gotoxy(40,12);
                    cout<< "NO EXISTE CLIENTE CON ID INDICADO." << endl;
                    gotoxy(40,13);
                    cout << "REINGRESE ID DEL CLIENTE: ";
                    cin >> id;
                    gotoxy(67,13);
                    cout << "   ";
                    x=buscarCliente(id);
                    }
                reg.leerDeDisco(x);
                cls();
                gotoxy(40,8);
                cout << "                  CLIENTE" << endl;
                gotoxy(40,9);
                cout << "-------------------------------------------" << endl;
                gotoxy(40,10);
                cout << reg.getNombre() << " " << reg.getApellido();
                gotoxy(40,11);
                cout << "TELEFONO: ";
                cout << reg.getTel() << endl;
                gotoxy(40,12);
                cout << "INGRESE NUEVO TELEFONO: ";
                cin >> telefono;
                reg.setTel(telefono);
                if(reg.modificarEnDisco(x)==true){
                    gotoxy(40,14);
                    cout << "           CLIENTE MODIFICADO"; }

            break;

            case 4:
                cls();
                gotoxy(40,8);
                cout << "          MODIFICAR DIRECCIÓN " << endl;
                gotoxy(40,9);
                cout << "-------------------------------------------" << endl;
                gotoxy(40,10);
                cout << "INGRESE ID DEL CLIENTE: ";
                cin >> id;

                x=buscarCliente(id);
                while(x==-1){
                    gotoxy(40,12);
                    cout<< "NO EXISTE CLIENTE CON ID INDICADO." << endl;
                    gotoxy(40,13);
                    cout << "REINGRESE ID DEL CLIENTE: ";
                    cin >> id;
                    gotoxy(67,13);
                    cout << "   ";
                    x=buscarCliente(id);
                    }

                reg.leerDeDisco(x);
                cls();
                gotoxy(40,8);
                cout << "                  CLIENTE" << endl;
                gotoxy(40,9);
                cout << "-------------------------------------------" << endl;
                gotoxy(40,10);
                cout << reg.getNombre() << " " << reg.getApellido();
                gotoxy(40,11);
                cout << "DIRECCIÓN: ";
                cout << reg.getDirec() << endl;
                gotoxy(40,12);
                cin.ignore();
                cout << "INGRESE NUEVA DIRECCION: ";
                cin.getline(direccion, 21),
                reg.setDirec(direccion);
                if(reg.modificarEnDisco(x)==true){
                    gotoxy(40,14);
                    cout << "           CLIENTE MODIFICADO"; }
            break;

            case 0:
                return menuClientes();
            break;

            default:
                cls();
                gotoxy(40,15);
                cout << "Ingresó una opción errónea.";
                gotoxy(40,16);
                system("pause");
                return menuModificar();
        break;
        }
        anykey();
        cin.ignore();

    }while(opcion != 0);

}



void menuModificarEmpleados(){
 int opcion;
 int id, x;
 Empleado reg;
 char dni[9];
 char nombre[21];
 char apellido[21];
 float sueldo;

    do{
        cls();
        gotoxy(45,8);
        cout << "-       beer&code CERVECERÍA       -"<< endl;
        gotoxy(45,9);
        cout << "-----------------------------------"<< endl;
        gotoxy(45,10);
        cout << "MENÚ DE MODIFICACIONES EMPLEADOS"<< endl;
        gotoxy(45,11);
        cout << "-----------------------------------"<< endl;
        gotoxy(45,12);
        cout << "1 - MODIFICAR DNI               "<< endl;
        gotoxy(45,13);
        cout << "2 - MODIFICAR NOMBRE Y APELLIDO              "<< endl;
        gotoxy(45,14);
        cout << "3 - MODIFICAR SUELDO          "<< endl;
        gotoxy(45,15);
        cout << "-----------------------------------"<< endl;
        gotoxy(45,16);
        cout << "0 - VOLVER AL MENÚ ANTERIOR"<< endl;
        gotoxy(45,20);
        cout  << "> ";
        gotoxy(46,20);
        cin>> opcion;
        cin.ignore();

        switch(opcion){

            case 1:
                cls();
                gotoxy(40,8);
                cout << "             MODIFICAR DNI " << endl;
                gotoxy(40,9);
                cout << "-------------------------------------------" << endl;
                gotoxy(40,10);
                cout << "INGRESE ID DEL EMPLEADO: ";
                cin >> id;

                x=buscarEmpleado(id);
                while(x==-1){
                    gotoxy(40,12);
                    cout<< "NO EXISTE EMPLEADO CON ID INDICADO." << endl;
                    gotoxy(40,13);
                    cout << "REINGRESE ID DEL EMPLEADO: ";
                    cin >> id;
                    gotoxy(67,13);
                    cout << "   ";

                x=buscarEmpleado(id);
                }
                reg.leerDeDisco(x);
                cls();
                gotoxy(40,8);
                cout << "                  EMPLEADO" << endl;
                gotoxy(40,9);
                cout << "-------------------------------------------" << endl;
                gotoxy(40,10);
                cout << reg.getNombre() << " " << reg.getApellido();
                gotoxy(40,11);
                cout << "DNI: ";
                cout << reg.getDNI() << endl;
                gotoxy(40,12);
                cout << "INGRESE NUEVO DNI: ";
                cin >> dni;
                reg.setDNI(dni);
                if(reg.modificarEnDisco(x)==true){
                    gotoxy(40,14);
                    cout << "           EMPLEADO MODIFICADO"; }

            break;

            case 2:
                 cls();
                gotoxy(40,8);
                cout << "          MODIFICAR NOMBRE Y APELLIDO " << endl;
                gotoxy(40,9);
                cout << "-------------------------------------------" << endl;
                gotoxy(40,10);
                cout << "INGRESE ID DEL EMPLEADO: ";
                cin >> id;

                x=buscarEmpleado(id);
                while(x==-1){
                    gotoxy(40,12);
                    cout<< "NO EXISTE EMPLEADO CON ID INDICADO." << endl;
                    gotoxy(40,13);
                    cout << "REINGRESE ID DEL EMPLEADO: ";
                    cin >> id;
                    gotoxy(67,13);
                    cout << "   ";

                x=buscarEmpleado(id);
                }
                reg.leerDeDisco(x);
                cls();
                gotoxy(40,8);
                cout << "                  EMPLEADO" << endl;
                gotoxy(40,9);
                cout << "-------------------------------------------" << endl;
                gotoxy(40,10);
                cout << reg.getNombre() << " " << reg.getApellido();
                gotoxy(40,11);
                cin.ignore();
                cout << "INGRESE NUEVO NOMBRE: ";
                cin.getline(nombre,21);
                gotoxy(40,12);
                cout << "INGRESE NUEVO APELLIDO: ";
                cin.getline(apellido,21);
                reg.setNombre(nombre);
                reg.setApellido(apellido);
                if(reg.modificarEnDisco(x)==true){
                    gotoxy(40,14);
                    cout << "           EMPLEADO MODIFICADO"; }

            break;

            case 3:
                cls();
                gotoxy(40,8);
                cout << "          MODIFICAR SUELDO " << endl;
                gotoxy(40,9);
                cout << "-------------------------------------------" << endl;
                gotoxy(40,10);
                cout << "INGRESE ID DEL EMPLEADO: ";
                cin >> id;

                x=buscarEmpleado(id);
                while(x==-1){
                    gotoxy(40,12);
                    cout<< "NO EXISTE EMPLEADO CON ID INDICADO." << endl;
                    gotoxy(40,13);
                    cout << "REINGRESE ID DEL EMPLEADO: ";
                    cin >> id;
                    gotoxy(67,13);
                    cout << "   ";
                    x=buscarEmpleado(id);
                    }
                reg.leerDeDisco(x);
                cls();
                gotoxy(40,8);
                cout << "                  EMPLEADO" << endl;
                gotoxy(40,9);
                cout << "-------------------------------------------" << endl;
                gotoxy(40,10);
                cout << reg.getNombre() << " " << reg.getApellido();
                gotoxy(40,11);
                cout << "SUELDO: $";
                cout << reg.getSueldo() << endl;
                gotoxy(40,12);
                cout << "INGRESE NUEVO SUELDO: $";
                cin >> sueldo;
                reg.setSueldo(sueldo);
                if(reg.modificarEnDisco(x)==true){
                    gotoxy(40,14);
                    cout << "           EMPLEADO MODIFICADO"; }

            break;

            case 0:
                return menuEmpleados();
            break;

            default:
                cls();
                gotoxy(40,15);
                cout << "Ingresó una opción errónea.";
                gotoxy(40,16);
                system("pause");
                return menuModificar();
        break;
        }
        anykey();
        cin.ignore();

    }while(opcion != 0);

}

void leerPass(char frase[]){

    int i=0;
    cout.flush();
    do
    {
        frase[i] = (unsigned char)getch();

        if(frase[i]!=8){
            cout << '*';
            i++;
        }
        else if(i>0){
            cout << (char)8 << (char)32 << (char)8;
            i--;
        }
        cout.flush();

    }while(frase[i-1]!=13);

    frase[i-1] = NULL;
    cout << endl;
}

void presentacion(){
gotoxy(17,1);
msleep(150);
cout << "888                                 .d8888b.                            888" << endl;
gotoxy(17,2);
msleep(150);
cout << "888                                d88P  '88b                           888" << endl;
gotoxy(17,3);
msleep(150);
cout << "888                                Y88b. d88P                           888" << endl;
gotoxy(17,4);
msleep(150);
cout << "88888b.   .d88b.   .d88b.  888d888  'Y8888P'      .d8888b  .d88b.   .d88888  .d88b." << endl;
gotoxy(17,5);
msleep(150);
cout << "888 '88b d8P  Y8b d8P  Y8b 888P'   .d88P88K.d88P d88P'    d88''88b d88' 888 d8P  Y8b" << endl;
gotoxy(17,6);
msleep(150);
cout << "888  888 88888888 88888888 888     888'  Y888P'  888      888  888 888  888 88888888" << endl;
gotoxy(17,7);
msleep(150);
cout << "888 d88P Y8b.     Y8b.     888     Y88b .d8888b  Y88b.    Y88..88P Y88b 888 Y8b." << endl;
gotoxy(17,8);
msleep(150);
cout << "88888P'   'Y8888   'Y8888  888      'Y8888P' Y88b 'Y8888P  'Y88P'   'Y88888  'Y8888" << endl;
gotoxy(17,9);
msleep(150);
cout << "---------------------------------------------------------------------------------------" << endl;
gotoxy(17,10);
msleep(150);
cout << "     _ _,---._                                                   .sssssssss." << endl;
gotoxy(17,11);
msleep(150);
cout << "   ,-','       `-.___                                      .sssssssssssssssssss" << endl;
gotoxy(17,12);
msleep(150);
cout << "  /-;'               `._                                 sssssssssssssssssssssssss" << endl;
gotoxy(17,13);
msleep(150);
cout << " /\\/          ._   _,'o \\                               ssssssssssssssssssssssssssss" << endl;
gotoxy(17,14);
msleep(150);
cout << "( /\\       _,--'\\,',''`. )                               @@sssssssssssssssssssssss@ss" << endl;
gotoxy(17,15);
msleep(150);
cout << " |\\      ,'o     \\'    //\\                               |s@@@@sssssssssssssss@@@@s|s" << endl;
gotoxy(17,16);
msleep(150);
cout << " |      \\        /   ,--'""`-.                             |sssss@@@@@sssss@@@@@sssss|s" << endl;
gotoxy(17,17);
msleep(150);
cout << " :       \\_    _/ ,-'         `-._              _________|sssssssss@sssss@sssssssss|s" << endl;
gotoxy(17,18);
msleep(150);
cout << "  \        `--'  /                )             /  _______|.ssssssss@sssss@ssssssss.|" << endl;
gotoxy(17,19);
msleep(150);
cout << "   `.  \\`._    ,'     ________,','            /  /       |...sssssss@sss@sssssss...|" << endl;
gotoxy(17,20);
msleep(150);
cout << "     .--`     ,'  ,--` __\\___,;'             /  /        |.......sss@sss@ssss......|" << endl;
gotoxy(17,21);
msleep(150);
cout << "      \\`.,-- ,' ,`_)--'  /`.,'              /  /         |..........s@ss@sss.......|" << endl;
gotoxy(17,22);
msleep(150);
cout << "       \\( ;  | | )      (`-/                \\  \\         |...........@ss@..........|" << endl;
gotoxy(17,23);
msleep(150);
cout << "         `--'| |)       |-/                  \\  \\        |...........@ss@..........|" << endl;
gotoxy(17,24);
msleep(150);
cout << "           | | |        | |                   \\  \\_______|...........@s@...........|" << endl;
gotoxy(17,25);
msleep(150);
cout << "           | | |,.,-.   | |_                   \\_________|............s............|" << endl;
gotoxy(17,26);
msleep(150);
cout << "           | `./ /   )---`  )                            |.........................|" << endl;
gotoxy(17,27);
msleep(150);
cout << "          _|  /    ,',   ,-'                            /...........................\\ " << endl;
gotoxy(17,28);
msleep(150);
cout << "         ,'|_(    /-<._,' |--,                         |.............................|" << endl;
gotoxy(17,29);
msleep(150);
cout << "         |    `--'---.     \\/ \\                     - Presione una tecla para continuar -" << endl;


}

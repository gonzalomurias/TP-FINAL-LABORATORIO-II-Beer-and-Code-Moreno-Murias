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
#include "Venta.h"
#include "Producto.h"
#include "DetalleVenta.h"
#include "Funciones.h"
#include "Cliente.h"
#include "Compras.h"

DetalleVenta::DetalleVenta()
{
    _estado = 1;
}

int DetalleVenta::getIDProducto()
{
    return _idProducto;
}

int DetalleVenta::getIDVenta()
{
    return _idVenta;
}
int DetalleVenta::getCantidad()
{
    return _cantidad;
}
float DetalleVenta::getPrecio()
{
    return _precioU;
}

bool DetalleVenta::getEstado()
{
    return _estado;
}

void DetalleVenta::setEstado(bool est)
{
    _estado = est;
}

void DetalleVenta::setIDProducto(int id)
{
    _idProducto=id;
}

void DetalleVenta::setIDVenta(int idv)
{
    _idVenta=idv;
}
void DetalleVenta::setCantidad(int cant)
{
    _cantidad=cant;

}
void DetalleVenta::setPrecio(float precio)
{
    _precioU=precio;
}
//void DetalleVenta::cargar();
void DetalleVenta::mostrar()
{
    if(_estado == 1)
    {
        cout << "ID VENTA";
        cout << _idVenta << endl;
        cout << "ID PRODUCTO";
        cout << _idProducto<< endl;
        cout << "CANTIDAD";
        cout << _cantidad<< endl;
        cout << "PRECIO UNITARIO";
        cout << _precioU<< endl;
    }
}
bool DetalleVenta::escribirDisco()
{
    FILE *p;
    p=fopen("DetalleVenta.dat", "ab");
    if(p==NULL)
    {
        return false;
    }
    bool escribio=fwrite(this, sizeof(DetalleVenta),1,p);
    fclose(p);
    return escribio;
}

bool DetalleVenta::leerDisco(int pos)
{
    FILE *p;
    p = fopen("DetalleVenta.dat", "rb");
    if (p == NULL)
    {
        return false;
    }
    bool ok;
    fseek(p, sizeof(DetalleVenta) * pos, 0);
    ok = fread(this, sizeof(DetalleVenta), 1, p);
    fclose(p);
    return ok;
}

bool DetalleVenta::modificarEnDisco(int pos)
{
    FILE *p;
    p=fopen("DetalleVenta.dat", "rb+");
    if(p==NULL) return false;
    fseek(p, pos*sizeof(DetalleVenta),0);
    bool escribio=fwrite(this, sizeof(DetalleVenta),1,p);
    fclose(p);
    return escribio;
}

void cancelarVentaActual(int id)
{

    int pos = 0, posAux = 0;
    DetalleVenta obj;
    Producto aux;

    while(obj.leerDisco(pos))
    {
        if(obj.getIDVenta() == id)
        {
            obj.setEstado(0);
            obj.modificarEnDisco(pos);
            while (aux.leerDeDisco(posAux))
            {
                if (obj.getIDProducto()== aux.getID())
                {
                    aux.setStock(aux.getStock()+obj.getCantidad());
                    aux.modificarEnDisco(posAux);
                }
                posAux++;
            }
        }
        pos++;
    }

}


void nuevaVenta()
{
    Venta obj;
    Producto reg;
    DetalleVenta aux;
    int opc;
    bool seguir=1;
    int idP;
    int cant;
    int numV;
    int pos;
    float total=0;
    int fp;
    float descuento = 0;
    int productos = 0;

    cls();
    listarRegistros2();

    for (int i=1; i<30; i++)
    {
        gotoxy(60,i);
        cout << "|";
    }

    gotoxy(65, 1);
    cout << "INGRESE 1 PARA MOSTRADOR O INGRESE 2 PARA DELIVERY > ";
    cin >> opc;

    switch(opc)
    {

    case 1:

        bool esClubPremium;

        obj.setIDC(1);
        gotoxy(65, 2);
        cout << "ES MIEMBRO DEL CLUB PREMIUM? 1- SI / 0- NO > ";
        cin >> esClubPremium;

        if(esClubPremium == 1)
        {
            int numCliente;
            int pos;
            gotoxy(65, 3);
            cout << "INGRESE NÚMERO DE CLIENTE > ";
            cin >> numCliente;
            pos = buscarCliente(numCliente);

            if (pos == -1)
            {
                gotoxy(63, 5);
                cout << "CLIENTE NO REGISTRADO. REINGRESE LOS DATOS DEL CLIENTE." << endl;
                gotoxy(63,6);
                anykey();
                return nuevaVenta();
            }

            Cliente cli;
            cli.leerDeDisco(pos);
            obj.setIDC(numCliente);
            if(cli.getClubPremium()==1)
            {
                descuento = 0.15;
            }
            else
            {
                bool eleccion;
                gotoxy(65, 4);
                cout << "CLIENTE NO PERTENECE AL CLUB PREMIUM.";
                gotoxy(65, 5);
                cout << "DESEA INSCRIBIRLO? 1- SI / 0- NO > ";
                cin >> eleccion;
                if (eleccion == 1)
                {
                    cli.setClubPremium(1);
                    cli.modificarEnDisco(pos);
                    descuento = 0.15;
                }
            }

        }

        numV=contarVentas()+1;
        obj.setID(numV);

        do
        {
            cls();
            listarRegistros2();

            for (int i=1; i<30; i++)
            {
                gotoxy(60,i);
                cout << "|";
            }

            gotoxy(65, 1);
            cout << "INGRESE ID PRODUCTO > ";
            cin >> idP;
            pos=buscarProducto(idP);
            while(pos==-1)
            {
                gotoxy(87,3);
                cout << "   ";
                gotoxy(65, 2);
                cout << "NO SE ENCONTRO EL PRODUCTO.";
                gotoxy(65, 3);
                cout << "REINGRESE ID PRODUCTO > ";
                cin >> idP;

                pos=buscarProducto(idP);
            }

            reg.leerDeDisco(pos);
            aux.setPrecio(reg.getPrecio());
            aux.setIDProducto(idP);
            aux.setIDVenta(numV);
            gotoxy(65, 5);
            cout << "INGRESE CANTIDAD > ";
            cin >> cant;

            while(cant<1)
            {
                gotoxy(65,5);
                cout << "                                                       ";
                gotoxy(65,6);
                cout << "CANTIDAD ERRÓNEA. REINGRESE LA CANTIDAD.";
                gotoxy(65,5);
                cout << "INGRESE CANTIDAD > ";
                cin >> cant;
                gotoxy(65,6);
                cout << "                                                       ";
            }

            if (reg.getStock() > cant)
            {

                aux.setCantidad(cant);
                total+=reg.getPrecio()*cant;
                aux.escribirDisco();
                reg.setStock(reg.getStock() - cant);
                reg.modificarEnDisco(pos);
                productos += 1;
            }

            else
            {
                int opc1;
                if (productos >= 1)
                {
                    gotoxy(65, 7);
                    cout << "NO HAY STOCK DEL PRODUCTO. ";

                }
                else
                {
                    gotoxy(65, 7);
                    cout << "NO HAY STOCK DEL PRODUCTO.";
                    gotoxy(65, 8);
                    cout << "INGRESE 1 PARA CONTINUAR / 0 PARA CANCELAR > ";
                    cin >> opc1;

                    switch(opc1)
                    {
                    case 1:
                        return nuevaVenta();
                        break;

                    case 0:
                        return menuVenta();
                        break;

                    default:
                        return menuVenta();
                        break;

                    }
                }
            }
            gotoxy(65, 10);
            cout << "INGRESE 1 - AÑADIR MÁS PRODUCTOS / 0 - FINALIZAR > ";
            cin >> seguir;

        }
        while(seguir);

        cls();
        listarRegistros2();

        for (int i=1; i<30; i++)
        {
            gotoxy(60,i);
            cout << "|";
        }

        if (descuento > 0 )
        {

            gotoxy(65, 1);
            cout << "SUBTOTAL: $" << total;
            total = total - (total * descuento);
            gotoxy(65, 2);
            cout << "DESCUENTO POR CLUB PREMIUM: " << descuento * 100 << "%";
        }
        gotoxy(65, 4);
        cout << "TOTAL: $" << total;
        gotoxy(65, 6);
        cout << "INGRESE FORMA DE PAGO: ";
        gotoxy(65, 7);
        cout << "1 -- EFECTIVO ";
        gotoxy(65, 8);
        cout << "2 -- MERCADO PAGO -- 5% DE RECARGO";
        gotoxy(65, 9);
        cout << "3 -- TARJETA DE CRÉDITO -- 5% DE RECARGO";
        gotoxy(65, 10);
        cout << "4 -- TARJETA DE DÉBITO";
        gotoxy(65, 11);
        cout << "> ";
        cin >> fp;

        while(fp!=1 && fp != 2 && fp != 3 && fp != 4)
        {
            gotoxy(65,5);
            cout << "FORMA DE PAGO INCORRECTA"<< endl;
            gotoxy(65, 6);
            cout << "INGRESE FORMA DE PAGO: ";
            gotoxy(65, 7);
            cout << "1 -- EFECTIVO ";
            gotoxy(65, 8);
            cout << "2 -- MERCADO PAGO -- 5% DE RECARGO";
            gotoxy(65, 9);
            cout << "3 -- TARJETA DE CRÉDITO -- 5% DE RECARGO";
            gotoxy(65, 10);
            cout << "4 -- TARJETA DE DÉBITO";
            gotoxy(65, 11);
            cout << "> ";
            cin >> fp;
        }
        obj.setFormaP(fp);

        if(fp==2 || fp==3)
        {
            total= total * 1.05;
            gotoxy(65,13);
            cout << "TOTAL: $" << total;
        }

        if(fp==1)
        {
            float billete;
            int opcionfp=2;
            gotoxy(65,15);
            cout << "INGRESE DINERO RECIBIDO: $";
            cin >> billete;
            while (billete < total && opcionfp==2)
            {
                gotoxy(65,22);
                cout << "                                ";
                gotoxy(65,16);
                cout << "DINERO INGRESADO NO ALCANZA.";
                gotoxy(65,17);
                cout << "1- CAMBIAR FORMA DE PAGO. ";
                gotoxy(65,18);
                cout << "2- REINGRESAR EFECTIVO";
                gotoxy(65,19);
                cout << "3- CANCELAR VENTA";
                gotoxy(65,20);
                cout << "            ";
                gotoxy(65,20);
                cout << "> ";
                cin >> opcionfp;
                if (opcionfp == 1)
                {
                    gotoxy(65,22);
                    cout << "INGRESE NUEVA FORMA DE PAGO";
                    gotoxy(65,23);
                    cout << "2 -- MERCADO PAGO -- 5 % DE RECARGO";
                    gotoxy(65,24);
                    cout << "3 -- TARJETA DE CRÉDITO -- 5% DE RECARGO" << endl;
                    gotoxy(65,25);
                    cout << "4 -- TARJETA DE DEBITO" << endl;
                    gotoxy(65,26);
                    cout << "> ";
                    cin >> fp;
                    while(fp != 2 && fp != 3 && fp != 4)
                    {
                        gotoxy(65,21);
                        cout << "FORMA DE PAGO INCORRECTA"<< endl;

                        gotoxy(65,22);
                        cout << "INGRESE NUEVA FORMA DE PAGO";
                        gotoxy(65,23);
                        cout << "2 -- MERCADO PAGO -- 5 % DE RECARGO";
                        gotoxy(65,24);
                        cout << "3 -- TARJETA DE CRÉDITO -- 5% DE RECARGO" << endl;
                        gotoxy(65,25);
                        cout << "4 -- TARJETA DE DEBITO" << endl;
                        gotoxy(65,26);
                        cout << "> ";
                        cin >> fp;
                    }
                    if(fp==2 || fp==3)
                    {
                        total = total * 1.05;
                        obj.setFormaP(fp);
                    }
                    else
                    {
                        obj.setFormaP(fp);
                    }
                    gotoxy(65, 27);
                    cout << "TOTAL: $" << total;
                }

                if (opcionfp == 2)
                {
                    gotoxy(65,22);
                    cout << "                                ";
                    gotoxy(65,22);
                    cout << "REINGRESE DINERO RECIBIDO: $";
                    cin >> billete;
                }

                if (opcionfp == 3)
                {
                    cancelarVentaActual(numV);
                    return menuVenta();
                }
            }
            if(opcionfp==2)
            {
                gotoxy(65,27);
                cout << "VUELTO: $" << billete - total;
            }
        }
        gotoxy(65,28);
        cout << "VENTA FINALIZADA ... " << endl;

        obj.setDelivery(0);
        obj.setTotal(total);
        obj.escribirDisco();

        break;

    case 2:
    {

        gotoxy(65,2);
        descuento = 0;

        char telefono[12];
        gotoxy(65,2);
        cout << "INGRESE TEL DEL CLIENTE > ";
        cin >> telefono;
        pos = buscarClientePorTel(telefono);

        if(pos == -1)
        {
            gotoxy(65,3);
            cout << "CLIENTE NO EXISTE, AGREGAR DATOS.";
            cin.ignore();
            anykey();
            cls();
            agregarCliente();
        }

        pos = buscarClientePorTel(telefono);

        Cliente cli;
        cli.leerDeDisco(pos);

        if(cli.getClubPremium()==1)
        {
            descuento = 0.15;
        }

        else
        {
            bool eleccion;
            gotoxy(65, 4);
            cout << "CLIENTE NO PERTENECE AL CLUB PREMIUM.";
            gotoxy(65, 5);
            cout << "DESEA INSCRIBIRLO? 1- SI / 0- NO > ";
            cin >> eleccion;
            if (eleccion == 1)
            {
                cli.setClubPremium(1);
                cli.modificarEnDisco(pos);
                descuento = 0.15;
            }
        }


        obj.setIDC(cli.getIDP());
        numV=contarVentas()+1;
        obj.setID(numV);

        do
        {
            cls();
            listarRegistros2();

            for (int i=1; i<30; i++)
            {
                gotoxy(60,i);
                cout << "|";
            }

            gotoxy(65, 1);
            cout << "INGRESE ID PRODUCTO > ";
            cin >> idP;
            pos=buscarProducto(idP);
            while(pos==-1)
            {
                gotoxy(87,3);
                cout << "   ";
                gotoxy(65, 2);
                cout << "NO SE ENCONTRO EL PRODUCTO.";
                gotoxy(65, 3);
                cout << "REINGRESE ID PRODUCTO > ";
                cin >> idP;
                pos=buscarProducto(idP);
            }

            reg.leerDeDisco(pos);
            aux.setPrecio(reg.getPrecio());
            aux.setIDProducto(idP);
            aux.setIDVenta(numV);
            gotoxy(65, 5);
            cout << "INGRESE CANTIDAD > ";
            cin >> cant;

            while(cant<1)
            {
                gotoxy(65,5);
                cout << "                                                       ";
                gotoxy(65,6);
                cout << "CANTIDAD ERRÓNEA. REINGRESE LA CANTIDAD.";
                gotoxy(65,5);
                cout << "INGRESE CANTIDAD > ";
                cin >> cant;
                gotoxy(65,6);
                cout << "                                                       ";
            }

            if (reg.getStock() > cant)
            {
                aux.setCantidad(cant);
                total+=reg.getPrecio()*cant;
                aux.escribirDisco();
                reg.setStock(reg.getStock() - cant);
                reg.modificarEnDisco(pos);
            }
            else
            {
                int opc1;
                gotoxy(65, 7);
                cout << "NO HAY STOCK DEL PRODUCTO.";
                gotoxy(65, 8);
                cout << "INGRESE 1 PARA CONTINUAR / 0 PARA CANCELAR > ";
                cin >> opc1;

                switch(opc1)
                {
                case 1:
                    return nuevaVenta();
                    break;

                case 0:
                    return menuVenta();
                    break;

                default:
                    return menuVenta();
                    break;
                }
            }


            gotoxy(65, 10);
            cout << "INGRESE 1 - AÑADIR MÁS PRODUCTOS / 0 - FINALIZAR > ";
            cin >> seguir;
        }
        while(seguir);

        cls();
        listarRegistros2();

        if (descuento > 0 )
        {
            cls();
            listarRegistros2();

            for (int i=1; i<30; i++)
            {
                gotoxy(60,i);
                cout << "|";
            }

            gotoxy(65, 1);
            cout << "SUBTOTAL: $" << total;
            total = total - (total * descuento);
            gotoxy(65, 2);
            cout << "DESCUENTO POR CLUB PREMIUM: " << descuento * 100 << "%";
        }
        gotoxy(65, 3);
        cout << "COSTO ENVÍO: $50";
        total = total + 50;
        gotoxy(65, 4);
        cout << "TOTAL: $" << total;

        gotoxy(65, 6);
        cout << "INGRESE FORMA DE PAGO: ";
        gotoxy(65, 7);
        cout << "1 -- EFECTIVO ";
        gotoxy(65, 8);
        cout << "2 -- MERCADO PAGO -- 5% DE RECARGO";
        gotoxy(65,9);
        cout << "> ";
        cin >> fp;

        while(fp!=1 && fp != 2)
        {
            gotoxy(65,5);
            cout << "FORMA DE PAGO INCORRECTA"<< endl;
            gotoxy(65, 6);
            cout << "INGRESE FORMA DE PAGO: ";
            gotoxy(65, 7);
            cout << "1 -- EFECTIVO ";
            gotoxy(65, 8);
            cout << "2 -- MERCADO PAGO -- 5% DE RECARGO";
            gotoxy(65,9);
            cin >> fp;
        }

        obj.setFormaP(fp);

        if(fp==1)
        {
            float billete;
            bool opcionfp=0;
            gotoxy(65, 11);
            cout << "INGRESE DINERO RECIBIDO: $";
            cin >> billete;
            while (billete < total && opcionfp==0)
            {
                gotoxy(65,14);
                cout << "                                             ";
                gotoxy(65,12);
                cout << "DINERO INGRESADO NO ALCANZA.";
                gotoxy(110,13);
                cout << "    ";
                gotoxy(65,13);
                cout << "DESEA CAMBIAR LA FORMA DE PAGO? 1-SI / 0-NO > ";
                cin >> opcionfp;
                if (opcionfp == 1)
                {

                    total= total * 1.05;
                    gotoxy(65,18);
                    cout << "TOTAL: " << total << endl;
                    obj.setFormaP(2);
                }
                else
                {
                    gotoxy(65,14);
                    cout << "                                ";
                    gotoxy(65,14);
                    cout << "REINGRESE DINERO RECIBIDO. > $";
                    cin >> billete;
                }
            }

            if(opcionfp==0)
            {
                gotoxy(65,15);
                cout << "VUELTO: $" << billete - total;
            }

        }

        if(fp==2)
        {
            total= total * 1.05;
            gotoxy(65,18);
            cout << "TOTAL: $" << total;
        }

        obj.setDelivery(0);
        obj.setTotal(total);
        obj.escribirDisco();
        gotoxy(65,20);
        cout << "VENTA FINALIZADA ... ";
    }
    break;

    default:
        cls();
        gotoxy(40,15);
        cout << "Ingresó una opción errónea.";
        gotoxy(40,16);
        system("pause");
        return nuevaVenta();
        break;

    }



}

void listarDetalleVentas()
{
    DetalleVenta obj;
    int pos=0;

    while(obj.leerDisco(pos++)==1)
    {
        obj.mostrar();
    }
}

bool devolucionVenta()
{

    cls();
    int id;
    int opc;

    gotoxy(50,8);
    cout << "    ELIMINAR VENTA";
    gotoxy(50,9);
    cout << "-------------------------";
    gotoxy(50,10);
    cout << "INGRESE ID DE VENTA: ";
    gotoxy(50,11);
    cout << "> ";
    cin >> id;

    Venta reg;
    DetalleVenta obj;

    int pos=0;

    pos = 0;
    while(reg.leerDisco(pos))
    {
        if(reg.getID() == id)
        {
            if (reg.getEstado()!=0)
            {
                gotoxy(40,15);
                cout << left;
                cout << setw(5)  << "ID";
                cout << setw(17) << "FECHA DE VENTA";
                cout << setw(15) << "FORMA DE PAGO";
                cout << setw(7)  << "TOTAL";
                gotoxy(40,16);
                cout << "--------------------------------------------" << endl;
                gotoxy(40,17);
                cout << left;
                cout << setw(5)  << reg.getID();
                cout << setw(2) << reg.getFecha().getDia();
                cout << setw(1) << "/";
                cout << setw(2) << reg.getFecha().getMes();
                cout << setw(1) << "/";
                cout << setw(14) << reg.getFecha().getAnio();
                cout << setw(12) << reg.getFormaP();
                cout << setw(1)  << "$" << setw(7) << reg.getTotal() << endl;

                gotoxy(40,19);
                cout << "DESEA ELIMINAR LA VENTA? 1-SI / 0-NO > ";
                cin >> opc;

                if(opc != 1)
                {
                    menuVenta();
                }

                reg.setEstado(0);
                reg.modificarEnDisco(pos);
            }
        }
        pos++;
    }

    while(obj.leerDisco(pos))
    {
        if(obj.getIDVenta() == id)
        {
            if(obj.getEstado()!=0)
            {
                obj.setEstado(0);
                return obj.modificarEnDisco(pos);
            }
            else
            {
                return false;
            }
        }
        pos++;
    }
}

void ventasPorDia()
{
    Fecha primer, actual;
    Venta obj;

    gotoxy(35,10);
    cout << "Ingresar fecha de inicio en formato DD/MM/AAAA" << endl;
    primer.cargar();
    primer.validarFecha();

    while(primer.getAnio() > actual.getAnio())
    {
        cls();
        gotoxy(35,10);
        cout << "Fecha ingresada no puede ser posterior a hoy." << endl;;
        primer.cargar();
        primer.validarFecha();
    }

    while(primer.getAnio() == actual.getAnio() && primer.getMes() > actual.getMes())
    {
        cls();
        gotoxy(35,10);
        cout << "Fecha ingresada no puede ser posterior a hoy." << endl;;
        primer.cargar();
        primer.validarFecha();
    }

    while(primer.getAnio() == actual.getAnio() && primer.getMes() == actual.getMes() && primer.getDia() > actual.getDia())
    {
        cls();
        gotoxy(35,10);
        cout << "Fecha ingresada no puede ser posterior a hoy." << endl;;
        primer.cargar();
        primer.validarFecha();
    }

    while(primer.getDia()==0)
    {
        cls();
        gotoxy(35,10);
        cout << "Fecha inválida, ingrese nuevamente la fecha de inicio en formato DD/MM/AAAA:" << endl;
        primer.cargar();
        primer.validarFecha();

        while(primer.getAnio() > actual.getAnio())
        {
            cls();
            gotoxy(35,10);
            cout << "Fecha ingresada no puede ser posterior a hoy." << endl;;
            primer.cargar();
            primer.validarFecha();
        }

        while(primer.getAnio() == actual.getAnio() && primer.getMes() > actual.getMes())
        {
            cls();
            gotoxy(35,10);
            cout << "Fecha ingresada no puede ser posterior a hoy." << endl;;
            primer.cargar();
            primer.validarFecha();
        }

        while(primer.getAnio() == actual.getAnio() && primer.getMes() == actual.getMes() && primer.getDia() > actual.getDia())
        {
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
    cout << "VENTAS DEL DÍA " << primer.getDia() << "/" << primer.getMes() << "/" << primer.getAnio();
    gotoxy(50,4);
    cout << "-------------------------";

    int j = 9;

    gotoxy(25,7);
    cout << left;
    cout << setw(5)  << "ID";
    cout << setw(17) << "FECHA DE VENTA";
    cout << setw(15) << "FORMA DE PAGO";
    cout << setw(7)  << "TOTAL";
    gotoxy(25,8);
    cout << "------------------------------------------------------------------------------" << endl;

    while(obj.leerDisco(pos++)==true)
    {
        if(obj.getFecha()==primer)
        {
            gotoxy(25,j);
            cout << left;
            cout << setw(5)  << obj.getID();
            cout << setw(2) << obj.getFecha().getDia();
            cout << setw(1) << "/";
            cout << setw(2) << obj.getFecha().getMes();
            cout << setw(1) << "/";
            cout << setw(14) << obj.getFecha().getAnio();
            cout << setw(12) << obj.getFormaP();
            cout << setw(1)  << "$" << setw(7) << obj.getTotal() << endl;
            totalDelDia += obj.getTotal();
            j++;
        }
    }

    gotoxy(25,j);
    cout << "------------------------------------------------------------------------------" << endl;
    gotoxy(82,j+1);
    cout << "TOTAL VENDIDO: $" << totalDelDia;

}




void cajaDiaria()
{

    Fecha actual;
    Venta obj;
    Compras aux;

    int pos = 0;
    float totalDelDia = 0;
    float totalVentas = 0;
    float totalCompras = 0;
    char formaPago[13];

    cls();

    gotoxy(45,1);
    cout << "CAJA DIARIA " << actual.getDia() << "/" << actual.getMes() << "/" << actual.getAnio();;
    gotoxy(1,2);
    cout << "------------------------------------------------------------------------------------------------------------------------";

    for (int i=3; i<30; i++)
    {
        gotoxy(49,i);
        cout << "|";
    }

    gotoxy(18,3);
    cout << "VENTAS DEL DÍA ";

    int j = 7;

    gotoxy(1,5);
    cout << left;
    cout << setw(5)  << "ID";
    cout << setw(25) << "FORMA DE PAGO";
    cout << setw(7)  << "TOTAL";
    gotoxy(1,6);
    cout << "------------------------------------------------" << endl;

    while(obj.leerDisco(pos++)==true)
    {
        if(obj.getFecha()==actual)
        {
            if(obj.getFormaP() == 1)
            {
                strcpy(formaPago, "EFECTIVO");
            }
            if(obj.getFormaP() == 2)
            {
                strcpy(formaPago, "MERCADOPAGO");
            }
            if(obj.getFormaP() == 3)
            {
                strcpy(formaPago, "CRÉDITO");
            }
            if(obj.getFormaP() == 4)
            {
                strcpy(formaPago, "DÉBITO");
            }
            gotoxy(1,j);
            cout << left;
            cout << setw(5)  << obj.getID();
            cout << setw(25) << formaPago;
            cout << setw(1)  << "$" << setw(7) << obj.getTotal() << endl;
            totalVentas += obj.getTotal();
            j++;
        }
    }

    gotoxy(1,j);
    cout << "------------------------------------------------" << endl;
    gotoxy(1,j+1);
    cout << "TOTAL VENDIDO:                $" << totalVentas;

    pos = 0;

    gotoxy(70,3);
    cout << "GASTOS DEL DÍA ";

    j = 7;

    gotoxy(51,5);
    cout << left;
    cout << setw(5)  << "ID";
    cout << setw(50) << "DESCRIPCION";
    cout << setw(7)  << "TOTAL";
    gotoxy(51,6);
    cout << "----------------------------------------------------------------------" << endl;

    while(aux.leerDisco(pos++)==true)
    {
        if(aux.getFechaCompra()==actual)
        {
            gotoxy(51,j);
            cout << left;
            cout << setw(5)  << aux.getIDCompra();
            cout << setw(50) << aux.getMotivo();
            cout << setw(1)  << "$" << setw(7) << aux.getImporteCompra() << endl;
            totalCompras += aux.getImporteCompra();
            j++;
        }
    }

    totalDelDia = totalVentas - totalCompras;

    gotoxy(51,j);
    cout << "----------------------------------------------------------------------" << endl;
    gotoxy(51,j+1);
    cout << "TOTAL GASTADO:                                         $" << totalCompras;

    resetColor();
    setBackgroundColor(4);
    gotoxy(65,j+5);
    cout << "                                            " << endl;
    gotoxy(65,j+6);
    cout << "           TOTAL CAJA: $" << setw(10) << totalDelDia << "          " << endl;
    gotoxy(65,j+7);
    cout << "                                            " << endl;
    resetColor();
    setBackgroundColor(0);
}
////////// EJERCICIOS PRACTICADOS:
int sumarProductos(int id)
{
    int cantidad = 0;
    DetalleVenta aux;
    int pos = 0;
    while(aux.leerDisco(pos++))
    {
        if (id == aux.getIDVenta())
        {
            cantidad += aux.getCantidad();
        }
    }
    return cantidad;
}

void productosXClientes()
{
    int m, a;
    Venta * vec;
    int cant = contarVentas();
    int pos = 0;
    Cliente obj;

    cout << "INGRESE MES: ";
    cin >> m;
    cout << "INGRESE ANIO: ";
    cin >> a;


    vec = new Venta[cant];
    if (vec == NULL)
    {
        return;
    }

    leerVentas(vec, cant);

    while(obj.leerDeDisco(pos++))
    {
        int productos = 0;
        for(int i=0; i<cant; i++)
        {
            if(vec[i].getFecha().getMes() == m && vec[i].getFecha().getAnio() == a)
            {
                if (vec[i].getIDC() == obj.getIDP())
                {
                    productos += sumarProductos(vec[i].getID());
                }
            }
        }
        cout << "CLIENTE: " << obj.getNombre() << " " << obj.getApellido() << endl;
        cout << "CANTIDAD DE PRODUCTOS: " << productos << endl;
        anykey();
    }


    delete vec;
}

int sumarRecaudacion(int idVenta, int idProducto)
{
    int pos = 0;
    DetalleVenta obj;
    int recau = 0;

    while(obj.leerDisco(pos++))
    {
        if (obj.getIDVenta() == idVenta && obj.getIDProducto() == idProducto)
        {
            recau = obj.getCantidad() * obj.getPrecio();
        }
    }

    return recau;
}

void productosNoVendidos()
{
    int m, a;
    Venta * vec;
    Producto obj;
    int pos = 0;
    int cant = contarVentas();
    int recau = 0;

    cout << "INGRESE MES: ";
    cin >> m;
    cout << "INGRESE ANIO: ";
    cin >> a;

    vec = new Venta[cant];
    if (vec == NULL)
    {
        return;
    }

    cls();
    cout << "PRODUCTOS NO VENDIDOS EN " << m << "/" << a << endl;
    cout << "-----------------------------------" << endl;

    leerVentas(vec, cant);

    while(obj.leerDeDisco(pos++))
    {
        recau = 0;
        for(int i=0; i<cant; i++)
        {
            if (vec[i].getFecha().getMes() == m && vec[i].getFecha().getAnio() == a)
            {
                recau += sumarRecaudacion(vec[i].getID(), obj.getID());
            }

        }
        if(recau == 0 && obj.getEstado() != 0)
        {
            cout << "PRODUCTO: " << obj.getID() << " " << obj.getDesc() << endl;
            anykey();
        }
    }

    delete vec;
}

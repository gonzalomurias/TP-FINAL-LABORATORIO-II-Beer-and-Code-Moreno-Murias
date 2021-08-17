#ifndef VENTA_H
#define VENTA_H
#include <iostream>
using namespace std;
#include <clocale>
#include <cstring>
#include "Fecha.h"
#include "Persona.h"

class Venta{
private:
	int _idVenta; //automatica
	Fecha _fechaVenta; //fecha sistema
	int _idCliente;
	int _formaPago;
	bool _delivery;
	float _total;
	bool _estado;

public:
	Venta();
	int getID();
	Fecha getFecha();
	int getIDC();
	int getFormaP();
	bool getDelivery();
	float getTotal();
	bool getEstado();
	void setEstado(bool);
	void setID(int);
	void setFecha(Fecha);
	void setIDC(int);
	void setFormaP(int);
	void setDelivery(bool);
	void setTotal(float);
	void cargar();
	void mostrar();
	bool escribirDisco();
	bool leerDisco(int);
	bool modificarEnDisco(int);
};

int contarVentas();
void listarVentas();
void leerVentas(Venta *, int);
void ventasPorCliente();
#endif // VENTA_H

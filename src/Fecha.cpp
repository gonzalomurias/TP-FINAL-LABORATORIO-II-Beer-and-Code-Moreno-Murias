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

Fecha::Fecha(){
    time_t t;
    t = time(NULL);
    struct tm * f;
    f = localtime (&t);

    _anio = f->tm_year + 1900;
    _mes = f->tm_mon + 1;
    _dia = f->tm_mday;
}

int Fecha::getDia() { return _dia; }
void Fecha::setDia(int val) { _dia = val; }
int Fecha::getMes() { return _mes; }
void Fecha::setMes(int val) { _mes = val; }
int Fecha::getAnio() { return _anio; }
void Fecha::setAnio(int val) { _anio = val; }
void Fecha::mostrar(){
    cout << _dia << "/" << _mes << "/" << _anio;
}
void Fecha::cargar(){
    gotoxy(35,11);
    cout<<"DIA: ";
    cin>> _dia;
    gotoxy(35,12);
    cout<<"MES: ";
    cin>> _mes;
    gotoxy(35,13);
    cout<<"AÑO: ";
    cin>> _anio;
}

void Fecha::cargar2(){
    gotoxy(50,17);
    cout<<"DIA: ";
    cin>> _dia;
    gotoxy(50,18);
    cout<<"MES: ";
    cin>> _mes;
    gotoxy(50,19);
    cout<<"AÑO: ";
    cin>> _anio;
}
void Fecha::validarFecha(){

if (_anio > 0){

    if(_mes >= 1 && _mes <= 12){

        switch(_mes){
            case 1: case 3: case 5: case 7: case 8: case 10: case 12:
                if(_dia >= 1 && _dia <= 31){
                    _dia = _dia;
                }
                else{
                    _dia = 0;
                    _mes = 0;
                    _anio = 0;
                }
            break;

            case 4: case 6: case 9: case 11:
                if(_dia >= 1 && _dia <= 30){
                    _dia = _dia;
                }
                else{
                    _dia = 0;
                    _mes = 0;
                    _anio = 0;
                }
            break;

            case 2:
                if((_anio%4 == 0) && (_anio%100 != 0) || (_anio%400 == 0)){
                    if(_dia >= 1 && _dia <= 29){
                        _dia = _dia;
                    }
                    else{
                        _dia = 0;
                        _mes = 0;
                        _anio = 0;
                    }
                }
                else{
                    if(_dia >= 1 && _dia <= 28){
                        _dia = _dia;
                    }
                    else{
                        _dia = 0;
                        _mes = 0;
                        _anio = 0;
                    }
                }
            break;
        }
    }
    else{
        _dia = 0;
        _mes = 0;
        _anio = 0;
    }
}
else{
    _dia = 0;
    _mes = 0;
    _anio = 0;
}
}

bool Fecha::operator==(Fecha aux){
    if(_dia!=aux._dia)return false;
    if(_mes!=aux._mes)return false;
    if(_anio!=aux._anio)return false;
    return true;
}

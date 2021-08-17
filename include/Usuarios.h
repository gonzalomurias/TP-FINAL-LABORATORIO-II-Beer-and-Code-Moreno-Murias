#ifndef USUARIOS_H
#define USUARIOS_H
#include <iostream>
using namespace std;
#include <clocale>
#include <cstring>


class Usuarios{
    private:
        char _user[10];
        char _passw[10];
        int _idUser;
    public:
        Usuarios();
        char *getUser();
        char *getPass();
        int getIDUser();
        void setUser(char *);
        void setPass(char *);
        void setIDUser(int);
        void cargar();
        void mostrar();
        bool escribirDisco();
        bool leerDeDisco(int);
        bool modificarEnDisco(int);
};

int contarUsuarios();
bool agregarUsuario();
bool listarUsuarios();
bool buscarUsuario(char *, char*);


#endif // USUARIOS_H

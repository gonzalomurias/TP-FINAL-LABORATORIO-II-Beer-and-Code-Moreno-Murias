#ifndef RANKINGPRODUCTOS_H
#define RANKINGPRODUCTOS_H


class RankingProductos{
    private:
    int _idP;
    char _desc[30];
    int _cantidad;
    float _precio;

    public:
    char *getDesc();
    int getCantidad();
    float getPrecioU();
    void setIDP(int);
    void setDesc(char *);
    void setCantidad(int);
    void setPrecioU(float);
    bool grabarEnDisco();
    bool leerDeDisco(int);
    void mostrar();
};

int contarRegistros();

#endif // RANKINGPRODUCTOS_H

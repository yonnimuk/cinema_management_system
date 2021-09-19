#ifndef ENTRADA_H
#define ENTRADA_H

class Entrada
{
    private:
    float precio;

    public:
        bool setPrecio();
        float getPrecio(){return precio;}
        bool grabarPrecio(int);

};

#endif // ENTRADA_H

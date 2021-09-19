#ifndef PELICULA_H
#define PELICULA_H

#include "Hora.h"
#include "Fecha.h"

class Pelicula{
  private:
    int idPelicula;
    char tituloPelicula[50];
    Fecha fechaEstreno;
    Fecha fechaVencimiento; /// agrege esto yonni 11/7
    int genero;
    int tipo;
    int minutos; //implementarlo en la carga

  public:
    bool cargarPelicula();
    void mostrarPelicula();
    void determinarGenero(char *);
    bool leerDeDisco(int);
    bool grabarEnDisco();
    bool grabarEnDisco(int);
    bool modificarPelicula(int);




    //setters
    bool setTituloPelicula(const char *);
    bool setGeneroPelicula(int);
    bool setTipoPelicula(int);
    bool setMinutosPelicula(int);
    void setIDPelicula(int);
    void setFechaEstreno(Fecha fecha){fechaEstreno=fecha;} /// agrege esto. atte: yonni 11/7
    void setFechaVencimiento(Fecha fecha){fechaVencimiento=fecha;} /// agrege esto. atte: yonni 11/7
    //getters
    char *getTituloPelicula();
    Fecha getFechaEstreno();
    int getNumeroSucursal();
    Hora getHorarioPelicula();
    int getGeneroPelicula();
    int getTipoPelicula();
    int getMinutosPelicula();
    int getDiaEstreno();
    int getMesEstreno();
    int getAnioEstreno();
    int getIdPelicula(){return idPelicula;}
    Fecha getFechaVencimiento(){return fechaVencimiento;} /// agrege esto. atte: yonni 11/7

    void mostrarTodasLasPeliculas();

};



#endif // PELICULA_H

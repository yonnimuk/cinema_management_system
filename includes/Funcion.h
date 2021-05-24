#ifndef FUNCION_H
#define FUNCION_H
#include "Hora.h"
#include "Fecha.h"

// poner el parchazo para ver la hora que puse en mostrar funcion en consultarVentas y consultarCompras creo, que hacen listados ambas

/// en el menu de el sectorclientes.h . La opcion consultar horarios disponibles debera enlazarse con esta clase. ya q que en realidad seria "consultar funciones Disponibles."
/// y en la consulta de funciones se mostraran todas las funciones a futuro con sus horarios y si esta dado de alta o baja.(podriamos n cada consulta, llamar a la funcion de baja para que chequee las fechas y de de baja al momento.)
/// las peliculas en cartelera deberan tener funciones en las cuales aparecer pero no podran ocupar la misma sala. y si la ocupan no podran asistir la misma hora.
/// en el menu "cargar horarios disponibles". Se deberan cargar las funciones con sus horarios y peliculas y demas cosas.

class Funcion
{
    protected:

    private:
    int idFuncion;
    int idPelicula;
    int tipoDePelicula;
    Hora horaInicio;
    Hora horaFin;
    int sala;
    int contAsientosDisponibles;
    Fecha fecha; /// damos una fecha que indique cuando se suma a la cartelera. si la pelicula lleva dos meses en cartelera el tercer mes no se muestra.

    public:
        bool cargarFuncion(); /// usar los set para cargar y validar antes de usar los get.
        void mostrarFuncion(Funcion *);
        bool grabarEnDisco(Funcion );
        bool grabarEnDisco(Funcion , int);
        void leerDeDisco();
        bool bajaFunciones();
        bool leerDeDisco(int);
    /// que retorne bool asi es mas faclil.

//    Funcion::Funcion(){
//    contAsientosDisponibles=100;  //VER DÓNDE PONER EL CONSTRUCTOR  Naza, 02/07
//    }

        ///setters deben tener validaciones dentro para que la carga este en limpio.
    void setTitulo(const char *);
    void setTipoDePelicula(int);
    void setIDfuncion(int);
    void setCodigoPelicula(int);
    void setHoraInicio(Hora);
    void setHoraFin(Hora);
    void setSala(int);
    void setActivo(int);
    void setAsientosDisponibles(int );
    void setFecha(Fecha); /// fecha que la funcion aparece en cartelera.
    ///getters
    int getAsientosDisponibles(){return contAsientosDisponibles;}
    int getIDfuncion(){return idFuncion;}
    int getCodigoPelicula(){return idPelicula;}
    Hora getHoraInicio(){return horaInicio;}
    Hora getHoraFin(){return horaFin;}
    int getSala(){return sala;}
    int getTipoDePelicula(){return tipoDePelicula;}
    Fecha getFecha(){return fecha;}




};
///->Jony: terminar de conectar Funciones con Películas
///        en Venta.cpp> setMonto> buscarTipoPelicula() , fijate de que la función buscarTipoPelicula devuelva bien el tipo

/// hicimos global una funcio para mostrar las funcines disponibles, declarandola en funcionesGenerales.h y dandole cuerpo en el .cpp
/// y llamandola en el main como la opcion 2.
/// en sector empleados.h dejamos una nota de que debemos dar una funcion para cargar los horarios disponibles. que en realidad
/// serian las funciones disponibles.

#endif // FUNCION_H

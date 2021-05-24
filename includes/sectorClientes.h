#ifndef SECTORCLIENTES_H_INCLUDED
#define SECTORCLIENTES_H_INCLUDED
using std::cout;
#include "sectorEmpleados.h"
#include "rlutil.h"
using namespace rlutil;

//Funciones correspondientes al menú de clientes (o menú general):

void menuClientes(){
    setColor(LIGHTRED);
    gotoxy(10,2);
    cout<<" ---------------------------------------"<<endl;
    setColor(LIGHTCYAN);
    gotoxy(10,3);
    cout<<"|             ROCKET-CINEMA             |";
    setColor(LIGHTRED);
    gotoxy(10,4);
    cout<<" ---------------------------------------"<<endl;
    setColor(YELLOW);
    gotoxy(10,5);
    cout<<"| 1) VER PELÍCULAS EN CARTELERA         |"<<endl;
    setColor(LIGHTRED);
    gotoxy(10,6);
    cout<<"| 2) CONSULTAR FUNCIONES DISPONIBLES    |"<<endl;
    setColor(YELLOW);
    gotoxy(10,7);
    cout<<"| 3) CONSULTAR PRECIO DE ENTRADAS       |"<<endl;
    setColor(LIGHTRED);
    gotoxy(10,8);
    cout<<"| 4) CONSULTAR PROMOCIONES VIGENTES     |"<<endl;
    setColor(YELLOW);
    gotoxy(10,9);
    cout<<"| 5) REGISTRARSE COMO CLIENTE           |"<<endl;
    setColor(LIGHTRED);
    gotoxy(10,10);
    cout<<"| 6) CONSULTAR COMPRAS REALIZADAS       |"<<endl;
    setColor(YELLOW);
    gotoxy(10,11);
    cout<<"| 7) REALIZAR COMPRA DE ENTRADAS        |"<<endl;
    setColor(LIGHTRED);
    gotoxy(10,12);
    cout<<" ---------------------------------------"<<endl;
    setColor(MAGENTA);
    gotoxy(10,13);
    cout<<"  0)        FINALIZAR PROGRAMA   "<<endl<<endl;
    setColor(WHITE);
    gotoxy(10,15);
    cout<<"Ingrese una opción: ";
}
//----------------------------------------------------------------------



#endif // SECTORCLIENTES_H_INCLUDED

/*Cambios hechos por mi (Cris) 20/06 -Pasadas a getters y setters las funciones cargar y mostrar de cliente
                                     -Pasada a funcion global con setters y getters, validarFecha y validarHora
                                     -Solucionados errores en clase venta
                                     -Iniciado el pasaje de cargar y mostrar en pelicula.cpp con getters y setters
                                     -Pasaje de algunas funciones mal declaradas (dentro de la clase) a funciones globales

                            25-26/06 -Pasados los setters de Cliente a booleanos como indico el profe
                                     -Convertidas las funciones erroneamente declaradas dentro de Cliente, a funciones globales
                                     -Efectuados cambios recomendados en la clase pelicula
                                     -Pasados a bool los setters de Pelicula, agregadas funciones de validacion
                                     -Añadido el atributo minutos a pelicula, con sus respectivas validaciones, sets, gets, etc
                                     -Añadidas validaciones de ingresos int y float, para que no rompa el programa si se ingresa un char u otra cosa que no corresponda
*/
/*
Hacer clase funcion.
la clase pelicula representara solo a la pelicula, la clase funcion seria la otra parte.
Entradas vuela no existe mas.
La entrada debe ser reemplazada por un registro de venta.
Las peliculas deberian mostrarse solo las vigentes. osea las q se estrenan en adelante.
las peliculas deben tener fecha de vencimiento.
El titulo no pude representar la pelicula por eso hacerle un ID a al pelicula.
usar un codigo de funcion, para guardar en la venta en vez de la pelicula.(guardamos el codigo de funcion.)
la venta va a ser de una funcion y no de una pelicula.
*/

/*Cambios hechos por Naza:
 implementados los setters y getters en la función de cargarVenta (venta.cpp)
 para lo cual también añadí algunas funciones globales de búsqueda (prototiposgenerales.cpp)
 *No olvidar, Cris, que hay una función global que llama a la carga de los clientes (también en proto.cpp)
 Para hacer bien la búsqueda del precio, sería conveniente hacer una clase Entrada y que guarde los 3 precios como único atributo
 */

/* Cambios realizados por Naza el 25/06:
            Descomenté toda la función de precioEntrada(int); //en funcionesGenerales.cpp

            Agregué el PATH_ENTRADAS
            //en Entrada.cpp

            Puse los private y public de Entrada
            //en Entrada.h

            Definí los set y gets de Entrada
            //en Entrada.cpp

            Definí las relaciones entre los métodos
            //en Entrada.cpp

            Definí la función global del sectorEmpleados.cpp "cargarPrecios"
            //en funcionesGenerales.cpp

            void cargarPrecios(){
            Entrada obj;
            int num;
            cout<<"Ingrese el tipo de precio a modificar: ";
            cout<<"          (1=XD, 2=2D, 3=3D"<<endl;
            cin>>num;
            if(obj.modificarPrecio(&obj)){
            if(obj.grabarPrecio(num){
            cout<<---Precio cargado correctamente---";
            anykey();
            return;
            }
            }

            Hice la función consultarPrecio de entrada del main, en funcionesGenerales.cpp

    30/06 DID:
    ->Cris: vista la parte de Venta y las Promociones
    ->Naza: terminado de cargar Precios y el registro de Clientes nuevos (ver ingresarNuevoCliente(); )
*/


/*TO DO 29/06:
->Jony: terminar de conectar Funciones con Películas
        en Venta.cpp> setMonto> buscarTipoPelicula() , fijate de que la función buscarTipoPelicula devuelva bien el tipo
->Mati:  hacer una función para listar las películas disponibles
        según género.
->Cris: hacer la carga de las funciones, determinando los horarios de inicio, y que a partir de este y el horario de la película.
            te determine el horario de fin.
->Naza: hacer función de realizarCompra con las linkeadas

-----> ¡VALIDAR INGRESOS! <------
*/

/* 03/07 DID:
   ->Cris: Solucionado problema en el algoritmo de calcularEdad(devolvia siempre 0), problema en la carga del Cliente (no lo cargaba)
   ->Solucionado problema de generar ID automaticamente en Pelicula
   ->Agregadas funciones para listar dinamicamente Clientes, listarlos ordenados x apellido (de A a Z) y ordenados por edad (de menor a mayor)
   ->Agregado bool Fecha::operator> (puede servir para comparar fechas, o para crear un operator propio, tenerlo en cuenta)
   ->

TO DO 03/07
 ->Vector Dinamico de peliculas, funciones y ventas, funciones para ordenarlos (hay como referencia el de Clientes)
 ->Validaciones de todo tipo que hayan quedado en el aire
 ->Funciones que muestren en los listados, en vez del genero como (1, 2, 3) que se vea (Masculino, Femenino, Otro) para todos los listados
 ->Chequear por que los listados no le funcionaban a mati con los gets (A mi me funciono sin problemas con Clientes)*/

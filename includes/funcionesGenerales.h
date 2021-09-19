#ifndef FUNCIONESGENERALES_H_INCLUDED
#define FUNCIONESGENERALES_H_INCLUDED

#include "rlutil.h"
using namespace rlutil;
#include "Venta.h"
#include "Cliente.h"
#include "Funcion.h"
#include "Pelicula.h"

//Funciones de la parte correspondiente al menú de los clientes (permite hacer consultas)
void anadirPelicula();
void consultarPeliculas();
void consultarHorarios();
void consultarPrecios();
void consultarPromociones();
void realizarCompra();
int sectorEmpleados();
void consultarCompras();


//Funciones correspondientes al menú de los empleados (permite hacer modificaciones y obtener reportes)

void cargarHorario();
void cargarPrecios();
void cargarPromociones();
void consultarClientes();
void consultarVentas();
void configuracion();
void menuConfiguracion();

//backups y restauracion debajo
bool CrearBackUpClientes();  //Back ups y restauracion, hechos x Cris (8/7)
bool CrearBackUpPeliculas();
bool CrearBackUpVentas();
bool CrearBackUpFunciones();
void BackUpTodos();

bool RestaurarClientes();
bool RestaurarPeliculas();
bool RestaurarVentas();
bool RestaurarFunciones();
void RestaurarTodos();

//reportes debajo
bool recaudacionAnual();
bool recaudacionMensual(); //-Cris (8/7)
void recaudacionPorTitulo();
bool recaudacionEntreFechas();




//--------------------------

/*en prototipos generales borré las funciones las 3 funciones, y la de Jony de consultar precio por título*/
//--------------------------

//Funciones globales del reboot del proyecto

bool ingresarNuevoCliente();    //Cris, atenti!

bool ingresarNuevoCliente(long );

int buscarTipoPelicula(int);

float precioEntrada(int);

int buscarCliente(long);

bool validarFecha(int, int, int); ///pasada a funcion global luego de la clase del 20/06 (Cris), 12/07 arreglado el tema de que permitia ingresar cualquier año

bool validarHora(int, int); ///lo mismo que validarFecha

bool crearVectorCliente();

int contarClientes();

void cargarVectorCliente(Cliente *, int);

void ordenarVClienteXApellido(Cliente *, int);

void ordenarVClienteXFechaNac(Cliente *, int);

void mostrarVectorCliente(Cliente *, int);

int buscarPelicula(int);

int buscarPelicula(char *);

int validarIngresoEntero();

float validarIngresoFlotante();

void funDisponibles();

void funDisponiblesHoy();

void funDisponiblesEstaSemana();

void recaudacionPorTitulo(char *, Fecha, Fecha);

int buscarFuncion(int);

bool aplicarDescuento(Fecha);

int comparandoID(int); /// recibe el ID de la pelicula, si existe retorna la posicion. sino encontro el archivo retorna -1, si encontro el archivo pero no existe el id retorna -2

void traigoGetTipoPelis(int,Funcion *);

bool checkSala(Funcion *); /// 7/7/20

int cantDFunciones();

int consultarAsientosDisponibles(int );   //Naza estuvo aquí, 02/07

void actualizarAsientosDisp(int, int );     //Aquí también :V

void ingresarPelicula();

void ingresarFuncion();

void listarPeliculas();

int generarIDPelicula();

void listarClientes();

bool listadoClientesxApellido();

bool listadoClientesxFechaNac();

bool crearVectorPelicula();

void cargarVectorPelicula(Pelicula *, int);

void mostrarVectorPelicula(Pelicula *, int);

int contarPeliculas();

void ordenarVPeliculaxTitulo(Pelicula *, int);

bool listadoPeliculasxFechaEstreno();

void ordenarVPeliculaxFechaEst(Pelicula *, int);

bool listadoPeliculasxTitulo();

void msj_error(const char *, int x = -1, int y = -1);

void msj_ok(const char *, int x = -1, int y = -1);

int idFuncionAutomatico();

int converMinAH(int);///para funciones

int converMinAM(int);///para funciones

string convertirGenero(int);

string convertirEstado(bool);

string devolverTipo(int);

int buscarMes(int);

long validarIngresoDNI();

int validarIngresoMes();

void msj_promo();

string devolverTitulo(int );

int validarIngresoAnio();

string buscarTitulo(int );

void recaudacionPorGenero();

string devolverGenero(int );

string devolverMes(int);

void reportes();

void menuReportes();

void confBackup();

void confRestaurar();

void menuBackup();

void menuRestaurar();

bool buscarPeliculaF(int);

///-------------------
bool traigoGetFechaPelicula(Fecha *, int); /// aca agrego la fecha de estreno a las funciones.

void modificarFechasPeliculas();

bool cambiarFechaEstrenoPeliculaYFechaVencimiento(int); /// si lo se...es el mejor nombre del mundo(?

bool fechaOk(int);

void listarPeliculasDisponibles();

bool cargaFechaEnFuncionOk(Fecha, Fecha);

int deHoraAmntI(Funcion *); /// hora de inicio a minutos:
int deHoraAmntF(Funcion *); /// hora de fin a minutos.

void verFunciones();

#endif // FUNCIONESGENERALES_H_INCLUDED

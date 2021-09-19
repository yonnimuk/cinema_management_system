#include <iostream>
using namespace std;
#include "rlutil.h"
using namespace rlutil;
#include "Fecha.h"
#include "Venta.h"
#include "funcionesGenerales.h"
#include "Cliente.h"
#include "Hora.h"

const char * PATH_VENTAS = "datos/ventas.dat";

bool Venta::setidFuncion(int nFunc){
    if(buscarFuncion(nFunc) == -1){  //Si devuelve algo distinto a -1, quiere decir que ya esta cargada
    msj_error("         ---Función no disponible---");
    cout << endl;
    cout<<"-Por favor, intente con otro número de función-"<<endl;
    anykey();
    return false;
    }
  idFuncion = nFunc;
  return true;
}

void Venta::setDniCliente(long dni){ //TENDRIAMOS QUE VER COMO TERMINAMOS ESTA
    if(!buscarCliente(dni)){
    msj_error("         ---Cliente no registrado---");
    cout<<" -Por favor regístrese antes de continuar-"<<endl;
    anykey();
    ingresarNuevoCliente(); //con esta función global, se crea  un objeto Cliente, y luego
                                //se hace uso de los métodos de Cliente cargar y guardar
  }

  dniCliente = dni;
}

bool Venta::setCantidadEntradas(int cantEntradas){
  this->cantidadEntradas = cantEntradas;
  return true;
}

void Venta::setfechaVenta(){
Fecha fechaActual;
int dia, mes, anio;
dia = fechaActual.getDia();
mes = fechaActual.getMes();
anio = fechaActual.getAnio();
fechaVenta.setDia(dia);
fechaVenta.setMes(mes);
fechaVenta.setAnio(anio);
}


void Venta::sethoraVenta(){
Hora horaActual;
int horas, minutos;
horas = horaActual.getHora();
minutos = horaActual.getMinutos();
horaVenta.setHora(horas);
horaVenta.setMinutos(minutos);

}

void Venta::setMonto(int cantEntr, int idFuncion){      //Naza estuvo aquí, 02/07
    int tipo=buscarTipoPelicula(idFuncion);               //paso el idFuncion, y en la misma, busca el tipo de película linkeada
    monto=precioEntrada(tipo)*cantEntr;
    if(aplicarDescuento(this->getfechaVenta())){
      msj_ok("Felicidades, es beneficiario del descuento de 30% por fin de mes, se le aplicará a su compra! ");
      anykey();
      monto*=0.7;
  }                                                     //precioEntrada tiene asignados los precios de acuerdo al tipo                                                    //falta desarrollar las funciones buscarTipoPelicula y precioEntrada
}



//-----------------------------
int Venta::getidFuncion(){
  return idFuncion;
}

long Venta::getDniCliente(){
  return dniCliente;
}

int Venta::getCantidadEntradas(/*int*/ ){ //sería para sacar el reporte de ventas de acuerdo al tipo de entrada vendida
  return cantidadEntradas;
}

Fecha Venta::getfechaVenta(){
  return fechaVenta;
}

Hora Venta::gethoraVenta(){
  return horaVenta;
}

float Venta::getMonto(){
  return monto;
}
//------------------------------
bool Venta::cargarVenta(){
int cantFunc = cantDFunciones();
cout<<"Número de función: ";
int numFunc;
numFunc = validarIngresoEntero();
cin.ignore();

if(numFunc<=0||numFunc>cantFunc){
    cout << endl;
    msj_error("Número de función inválido, intente nuevamente con uno válido");
    cout << endl;
    anykey("Presione cualquier tecla para continuar. . .");
    return false;
}

cout<<endl<<"Película: ";
setColor(LIGHTCYAN);
cout<<buscarTitulo(numFunc)<<endl;
setColor(WHITE);

if(!setidFuncion(numFunc)){
  return false;
}

Funcion obj;
Fecha fe;
Hora aux;
int pos=buscarFuncion(numFunc);
if(obj.leerDeDisco(pos)){
if(!fechaOk(obj.getCodigoPelicula())){
        cout<<endl;
        msj_error("---Error, la película proyectada en la función seleccionada no se encuentra disponible---");
        cout<<endl;
        anykey("---Presione una tecla para continuar---");
        return false;
}

if((obj.getFecha() < fe)||(obj.getFecha() == fe && obj.getHoraInicio() < aux)) {
        cout<<endl;
        msj_error("---Error, la función seleccionada ya inició---");
        cout<<endl;
        anykey("---Presione una tecla para continuar---");
        return false;
  }
}

cout<< "DNI cliente: ";
long dniCli;
dniCli = validarIngresoDNI();
cin.ignore();
if(buscarCliente(dniCli)==-1){
    msj_error("      ---Cliente no registrado---");
    cout<<"---Debe registrarse antes de continuar---"<<endl;
    anykey();
    if(!ingresarNuevoCliente(dniCli)){
        cout<<endl<<endl;
        msj_error("---Error en el registro de cliente, inténtelo de nuevo---");
        anykey("---Presiona una tecla para volver al menú principal---");
        return false;
    }
}
setDniCliente(dniCli);

cout<<"Cantidad de entradas: ";
int cantEntr;
cantEntr = validarIngresoEntero();
while(cantEntr<=0){
    cout<<"---Error, la cantidad de entradas no puede ser igual o menor a 0---"<<endl;
    cout<<"          ---Por favor, ingrese una cantidad válida---"<<endl;
    anykey();
    cout<<"Cantidad de entradas: ";
    cantEntr = validarIngresoEntero();
}
cin.ignore();
int asientosDisp=consultarAsientosDisponibles(numFunc);  //hice estas funciones. Naza, 02/07
while(cantEntr>asientosDisp){
    msj_error("---Disculpe, la cantidad de asientos no está disponible---");
    cout<<"---Actualmente, para esta función, hay "<<asientosDisp<<" disponibles"<<endl;

    cout<< "Ingrese una nueva cantidad de entradas: " << endl;
    cin.get();
    cantEntr = validarIngresoEntero();
    cin.ignore();
}
setCantidadEntradas(cantEntr);      //rehice esto

actualizarAsientosDisp(cantEntr, numFunc);      //e hice esto

setfechaVenta();

sethoraVenta();

setMonto(cantEntr, numFunc);        //rehice esto x2   P.D.: a las funciones de cargar involucradas, les pasé los obj por valor.
for(int i=0; i<3; i++){
        cout<<".";
        msleep(500);
}
cout <<endl<< "Monto a pagar: ";
setColor(LIGHTGREEN);
cout<<"$"<<getMonto();
setColor(WHITE);
cin.get();
return true;
}

bool Venta::leerDeDisco(int pos){
  FILE * p = fopen(PATH_VENTAS, "rb");
  if(p == NULL){
    msj_error("No se pudo abrir el archivo. ");
    anykey();
    return false;
  }
  fseek(p, sizeof *this * pos, 0);
  bool leyo = fread(this, sizeof *this, 1, p);
  fclose(p);
  return leyo;
}

bool Venta::leerDeDisco(){
  FILE * p = fopen(PATH_VENTAS, "rb");
  if(p == NULL){
    msj_error("No se pudo abrir el archivo. ");
    anykey();
    return false;
  }
  fread(this, sizeof *this, 1, p);
  fclose(p);
  return true;
}

bool Venta::grabarEnDisco(Venta obj){
  FILE * p = fopen(PATH_VENTAS, "ab");
  if(p == NULL){
    msj_error("---No se pudo abrir el archivo---");
    anykey();
    return false;
  }
  bool escribio = fwrite(&obj, sizeof(Venta), 1, p);
  fclose(p);
  return escribio;
}

void Venta::mostrarVenta(){  //Creo que se puede hacer sin necesidad de declarar objeto, como en Pelicula y Cliente
  cout << "ID de la funcion: " << getidFuncion() << endl;
  cout << "DNI del cliente: " << getDniCliente() << endl;
  cout << "Cantidad de entradas compradas: " << getCantidadEntradas() << endl;
  cout << "Fecha de la venta (DD/MM/AAAA): " << getfechaVenta().getDia() << "/" << getfechaVenta().getMes() << "/" << getfechaVenta().getAnio() << endl;
  cout << "Hora de la venta (HH/MM): ";
    if( ( gethoraVenta().getHora() <= 9 ) && ( gethoraVenta().getHora() >=00 ) ) /// parachazo para mostrar "0" antes de un numero menor o igual a 9 en la hora
    {
        cout << "0" << gethoraVenta().getHora();
    }else{cout << gethoraVenta().getHora();}
    if( ( gethoraVenta().getMinutos() <= 9) && ( gethoraVenta().getMinutos() >= 0) )
    {
        cout << ":0" << gethoraVenta().getMinutos() << endl;
    }else{cout << ":" << gethoraVenta().getMinutos() << endl;}

}

void realizarCompra(){
cls();                    //cuidado al copiar los cambios de Cris, de no pisar esto! Naza, 30/06
Venta obj;
if(obj.cargarVenta()==1){
if(obj.grabarEnDisco(obj)==1){
msj_ok("---Compra efectuada exitosamente---");
cin.get();
   }
 }
}

void consultarCompras(){//Tuve que comentar la parte de estado o me impedía devolver un msj error si el DNI no existía. -Cris 7/7
cls();
long dni;
int busqueda;
int posicion = 0;
Venta obj;
cout<<"Ingrese su DNI: ";
dni = validarIngresoDNI();
cin.ignore();
if(dni<3000000 || dni>50000000){
  cls();
  msj_error("El DNI ingresado es inválido");
  cout << endl;
  anykey("Presione cualquier tecla para retornar. . .");
  return;
}
cls();
busqueda = buscarCliente(dni);

if(busqueda!=-1){
    setColor(LIGHTCYAN);
    cout << "Listado de compras para el DNI número " << dni << ":" << endl;
    setColor(WHITE);
    cout << endl;
    while(obj.leerDeDisco(posicion++)){
      if(obj.getDniCliente() == dni){
      obj.mostrarVenta();
      cout << endl;
      }
    }
    anykey("Presione cualquier tecla para continuar. . .");
  }
  else{
  cls();
  setColor(LIGHTRED);
  cout << "El DNI " << dni << " no está registrado, regístrese para continuar. . ." << endl;
  setColor(WHITE);
  cout << endl;
  anykey("Presione cualquier tecla para retornar. . .");
  }
}


void consultarVentas(){
  cls();
  int mes, anio, busqueda, pos = 0;
  Venta obj;
  Fecha actual;
  anio = actual.getAnio();
  cout << "Ingrese el número de mes sobre el cual quiera consultar las ventas (será acorde a este año): " << endl;
  mes = validarIngresoMes();
  cin.ignore();
  if(mes<1||mes>12){
    cls();
    msj_error("Mes inválido, por favor, reintente con un mes válido.");
    cout << endl;
    anykey("Presione cualquier tecla para retornar. . .");
    return;
  }
  cls();
  busqueda = buscarMes(mes);
  if(busqueda!=-1){

    setColor(LIGHTMAGENTA);
    cout << "Listado de ventas para el mes de " << devolverMes(mes) << " del año " << anio << "." << endl;
    setColor(WHITE);
    cout << endl;
    while(obj.leerDeDisco(pos++)){
      if(obj.getfechaVenta().getMes() == mes){
      obj.mostrarVenta();
        cout << endl;
      }
    }
    anykey("Presione cualquier tecla para continuar. . .");
  }
  else{
  setColor(LIGHTRED);
  cls();
  cout << "No se encontraron ventas para el mes de " << devolverMes(mes) << " del año " << anio << "." << endl;
  setColor(WHITE);
  cout << endl;
  anykey("Presione cualquier tecla para retornar. . .");
  }
}



#include <iostream>
using namespace std;
#include "funcionesGenerales.h"
#include "Fecha.h"
#include "Cliente.h"
#include "rlutil.h"
using namespace rlutil;

const char * PATH_CLIENTES = "datos/clientes.dat";


bool Cliente::cargarCliente(){ //Solucionado problema de que no cargaba el cliente(porque no setteaba el estado), mostraba 0 en edad(tampoco la setteaba, ahora muestra la edad correcta), Cris 3/7
Fecha actual;
bool estadoCliente = false;
setEstado(estadoCliente);

cout << "DNI Cliente: ";
  long longAux;
  longAux = validarIngresoDNI();
  cin.ignore();
  if(!setDniCliente(longAux)){
    return false;
  }

   if(buscarCliente(longAux)==-1){

    cout << "Nombre: ";
    char charAux[30];
    cin.getline(charAux,30);
   if(!setNombreCliente(charAux)){
     return false;
   }

    cout << "Apellido: ";
    cin.getline(charAux,30);
    if(!setApellidoCliente(charAux)){
      return false;
    }
    cout << "Género: (1: Masculino// 2: Femenino// 3: Otro) " << endl;
    int generoAux;
    cin>> generoAux;
    cin.ignore();
    if(!setGeneroCliente(generoAux)){
      return false;
    }

    cout << "Fecha de nacimiento: ";
    if(fechaNac.cargarFecha() && actual-fechaNac <= 80 && actual-fechaNac >= 13){
      estadoCliente = true;
      setEstado(estadoCliente);
      return true;
    }
    else{
      cout << endl;
      msj_error("No hemos podido registrarle como cliente. Verifique el ingreso de datos.");
      cout << endl;
      anykey("Presione cualquier tecla para continuar. . .");
      return false;
    }
   }
   cout << endl;
   msj_error("El DNI ingresado ya se encuentra registrado.");
   cout << endl;
   anykey("Presione cualquier tecla para retornar. . .");
   return false;
  }

  bool Cliente::cargarCliente(long dniCli){  //acabo de hacerla, Naza 04/07
bool estadoCliente = false;
setEstado(estadoCliente);

cout<<endl<< "DNI Cliente: "<<dniCli;
  if(!setDniCliente(dniCli)){
    return false;
  }
    cin.ignore();
    cout << "Nombre: ";
    char charAux[30];
    cin.getline(charAux,30);
   if(!setNombreCliente(charAux)){
     return false;
   }

    cout << "Apellido: ";
    cin.getline(charAux,30);
    if(!setApellidoCliente(charAux)){
      return false;
    }
    cout << "Género: (1: Masculino// 2: Femenino// 3: Otro) " << endl;
    int generoAux;
    generoAux = validarIngresoEntero();
    cin.ignore();
    if(!setGeneroCliente(generoAux)){
      return false;
    }

    cout << "Fecha de nacimiento: ";
    if(fechaNac.cargarFecha()){
      estadoCliente = true;
      setEstado(estadoCliente);

      return true;
    }
    else{
      cout << endl;
      msj_error("No se pudo realizar la carga del cliente. Por favor, verifique el ingreso de datos");
      cout << endl;
      anykey("Presione cualquier tecla para continuar. . .");
      return false;
    }
  }


  bool Cliente::grabarEnDisco(){
  FILE *p = fopen(PATH_CLIENTES,"ab");
    if(p == NULL){
       cout << endl;
       msj_error("Error en la apertura del archivo.");
       cout << endl;
       anykey("Presione cualquier tecla para continuar. . .");
        return false;
    }
    bool escribio = fwrite(this, sizeof *this, 1, p);
    fclose(p);
    return escribio;
  }

  void Cliente::mostrarCliente(){
    if(estado){
      cout << "DNI del cliente: " << getDniCliente() << endl;  //Esto si me funciono mati, no se por que no te funciono en Pelicula, raro
      cout << "Nombre del cliente: " << getNombreCliente() << endl;
      cout << "Apellido del cliente: " << getApellidoCliente() << endl;
      cout << "Género: " << convertirGenero(getGeneroCliente()) << endl;
      int edadCliente = calcularEdad(getfechaNac());
      setEdadCliente(edadCliente);
      cout << "Edad: " << getEdad() << " años " << endl;
      cout << "Estado: " << convertirEstado(getEstado()) << endl;

    }
  }

  bool Cliente::leerDeDisco(int posicion){
    FILE *p = fopen(PATH_CLIENTES,"rb");
    if(p == NULL){
       cout << endl;
       msj_error("No se pudo abrir el archivo. ");
       cout << endl;
       anykey("Presione cualquier tecla para continuar. . .");
        return false;
    }
    fseek(p, sizeof *this * posicion, 0);
    bool leyo = fread(this, sizeof *this, 1, p);
    fclose(p);
    return leyo;

  }

  int Cliente::calcularEdad(Fecha _fechaNac){
    int edadCliente;
    Fecha fe;
  Fecha actual = Fecha();
  edadCliente = actual.getAnio() - _fechaNac.getAnio();
    if((fe.getMes() == _fechaNac.getMes() && fe.getDia() < _fechaNac.getDia() )||(fe.getMes() < _fechaNac.getMes())){
        edadCliente--;
    }
    return edadCliente;
}


  //setters y getters debajo

  bool Cliente::setNombreCliente(const char * nombre){
  if(strcasecmp(nombre,"\0")== 0){
    cout << endl;
    msj_error("No puede dejar el campo nombre vacío. ");
    cout << endl;
    anykey("Presione cualquier tecla para continuar. . .");
    return false;
    }
  strcpy(this->nombre,nombre);
  return true;
  }

  bool Cliente::setApellidoCliente(const char * apellido){
  if(strcasecmp(apellido,"\0")== 0){
        cout << endl;
        msj_error("El apellido no puede quedar vacío. ");
        cout << endl;
        anykey("Presione cualquier tecla para continuar. . .");
        return false;
    }
  strcpy(this->apellido,apellido);
  return true;
  }

  bool Cliente::setGeneroCliente(int genero){
  if(genero!=1 && genero!=2 && genero!=3){
        cout << endl;
        msj_error("El género ingresado es inválido.");
        cout << endl;
        anykey("Presione cualquier tecla para continuar. . .");
        return false;
    }
  this->genero=genero;
  return true;
  }

  bool Cliente::setDniCliente(long dni){
  if(dni<3000000 || dni>50000000){
    cls();
    msj_error("No se pudo cargar el DNI, el mismo no es válido. ");
    cout << endl;
    anykey("Presione cualquier tecla para continuar. . .");
    return false;
    }
    this->dni = dni;
    return true;
}

void Cliente::mostrarTodosLosClientes(){
Cliente cli; int pos=0;
while(cli.leerDeDisco(pos++)){
    cli.mostrarCliente();
  }
  cin.get();
}

void listarClientes(){
Cliente obj;
obj.mostrarTodosLosClientes();
}

  void Cliente::setEstado(bool estado){
  this->estado = estado;
  }

  void Cliente::setEdadCliente(int edad){
  this->edad=edad;
  }

  char * Cliente::getNombreCliente(){
  return nombre;
  }

  char * Cliente::getApellidoCliente(){
  return apellido;
  }

  int Cliente::getEdad(){
  return edad;
  }

  int Cliente::getGeneroCliente(){
  return genero;
  }

  long Cliente::getDniCliente(){
  return dni;
  }

  Fecha Cliente::getfechaNac(){
  return fechaNac;
  }

  bool Cliente::getEstado(){
  return estado;
  }

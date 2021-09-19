#ifndef CLIENTE_H
#define CLIENTE_H


#include <cstring>
#include "Fecha.h"

class Cliente{
    private:
  char nombre[30];
  char apellido[30];
  int genero;
  long dni;
  Fecha fechaNac;
  bool estado;
  int edad;

    public:
  bool cargarCliente();
  bool cargarCliente(long);
  bool grabarEnDisco();
  void mostrarCliente();
  bool leerDeDisco(int);
  int calcularEdad(Fecha);
  void mostrarTodosLosClientes();


  //setters
  bool setNombreCliente(const char *);
  bool setApellidoCliente(const char *);
  bool setDniCliente(long);
  void setEstado(bool);
  bool setGeneroCliente(int );
  void setEdadCliente(int);


  //getters
  char * getNombreCliente();
  char * getApellidoCliente();
  int getGeneroCliente();
  long getDniCliente();
  Fecha getfechaNac();
  bool getEstado();
  int getEdad();

 };

#endif // CLIENTE_H

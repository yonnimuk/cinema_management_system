#ifndef VENTA_H
#define VENTA_H

#include "Hora.h"
#include "Fecha.h"

class Venta{
    private:
  int idFuncion;
  long dniCliente;
  int cantidadEntradas; //nSucursal ya no forma parte, porque eso pertenece a la clase Función
  Fecha fechaVenta;
  Hora horaVenta;
  float monto;
  bool descuento;
    public:
  bool cargarVenta();
  void mostrarVenta();
  bool leerDeDisco(int);
  bool leerDeDisco();
  bool grabarEnDisco(Venta);

  //setters
  bool setidFuncion(int);
  void setDniCliente(long);
  bool setCantidadEntradas(int);
  void setfechaVenta();
  void sethoraVenta();
  void setMonto(int, int);


  //getters

  int getidFuncion();
  long getDniCliente();
  int getCantidadEntradas(/*int*/);
  Fecha getfechaVenta();
  Hora gethoraVenta();
  float getMonto();


};

#endif // VENTA_H

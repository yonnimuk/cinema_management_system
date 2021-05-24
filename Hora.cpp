#include <iostream>
using namespace std;
#include "rlutil.h"
using namespace rlutil;
#include <ctime>
#include "funcionesGenerales.h"
#include "Hora.h"
#include "Fecha.h"
#include "Cliente.h"
#include "Pelicula.h"


bool Hora::cargarHora(){
  int h, m;
  cout << "Hora: ";
  h = validarIngresoEntero();
  cin.ignore();
  cout << "Minutos: ";
  m = validarIngresoEntero();
  cin.ignore();

  bool horaValida = validarHora(h, m);
    if(horaValida){
        setHora(h);
        setMinutos(m);
        return true;

    }
    else{
        msj_error("Hora inválida.");
        return false;
        anykey("Presione cualquier tecla para continuar. . .");
    }

}


void Hora::mostrarHora(){
  cout << getHora() << ":" << getMinutos() << endl;
}

 Hora::Hora(){
  time_t timestamp;
  timestamp = time(NULL);
  tm *f;
  f = localtime(&timestamp);
  hora = f->tm_hour;
  minutos = f->tm_min;
}

Hora::Hora(int hora, int minutos){
  this->hora = hora;
  this->minutos = minutos;
}

//setters y getters debajo

void Hora::setHora(int hora){
  this->hora = hora;
}

void Hora::setMinutos(int minutos){
  this->minutos = minutos;
}

int Hora::getHora(){
  return hora;
}

int Hora::getMinutos(){
  return minutos;
}


bool Hora::operator<(Hora obj) //Hora obj es la hora de la función
{
   if (hora <= obj.getHora() && minutos < obj.getMinutos())
      return true;
   if (hora < obj.getHora() && minutos >= obj.getMinutos())
      return true;
   return false;
}

bool Hora::operator>(Hora obj)
{
   if (hora >= obj.getHora() && minutos > obj.getMinutos())
      return true;
   if (hora > obj.getHora() && minutos <= obj.getMinutos())
      return true;
   return false;
}


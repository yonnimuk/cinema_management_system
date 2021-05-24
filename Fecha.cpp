#include <iostream>
using namespace std;
#include "rlutil.h"
using namespace rlutil;
#include <ctime>
#include "funcionesGenerales.h"
#include "Fecha.h"
#include "Cliente.h"

bool Fecha::cargarFecha(){
  int d, m, a;
  cout << "Día: ";
  d = validarIngresoEntero();
  cin.ignore();
  cout << "Mes: ";
  m = validarIngresoEntero();
  cin.ignore();
  cout << "Año: ";
  a = validarIngresoEntero();
  cin.ignore();

  bool fechaValida = validarFecha(d, m, a);
    if(fechaValida){
        setDia(d);
        setMes(m);
        setAnio(a);
        return true;

    }
    else{
        msj_error("Fecha inválida. ");
        return false;
        anykey("Presione cualquier tecla para continuar. . .");
    }

}

void Fecha::mostrarFecha(){
  cout << getDia() << "/" << getMes() << "/" << getAnio() << endl;
}

 Fecha::Fecha(){
  time_t timestamp;
  timestamp = time(NULL);
  tm *f;
  f = localtime(&timestamp);
  dia = f->tm_mday;
  mes = f->tm_mon + 1;
  anio = f->tm_year + 1900;
}

Fecha::Fecha(int dia, int mes, int anio){
  this->dia = dia;
  this->mes = mes;
  this->anio = anio;
}


//setters y getters debajo

void Fecha::setFecha(Fecha obj)
{
    dia=obj.getDia();
    mes=obj.getMes();
    anio=obj.getAnio();
}

void Fecha::setDia(int dia){
  this->dia = dia;
}

void Fecha::setMes(int mes){
  this->mes = mes;
}

void Fecha::setAnio(int anio){
  this->anio = anio;
}

int Fecha::getDia(){
  return dia;
}

int Fecha::getMes(){
  return mes;
}

int Fecha::getAnio(){
  return anio;
}

bool Fecha::operator>(Fecha obj)
{
   if (anio > obj.getAnio())
      return true;
   if (anio == obj.getAnio() && mes > obj.getMes())
      return true;
   if (anio == obj.getAnio() && mes == obj.getMes() && dia > obj.getDia())

      return true;
   return false;
}



bool Fecha::operator==(Fecha obj){
if(anio == obj.getAnio() && mes == obj.getMes() && dia == obj.getDia())
    return true;
  return false;
}
bool Fecha::operator<(Fecha obj)
{
   if (anio < obj.getAnio())
      return true;
   if (anio == obj.getAnio() && mes < obj.getMes())
      return true;
   if (anio == obj.getAnio() && mes == obj.getMes() && dia < obj.getDia())

      return true;
   return false;
}


bool Fecha::operator>=(Fecha obj)  //Solucionado mal funcionamiento de operadores >= y <= sobrecargados de fecha -Cris 12/07
{
   if (anio > obj.getAnio())
      return true;
   if (anio == obj.getAnio() && mes > obj.getMes())
      return true;
   if (anio == obj.getAnio() && mes == obj.getMes() && dia >= obj.getDia())

      return true;
   return false;
}

bool Fecha::operator<=(Fecha obj)
{
   if (anio < obj.getAnio())
      return true;
   if (anio == obj.getAnio() && mes < obj.getMes())
      return true;
   if (anio == obj.getAnio() && mes == obj.getMes() && dia <= obj.getDia())

      return true;
   return false;
}

int Fecha::operator-(Fecha obj)
{
  int tot = anio - obj.getAnio();
  if(mes == obj.getMes() && dia < obj.getDia())
    tot -=1;
  if(mes < obj.getMes())
    tot -=1;

  return tot;
}









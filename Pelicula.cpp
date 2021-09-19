#include <iostream>
using namespace std;
#include "funcionesGenerales.h"
#include "Fecha.h"
#include "Pelicula.h"
#include "rlutil.h"
using namespace rlutil;

const char * PATH_PELICULAS = "datos/peliculas.dat";

bool Pelicula::modificarPelicula(int idPelicula) /// que modifique. las fechas.
{
    Pelicula objp;

    return true;
}


bool Pelicula::cargarPelicula(){

  int genero; int tipo; int cantMin; char auxTitulo[50];

///GENERA ID DE LA MOVIE
  int newID = generarIDPelicula(); //SOLUCIONADO PROBLEMA DEL ID AUTOMATICO, Cris 3/7
  setIDPelicula(newID);

///SETEA EL TITULO
  cout<<"ID de película: "<<newID<<endl;
  cout<<"Título de la película: ";
  cin.getline(auxTitulo, 50);
    if(buscarPelicula(auxTitulo)!=-1){
      msj_error("La película ya se encuentra cargada.");
      anykey();
      return false;
    }
    if(!setTituloPelicula(auxTitulo)){
      return false;
    }

///FECHA DE ESTRENO
  cout << "Ingrese la fecha de estreno de la misma (DD/MM/AAAA): " << endl;
  if(!fechaEstreno.cargarFecha()){
    cin.get();
    return false;
  }

///FECHA DE VENCIMIENTO
  cout << "Ingrese la fecha de Vencimiento de la misma (DD/MM/AAAA): " << endl; /// agrege esto. atte: yonni 11/7
  if(!fechaVencimiento.cargarFecha()){
    cin.get();
    return false;
  }

  if(fechaEstreno >= fechaVencimiento){
    cout << endl;
    msj_error("La fecha de estreno no puede ser posterior o igual a la de vencimiento");
    cin.get();
    return false;
  }

///GENERO
  cout << "Género de la película: " << endl;
  cout<<"1- Terror "<<endl;
  cout<<"2- Accion "<<endl;
  cout<<"3- Comedia "<<endl;
  cout<<"4- Drama "<<endl;
  cout<<"5- Ciencia ficcion "<<endl;
  cout<<"6- Infantil "<<endl;
  cin>>genero;
  if(!setGeneroPelicula(genero)){
    return false;
  }

///TIPO DE PELI
  cout << "Tipo de película: 1 para XD, 2 para 2D y 3 para 3D " << endl;
  tipo = validarIngresoEntero();
  cin.ignore();
  if(!setTipoPelicula(tipo)){
    return false;
  }

///MINUTOS DE DURACION
cout<<"Ingrese los minutos de duración de la película: "<<endl;
cin>>cantMin;
if(!setMinutosPelicula(cantMin)){
    return false;}

msj_ok("---Película añadida exitosamente---");
anykey("Presione cualquier tecla para continuar. . .");
return true;
}

///GRABA PELICULA EN DISCO
bool Pelicula::grabarEnDisco(){
  FILE * p = fopen(PATH_PELICULAS,"ab");
    if(p == NULL) {
    msj_error("No se pudo abrir el archivo. ");
    cin.get();
      return false;
    }
    bool escribio = fwrite(this, sizeof *this, 1, p);
    fclose(p);
    return escribio;
 }

 bool Pelicula::grabarEnDisco(int pos){
  FILE * p = fopen(PATH_PELICULAS,"rb+");
    if(p == NULL) {
    msj_error("No se pudo abrir el archivo. ");
    cin.get();
      return false;
    }
    fseek(p,sizeof *this * pos,0);
    bool escribio = fwrite(this, sizeof *this, 1, p);
    fclose(p);
    return escribio;
 }

///MUESTRA PELICULAS
void Pelicula::mostrarPelicula(){
  cout << "ID Película: " << getIdPelicula()<<endl;
  cout << "Título de película: " << getTituloPelicula() << endl;
  cout << "Fecha de estreno: " << fechaEstreno.getDia() <<  "/" <<fechaEstreno.getMes()<< "/" <<fechaEstreno.getAnio()<<endl;
  cout << "Fecha de vencimiento: " << fechaVencimiento.getDia() <<  "/" <<fechaVencimiento.getMes()<< "/" <<fechaVencimiento.getAnio()<<endl; /// agrege esto. atte: yonni 11/7
  cout << "Género de película: " << devolverGenero(getGeneroPelicula())<< endl;
  cout << "Tipo de película: " << devolverTipo(getTipoPelicula()) << endl;
  cout << "Duración de película: " << getMinutosPelicula() << " minutos " << endl;
  if( fechaOk(this->getIdPelicula()) )
  {   setColor(LIGHTGREEN);
      cout<< "----DISPONIBLE-----" << endl;
      setColor(WHITE);

  }else{
      setColor(LIGHTRED);
      cout << "---NO DISPONIBLE---" << endl;
      setColor(WHITE);
  }
}

///LEE LAS PELICULAS CARGADAS EN EL DISCO
bool Pelicula::leerDeDisco(int posicion){
  FILE * p = fopen(PATH_PELICULAS, "rb");
    if(p == NULL){
      cout << "De momento no hay películas cargadas. Vuelva pronto! " << endl;
      cin.get();
      return false;
    }
    fseek(p, sizeof *this * posicion, 0);
    bool leyo = fread(this, sizeof *this, 1, p);
    fclose(p);
    return leyo;
}



//setters

void Pelicula::setIDPelicula(int idPelicula){
this->idPelicula = idPelicula;
}

bool Pelicula::setTituloPelicula(const char * tituloPelicula){
   if(strcasecmp(tituloPelicula,"\0")== 0){
      msj_error("ERROR. El título no puede quedar vacío. ");
      cin.get();
      return false;
      }
  else{
  strcpy(this->tituloPelicula, tituloPelicula);
  return true;
  }
}

bool Pelicula::setGeneroPelicula(int genero){
   if(genero>6||genero<1){
      msj_error("ERROR. El género ingresado no es válido. ");
      anykey();
      return false;
      }
   else{
   this->genero=genero;
  return true;
 }
}

bool Pelicula::setTipoPelicula(int tipo){
  if(tipo!=3 && tipo!=2 && tipo!=1){
    msj_error("El tipo ingresado es inválido. ");
    anykey();
    return false;
  }
  else this->tipo = tipo;
  return true;
}

bool Pelicula::setMinutosPelicula(int minutos){
if(minutos<60||minutos>300){
    msj_error("Error, toda película debe tener entre 60 y 300 minutos de duración.");
    cin.get();
    return false;
 }
  else {
    this->minutos = minutos;
    return true;
  }
}



//getters

char * Pelicula::getTituloPelicula(){
  return tituloPelicula;
}

Fecha Pelicula::getFechaEstreno(){
  return fechaEstreno;
}

int Pelicula::getDiaEstreno(){
  return fechaEstreno.getDia();
}

int Pelicula::getMesEstreno(){
  return fechaEstreno.getMes();
}

int Pelicula::getAnioEstreno(){
  return fechaEstreno.getAnio();
}

int Pelicula::getGeneroPelicula(){
  return genero;
}

int Pelicula::getTipoPelicula(){
  return tipo;
}

int Pelicula::getMinutosPelicula(){
  return minutos;
}

void ingresarPelicula(){
cls();                               //cuidado al copiar los cambios de Cris, de no pisar esto! Naza, 30/06
Pelicula obj;
if(obj.cargarPelicula()==1){
if(obj.grabarEnDisco()==1){
msj_ok("---Película cargada con éxito---");
   }
  }
}

///MUESTRA TODAS LAS PELICULAS DEL ARCHIVO
void Pelicula::mostrarTodasLasPeliculas(){
Pelicula regPeli; int pos=0;
while(regPeli.leerDeDisco(pos++)){
    regPeli.mostrarPelicula();
    cout << endl;
  }
  cin.get();
}





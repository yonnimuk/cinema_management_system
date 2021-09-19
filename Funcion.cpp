#include <iostream>
using namespace std;
#include "rlutil.h"
using namespace rlutil;
#include "Funcion.h"
#include "Fecha.h"
#include "funcionesGenerales.h"

const char *PATH_FUNCION = "datos/funcion.dat";

/**
    int idFuncion; /// random. o en orden creciente.(hecho)
    int idPelicula; /// hacer una funcion para que chequee que existe y si existe traer los datos necesarios.(hecho)
    int tipoDePelicula; /// a partir de la funcion que chekea y trae copiar y pegar el genero.(Hecho)
    Hora horaInicio;
    Hora horaFin;   ///
    int sala; /// ni puta idea, pero una sala no puede tener dos peliculas o mas a la misma hora el mismo dia. // hecho
    int contAsientosDisponibles; /// se auto ponen 100 y se le iran restando con cada venta de entrada. // (la venta deberia meter mano aca)
    bool activo; /// hacer funcion que revise si la pelicula sigue vigente sino darla de baja o dar baja manualmente.
**/


void Funcion::mostrarFuncion(Funcion *f) /// 13/7/20
{

    cout << "ID función: " <<  f->idFuncion << endl;
    cout << "Titulo de la película: "<<devolverTitulo(f->idPelicula)<<endl;
    cout << "Tipo de película: " << devolverTipo(f->tipoDePelicula)<<endl;          //f->tipoDePelicula << endl;
    cout << "Codigo de la Película: " << f->idPelicula << endl;
    cout << "Fecha de esta Funcion: " << f->getFecha().getDia() << "/" << f->getFecha().getMes()<< "/" << f->getFecha().getAnio() << endl; /// muestra basura.
    cout << "Hora de inicio: "; /// PARCHASO PARA MOSTRAR BIEN LA HORA 8/7/2020
    if((f->getHoraInicio().getHora() <= 9) && (f->getHoraInicio().getHora() >=00) )
    {
        cout << "0" << f->getHoraInicio().getHora();
    }else{cout << f->getHoraInicio().getHora();}
    if((f->getHoraInicio().getMinutos()<= 9) && (f->getHoraInicio().getMinutos() >= 0) )
    {
        cout << ":0" << f->getHoraInicio().getMinutos() << endl;
    }else{cout << ":" << f->getHoraInicio().getMinutos() << endl;}

    cout << "Hora de fin: ";
    if( (f->getHoraFin().getHora()<= 9) && (f->getHoraFin().getHora()>=0) )
        {
            cout << "0" << f->getHoraFin().getHora();
        }else{cout << f->getHoraFin().getHora();}
    if((f->getHoraFin().getMinutos() <= 9) && (f->getHoraFin().getMinutos() >= 0))
    {
        cout << ":0" << f->getHoraFin().getMinutos() << endl;
    }else{cout<< ":" << f->getHoraFin().getMinutos() << endl;}
    cout << "Número de sala: " << f->sala << endl;
    cout << "Cantidad de asientos disponibles: " << contAsientosDisponibles << endl;
    if(f->getAsientosDisponibles()>0)
    {
        setColor(LIGHTGREEN);
        msj_ok("---Disponible---");

    }else
    {
        setColor(LIGHTRED);
        msj_error("---No Disponible---");
                                        //Estaba como dada de baja, pero no disponible queda mejor si lo vemos del lado cliente
    }

}

bool Funcion::cargarFuncion() ///subir al ultimo q subio cris. 13/7/2020
{
    /// [ID FUNCION]***********************************************************
    cout << "ID de la Funcion: ";
    int id=cantDFunciones();
    if(id==0)
    {
        idFuncion=id+1;
    }else if(id>0)
    {
        idFuncion=id+1;
    }else{cout << "Error inesperado. "<< endl; anykey(">#Enter para cotinuar..."); return false;}
    cout << id+1 << endl;

    cout << "Ingrese el ID de Pelicula: ";
     idPelicula = validarIngresoEntero();
     cin.ignore();
     if(!buscarPeliculaF(idPelicula)){
        cout << endl;
        msj_error("ID Ingresado inválido");
        anykey();
        return false;
     }
     cout<<endl<<"Título de la película: ";
     setColor(LIGHTCYAN);
     cout<<devolverTitulo(idPelicula);
     setColor(WHITE);
    if(!fechaOk(idPelicula)){
        cout << endl;
        msj_error("---La película no está disponible, y por ende, no puede asociarse a la función---");
        anykey();
        cout<<endl;
        return false;
    }
     cin.ignore();
    if(comparandoID(idPelicula)<0) /// retorna la posicion de el archivo.
    {   cls();
        cout << "El ID ingresado no existe." << endl;
        cout << endl;
        anykey(">#Enter para continuar...");
        return false;
    }
    /// [TIPO]*****************************************************************
    cout << "TIPO de Pelicula: ";
    traigoGetTipoPelis(comparandoID(idPelicula),this);
    cout << devolverTipo(tipoDePelicula)<< endl;
    /// [HORA INICIO]**********************************************************
    cout << "Ingrese el horario que inicia la funcion: ";  /// la pelicula tiene el tiempo marcado en minutos.
    int hi,mi;/// 7/7/20
    if(horaInicio.cargarHora())
    {
        hi=horaInicio.getHora();/// 7/7/20
        mi=horaFin.getMinutos();/// 7/7/20
    }else
    {   cls();
        cout << "La carga de la hora de inicio fallo. " << endl;
        cout << endl;
        anykey("Presione una tecla para continuar");
        return false;
    }
    if(hi>23 || mi > 59)
    {   cls();
        cout <<  "La hora no puede ser mayor a 23:59 ." << endl;
        cout << endl;
        anykey(">#Enter para continuar");
        return false;
    }
    if( hi<0 || mi<0)
    {   cls();
        cout << "La hora no puede ser negativa. Intente con una hora válida." << endl; /// creo q no se muestra por que validarHora(); la deniega
        cout << endl;
        anykey(">#Enter para continuar");
        return false;
    }
    /// [HORA DE FIN]***********************************************************
    cout << "Hora en la que finaliza la Funcion: ";/// tomamos la duracion de la pelicula, y se la sumamos a la hora de unicio. y le sumaos 30mnts.
    int h,m;
    h=converMinAH(idPelicula);/// 7/7/20
    m=converMinAM(idPelicula);/// 7/7/20
    if(m>=0 && h>0)/// 7/7/20
    {
        if((m+30)>59){/// 7/7/20
            h++;
            m=(m+30)-59;/// 7/7/20
        }else{m=(m+30);}/// 7/7/20 // los 30mnts se agregan si o si.
        h=getHoraInicio().getHora()+h;/// 7/7/20
        m=getHoraInicio().getMinutos()+m;/// 7/7/20
        if(m>59){h++; m=m-59;}
        if(h>=24){h=h-24;}

        horaFin.setHora(h);/// 7/7/20
        horaFin.setMinutos(m);/// 7/7/20
    }
    if( ( h <= 9 ) && ( h >=00 ) ) /// parchazo para mostrar "0" antes de un numero menor o igual a 9 en la hora
    {
        cout << "0" << h;
    }else{cout << h;}
    if( ( m <= 9) && ( m >= 0) )
    {
        cout << ":0" << m << endl;
    }else{cout << ":" << m << endl;}

    /// [FECHA]***************************************************************
    Fecha aux;
    if(traigoGetFechaPelicula(&aux, comparandoID(idPelicula))) /// 10/7/2020
    {
        cout << "Fecha de estreno: " << aux.getDia() << "/" << fecha.getMes() << "/" << fecha.getAnio() << endl; /// parace que lo tomo bien a la carga de la fecha viniendo de la pelicula.
    }else{return false;}

    cout << "Fecha de la funcion: ";
    if(!fecha.cargarFecha())
    {
        cout << "error al cargar la fecha..." << endl;
        anykey(">#Enter para continuar retornando al menu anterior...");
        return false;
    }
    if(!cargaFechaEnFuncionOk(this->getFecha(),aux))
    {
        cls();
        cout << "La fecha no puede ser menor a la fecha de estreno." << endl;
        anykey("Enter para continuar...");
        cout<<endl;
        return false;
    }

    /// [SALA]****************************************************************
    cout << "Ingrese el numero de sala: ";
    sala = validarIngresoEntero();
    cin.ignore();
    if(!checkSala(this))/// 14/7/20
    {
        return false;
    }
    contAsientosDisponibles=100;
    cout << "Asientos disponibles: " << contAsientosDisponibles << endl;
    cout<<endl<<endl;

    return true;

}



  bool Funcion::grabarEnDisco(Funcion obj){
  FILE *p;
  p = fopen(PATH_FUNCION,"ab");
    if(p == NULL){
        cout << endl;
        msj_error("Error con la apertura del archivo.");
        anykey();
        fclose(p);
        return false;
    }
    bool grabo = fwrite(&obj, sizeof (Funcion), 1, p);
    fclose(p);
    anykey();
    return grabo;
  }


  bool Funcion::grabarEnDisco(Funcion obj, int numFunc){
  FILE *p;
  int pos=numFunc-1;
  p = fopen(PATH_FUNCION,"rb+");
    if(p == NULL){
        cout << endl;
        msj_error("Error con la apertura del archivo.");
        anykey();
        fclose(p);
        return false;
    }
    fseek(p, sizeof(Funcion)*pos, 0);
    bool grabo = fwrite(&obj, sizeof (Funcion), 1, p);
    fclose(p);
//    msj_ok("Función guardada correctamente. "); //Comentada porque no corresponde que aparezca en la cargarVemta, Naza 07/07
    return grabo;
  }

void Funcion::leerDeDisco()
{
    FILE *p;
    p=fopen(PATH_FUNCION,"rb");
    if(p==NULL)
    {
        msj_error("Error. no se encontró el archivo.");
        anykey();
        fclose(p);
    }

    while(fread(this,sizeof *this,1,p))
    {
        mostrarFuncion(this);
    }
}
/// set ///
void Funcion::setFecha(Fecha fec)
{
    fecha=fec;
}

    void Funcion::setTipoDePelicula(int tipo)
    {
        if(tipo>0 && tipo<4)
            {
                tipoDePelicula = tipo;
            }else
            {
                setColor(RED);
                msj_error("Error, el tipo de película solo puede ser 1- XD , 2- 2D , 3- 3D.");
                anykey();
                setColor(WHITE);

            }
    }
    void Funcion::setIDfuncion(int idFuncion)
    {
        if(idFuncion>0)
        {
                this->idFuncion = idFuncion;
        }else
        {
            msj_error("El ID de función no puede ser un número negativo. ");
            anykey();
        }

    }

    void Funcion::setCodigoPelicula(int cod)
    {
        if(cod>0)
        {
            idPelicula=cod;
        }else
        {
            msj_error("El código de película no puede ser negativo.");
        }

    }
    void Funcion::setHoraInicio(Hora horaInicio)
    {
        horaInicio.cargarHora();
        this->horaInicio=horaInicio;
    }
    void Funcion::setHoraFin(Hora horaFin)
    {
        horaFin.cargarHora();
        this->horaFin=horaFin;
    }
    void Funcion::setSala(int sala)
    {
        this->sala=sala;
    }

   bool Funcion::leerDeDisco(int pos){
   FILE *p = fopen(PATH_FUNCION, "rb");
   if(p == NULL){
      msj_error("Error en la apertura del archivo. ");
      anykey();
      fclose(p);
      return false;
   }
   fseek(p, sizeof *this * pos, 0);
   bool leyo = fread(this, sizeof *this, 1, p);
   fclose(p);
   return leyo;
  }

  void Funcion::setAsientosDisponibles(int cantEntradas){
    contAsientosDisponibles-=cantEntradas;
  }


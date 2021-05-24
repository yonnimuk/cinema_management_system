#include <iostream>
using namespace std;
#include "rlutil.h"
using namespace rlutil;
#include "Fecha.h"
#include "Funcion.h"
#include "Cliente.h"
#include "Venta.h"
#include "funcionesGenerales.h"
#include "Pelicula.h"
#include "Entrada.h"
#include "Hora.h"
/** ********************************************************************************************************* **/
/// tenemos la baja automatica de funciones. falta la baja automatica de las peliculas y la baja manual de ambas.
/// falta la alta de las peliculas. que debera revisar si ya se estrenan y de ser asi darles true en el activo. sino false.

bool cargaFechaEnFuncionOk(Fecha funcion, Fecha peli)
{
    if(funcion < peli)
    {
        return false;
    }
    return true;
}

void modificarFechasPeliculas()
{   cls();
    int cantPelis = contarPeliculas();
    int id;
    cout << "Ingrese el ID de la película: ";
    id = validarIngresoEntero();
    cin.ignore();
    if(id>cantPelis||id<=0){
      cout << endl;
      msj_error("ID inválido, intente nuevamente con uno válido");
      cout << endl;
      anykey("Presione cualquier tecla para continuar. . .");
      return;
    }
    cout<<endl<<"Título de la película: "<<devolverTitulo(id);
    cin.ignore();
    if(cambiarFechaEstrenoPeliculaYFechaVencimiento(id))
    {
        cout<<endl;
        msj_ok("---FECHAS MODIFICADAS---");
        cout << endl;
        anykey("Enter para continuar...");

    }else
    {
        cout<<endl;
        msj_error("---ERROR EN LA MODIFICACIÓN---");
        cout << endl;
        anykey("Enter para continuar...");
    }
}

bool fechaOk(int idpelicula)
{
    Pelicula obj;
    Fecha aux;
    obj.leerDeDisco(idpelicula-1);
    if( aux >= obj.getFechaEstreno()  &&  aux <= obj.getFechaVencimiento() )
    {
        return true;
    }
    return false;
}

bool cambiarFechaEstrenoPeliculaYFechaVencimiento(int idPelicula) /// agrege esto. atte: yonni 11/7
{

    int pos=idPelicula-1;
    Fecha fechaEst, fechaVenc;
    Pelicula obj;
    if(obj.leerDeDisco(pos))
    {
        cout << endl;
        cout << "Ingrese la nueva fecha de estreno: " << endl;
        if(!fechaEst.cargarFecha()){
        cls();
        msj_error("Por favor, ingrese fechas válidas, de lo contrario, no podrá modificar las mismas.");
        cout << endl;
        return false;
  }
        obj.setFechaEstreno(fechaEst);
        cout << "Favor de ingresar la nueva fecha de vencimiento: " << endl;
        if(!fechaVenc.cargarFecha()){
        cls();
        msj_error("Por favor, ingrese fechas válidas, de lo contrario, no podrá modificar las mismas.");
        cout << endl;
        return false;
  }
        if(fechaEst>=fechaVenc){
            cout << endl;
            msj_error("La fecha de estreno no puede ser posterior o igual a la de vencimiento.");
            return false;
        }
        obj.setFechaVencimiento(fechaVenc);
        cout << "----------------------------------" << endl;
        if(obj.grabarEnDisco(pos))
        {

         return true;
        }
        anykey();

    }

    return false;
}

/// agrege esto. atte: yonni 11/7
bool traigoGetFechaPelicula(Fecha *objf, int pos)/// toma la fecha de la pelicula marcada y la aplica a la fecha de estreno de la funcion.
{
    Pelicula objp;
    FILE*p;
    p=fopen("datos/peliculas.dat","rb");
    if(p==NULL)
    {
        fclose(p);
        msj_error("no se encontró el archivo en traigoGetpelis. ");
        anykey();
        return false;
    }
    fseek(p,sizeof(Pelicula)*pos,0);
    if(fread(&objp,sizeof(Pelicula),1,p))
    {
        objf->setFecha(objp.getFechaEstreno());
        fclose(p);
        return true;
    }else
    {
        msj_error("No se encontró coincidencia.");
        fclose(p);
        return false;
    }
    fclose(p);
    return false;
}
/////////////////////////////////////////////////////////////////////////////////////////

int converMinAM(int pos)/// 7/7/20
{
    int posi=pos-1; /// esto es por que recibe el id y no la posicion original.(cambiarlo?)
    Pelicula objp;
    FILE*p;
    p=fopen("datos/peliculas.dat","rb");
    if(p==NULL)
    {
        fclose(p);
        cout <<"no se encontró el archivo en traigoGetpelis. " << endl;
        anykey();
        return 0;
    }
    fseek(p,sizeof(Pelicula)*posi,0);
    if(fread(&objp,sizeof(Pelicula),1,p))
    {
        int minut=objp.getMinutosPelicula();
        fclose(p);
        float resto=minut%60;
        minut= (int)resto; /// casteo.
        return minut;
    }else
    {
        cout << "no se encontraron los minutos." << endl;
        fclose(p);
        return 0;
    }

}

int converMinAH(int pos) /// 7/7/20
{
    int posi=pos-1;/// esto es por que recibe el id y no la posicion original.(cambiarlo?)
    Pelicula objp;
    FILE*p;
    p=fopen("datos/peliculas.dat","rb");
    if(p==NULL)
    {
        fclose(p);
        cout <<"no se encontró el archivo en traigoGetpelis. " << endl;
        anykey();
        return 0;
    }
    fseek(p,sizeof(Pelicula)*posi,0);
    if(fread(&objp,sizeof(Pelicula),1,p))
    {
        int minut=objp.getMinutosPelicula();
        fclose(p);
        minut=minut/60;
        return minut;
    }else
    {
        cout << "no se encontraron los minutos." << endl;
        fclose(p);
        return 0;
    }

}

bool checkSala(Funcion *f)/// 14/7/20
{
    Funcion obj;
    FILE*p;
    p=fopen("datos/funcion.dat","rb");
    if(p==NULL)
    {
        int opc;
        cout << " Es la primera función que carga?...1 para sí. 2 para no " << endl;
        cin>>opc;
        cin.ignore();
        if(opc == 1)
        {
            return true;
        }else if(opc == 2)
        {
            cls();
            msj_error(" :( ");
            cout<<endl;
            msj_error("Error al ubicar el archivo...");
            cout<<endl;
            anykey(">#Enter para continuar...");
            return false;
        }else
        {
            cls();
            msj_error(" :( ");
            cout<<endl;
            msj_error("opcion erronea... se cancelara la carga para evitar problemas...");
            cout<<endl;
            anykey(">#Enter para continuar...");
            return false;
        }
    }
    int mntInObj,mntFinObj,fmntIni,fmntFin;
    while(fread(&obj,sizeof(Funcion),1,p)) /// un dia tiene 1440 minutos.
    {
        if( (obj.getSala()==f->getSala() ) && ( obj.getFecha() == f->getFecha() ) )
        {
            mntInObj=deHoraAmntI(&obj); /// minutos de inicio de la funcion ya cargada
            mntFinObj=deHoraAmntF(&obj); /// minutos de finalizacion de la funcion ya cargada
            fmntIni=deHoraAmntI(f); /// minutos de inicio de la funcion a cargada
            fmntFin=deHoraAmntF(f); /// minutos de finalizacion de la funcion a cargada
            if( ( fmntIni >= mntInObj ) && ( fmntIni <= mntFinObj ) )
            {
                cls();
                msj_error(" :( ");
                cout<<endl;
                msj_error("La sala en ese momento se encuentra ocupada por otra función. ");
                anykey("Enter para continuar...");
                fclose(p);
                return false;
            }else if( ( fmntFin > mntInObj ) && ( fmntFin <= mntFinObj ) )
            {
                cls();
                msj_error(" :( ");
                cout<<endl;
                msj_error("La sala en ese momento se encuentra ocupada por otra función. ");
                cout<<endl;
                anykey("Enter para continuar...");
                fclose(p);
                return false;
            }

        }
    }
    fclose(p);
    return true;
}
/// de hora a minutos: (h*60)+mnts = minutos
/// de minutos a hora:          miutos/60 = hs,nd
/// "nd" son los numeros dedimaes             \
/// ó resto de la division. solo               > hs : mnts
/// los multiplicamos por 60 y                /
///tendremos el valor que nos falta. nd*60 = mnts


int deHoraAmntI(Funcion *obj)/// 14/7/20 /// (fx)=(h*60)+mnts
{
    int mnts;
    mnts = (obj->getHoraInicio().getHora()*60) + obj->getHoraInicio().getMinutos();
    return mnts;
}

int deHoraAmntF(Funcion *obj)/// 14/7/20 /// (fx)=(h*60)+mnts
{
    int mnts;
    mnts = (obj->getHoraFin().getHora()*60) + obj->getHoraFin().getMinutos();
    return mnts;
}

int cantDFunciones() /// retorna la cantidad total de funcione que hay en base a sus posiciones.
{
    Funcion obj;
    FILE*p;
    p=fopen("datos/funcion.dat","rb");
    if(p==NULL)
    {
        fclose(p);
        return 0;
    }
    int pos=0;
    while(fread(&obj,sizeof(Funcion),1,p))
    {
        pos++;
    }
    return pos;
}

void traigoGetTipoPelis(int pos,Funcion *objf)
{
    Pelicula objp;
    FILE*p;
    p=fopen("datos/peliculas.dat","rb");
    if(p==NULL)
    {
        fclose(p);
        msj_error("no se encontró el archivo en traigoGetpelis. ");
        anykey();
        return;
    }
    fseek(p,sizeof(Pelicula)*pos,0);
    if(fread(&objp,sizeof(Pelicula),1,p))
    {
        objf->setTipoDePelicula(objp.getTipoPelicula());
        fclose(p);
        return;
    }else
    {
        msj_error("No se encontró coincidencia.");
        fclose(p);
        return;
    }

}

int comparandoID(int idPeli)
{
    Pelicula objp;
    FILE*p;
    p=fopen("datos/peliculas.dat","rb");
    if(p==NULL)
    {
        fclose(p);
        return -1;
    }
    int pos=0;
    while(fread(&objp,sizeof(Pelicula),1,p))
    {
        if(objp.getIdPelicula() == idPeli)
        {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -2;
}

int buscarTipoPelicula(int idFuncion){
    Funcion obj;
    FILE *p;
    int pos=idFuncion-1; //idFuncion-1 no me sirve, porque Jony genera el id automática de una forma medio rara
    p=fopen("datos/funcion.dat", "rb");
    if(p==NULL)return 0;
    fseek(p,sizeof(Funcion)*pos,0); /// este fseek no estaba. edito yonni 7/7/2019 03:15 am
    fread(&obj, sizeof(Funcion), 1, p); /// aca habia un "sizeof(Funcion)*idFuncion" 7/7/2019 03:15 am
    int tipo=obj.getTipoDePelicula();
    fclose(p);
    return tipo;
}
/** ********************************************************************************************************* **/
float precioEntrada(int tipo){
int t=tipo-1;
Entrada obj;
FILE *p;
p=fopen("datos/entradas.dat", "rb");
if(p==NULL)return 0;
fseek(p, sizeof(Entrada)*t,0);
fread(&obj, sizeof(Entrada), 1, p);
float precio;
precio=obj.getPrecio();
fclose(p);
return precio;
}

int buscarCliente(long dniCli){
  Cliente obj;
  int posicion = 0;
    while(obj.leerDeDisco(posicion++)){
      if(obj.getDniCliente() == dniCli){
        return posicion;
      }
    }
    return -1;
  }

  bool validarFecha(int dia, int mes, int anio){
  Fecha actual;
  bool fechaValida = false;
  if(mes>0 && mes<13){
    switch(mes){
    case 1:
    case 3:  /// Enero, marzo, mayo, julio, agosto, octubre y diciembre (meses de 31 dias)
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
      if(dia>0 && dia<32 && anio>1895 && anio <= actual.getAnio()+1){
      fechaValida = true;
    }
    break;

    case 4:
    case 6: ///Abril, junio, septiembre y noviembre (meses de 30 días)
    case 9:
    case 11:
        if(dia>0 && dia<31 && anio>1895 && anio <= actual.getAnio()+1){
            fechaValida = true;
        }
    break;

    case 2:      ///Febrero, caso particular, donde si es bisiesto, tendrá 29 días
        if((anio%4 == 0) && (anio%100 != 0) || (anio%400 == 0)){
          if(dia>0 && dia<30 && anio>1895 && anio <= actual.getAnio()+1){
            fechaValida = true;
          }
    }
    else {
        if(dia>0 && dia<29 && anio>1895 && anio <= actual.getAnio()+1){ ///Si no es bisiesto, tendrá 28
            fechaValida = true;
        }
    }
    break;
  }
}
  return fechaValida;
}

bool validarHora(int hora, int minutos){
  bool horaValida = false;
  if(hora>=00 && hora<=23){
      if(minutos>=00 && minutos<=59){
      horaValida = true;
    }
  }
  return horaValida;
}

bool ingresarNuevoCliente(){
cls();                //Por el false no puse nada, ya que tanto cargar, como grabar, tienen por el falso un msj indicando el problema
Cliente obj;                 //Cris 20/06
if(obj.cargarCliente()){
    if(obj.grabarEnDisco()){
        msj_ok("---Cliente añadido correctamente---");
        anykey();
        return true;
    }
  }
  else{
    cout<<endl<<endl;
    msj_error("---Error en el registro del cliente, inténtelo de nuevo---");
    anykey("---Presione una tecla para volver al menú principal---");
    return false;

  }
}

bool ingresarNuevoCliente(long DNI){
Cliente obj;
if(obj.cargarCliente(DNI)){
    if(obj.grabarEnDisco()){
        cout << "---Cliente añadido correctamente---" << endl;
        anykey();
        return false;
    }
  }
}


void cargarPrecios(){
cls();
Entrada obj;
int num;
cout<<"Ingrese el tipo de precio a modificar: "<<endl;
cout<<"          (1=XD, 2=2D, 3=3D)"<<endl;
num = validarIngresoEntero();
cin.ignore();
while(num!=1 && num!=2 && num!=3){
cout << endl;
msj_error("Tipo ingresado inválido. ");
cout << endl;
cout<<"Ingrese el tipo de precio a modificar: "<<endl;
cout<<"          (1=XD, 2=2D, 3=3D)"<<endl;
num = validarIngresoEntero();
cin.ignore();
}
if(!obj.setPrecio()){
msj_error("---Error en la carga---");
anykey();
return;
}

if(obj.grabarPrecio(num)){
msj_ok("---Precio cargado correctamente---");
anykey();
return;
  }
}

void consultarPrecios(){
cls();
float precioXD, precio2D, precio3D;
gotoxy(8, 2);
setColor(LIGHTMAGENTA);
cout<<"---Precios de las entradas---";
precioXD=precioEntrada(1);
precio2D=precioEntrada(2);
precio3D=precioEntrada(3);
gotoxy(13, 4);
cout<<"Películas 2D: ";
setColor(LIGHTCYAN);
cout<<"$"<<precio2D;
setColor(LIGHTMAGENTA);
gotoxy(13, 6);
cout<<"Películas 3D: ";
setColor(LIGHTCYAN);
cout<<"$"<<precio3D;
setColor(LIGHTMAGENTA);
gotoxy(13, 8);
cout<<"Películas XD: ";
setColor(LIGHTCYAN);
cout<<"$"<<precioXD;
anykey();
setColor(WHITE);
}

int contarClientes(){
    int cantidadClientes;
    FILE *p = fopen("datos/clientes.dat","rb");
      if(p == NULL){
        msj_error("Error en la apertura del archivo. ");
        cin.get();
        return -1;
      }
      fseek(p, SEEK_SET, SEEK_END);
      cantidadClientes = ftell(p)/sizeof (Cliente);
      return cantidadClientes;
  }

bool crearVectorCliente(){
    Cliente *vec;
    int cantidadClientes = contarClientes();
    if(cantidadClientes == 0){
        msj_error("No hay clientes grabados en el archivo. ");
        cin.get();
        return false;
    }
    vec = new Cliente[cantidadClientes];
      if(vec == NULL){
        msj_error("No se pudo asignar memoria para el vector dinámico. ");
        cin.get();
        delete vec;
        return false;
      }
      cargarVectorCliente(vec, cantidadClientes);
      mostrarVectorCliente(vec, cantidadClientes);
      cin.get();

      delete vec;
      return true;
  }

void cargarVectorCliente(Cliente * vec, int cantidad){
  if(cantidad == 0){
  msj_error("No se pudo cargar el vector dinámico, ya que no hay clientes grabados en el archivo. ");
  cin.get();
  return;
  }
  for(int i = 0; i<cantidad; i++){
    vec[i].leerDeDisco(i);
 }

    return;
}

   void ordenarVClienteXApellido(Cliente * vec, int cantidad){
     if(cantidad == 0){
       msj_error("No hay clientes en el archivo. ");
       return;
     }
     for(int i = 0; i<cantidad-1; i++){
       int posMenor = i;

       for(int j = i+1; j<cantidad; j++){
          if(strcasecmp(vec[j].getApellidoCliente(), vec[posMenor].getApellidoCliente()) < 0){
            posMenor = j;
          }
       }
       Cliente iAux;
       iAux = vec[i];
       vec[i] = vec[posMenor];
       vec[posMenor] = iAux;
     }
   }

 void ordenarVClienteXFechaNac(Cliente * vec, int cantidad){
   if(cantidad == 0){
     msj_error("No hay clientes en el archivo. ");
     cin.get();
     return;
   }
   for(int i = 0; i<cantidad-1; i++){
     int posMayor = i;
   for(int j = i+1; j<cantidad; j++){
     if(vec[j].getfechaNac()>vec[posMayor].getfechaNac()){
       posMayor = j;
       }
    }
      Cliente iAux;
      iAux = vec[posMayor];
      vec[posMayor] = vec[i];
      vec[i] = iAux;
   }
}

  void mostrarVectorCliente(Cliente * vec, int cantidad){
    cls();
    cout<<"Listado clientes: "<<endl<<endl;
    for(int i = 0; i<cantidad; i++){
      vec[i].mostrarCliente();
      cout<<endl;
    }

  }

bool buscarPeliculaF(int id){
  Pelicula reg;
  int pos = 0;
  while(reg.leerDeDisco(pos++)){
    if(reg.getIdPelicula()==id){
      return true;
    }
  }
  return false;
}

int buscarPelicula(int id){  //hablar sobre esto, puede hacerse sobre el ID, pero funciona
  Pelicula reg;
  int pos = 0;
  while(reg.leerDeDisco(pos++)){
    if(reg.getIdPelicula()==id){
      return pos;
    }
  }
  return -1;
}

int buscarPelicula(char *titulo){  //hablar sobre esto, puede hacerse sobre el ID, pero funciona
  Pelicula reg;
  int pos = 0;
  while(reg.leerDeDisco(pos++)){
    if(strcasecmp(reg.getTituloPelicula(), titulo) == 0){
      return pos;
    }
  }
  return -1;
}

int validarIngresoEntero()
{
    int op;
    while(!(cin>>op))
    {   setColor(LIGHTRED);
        cout << endl << "- ERROR, SE ESPERA UN VALOR NUMERICO, INTENTE NUEVAMENTE CON UNO QUE CORRESPONDA: ";
        cin.clear();
        cin.ignore(123,'\n');
        setColor(WHITE);
     }
    return op;
}

float validarIngresoFlotante()
{
    float op;
    while(!(cin>>op))
    {   setColor(LIGHTRED);
        cout << endl << "- ERROR, SE ESPERA UN VALOR NUMERICO, INTENTE NUEVAMENTE CON UNO QUE CORRESPONDA: ";
        cin.clear();
        cin.ignore(123,'\n'); // practicamente lo mismo que su contraparte int, solo que espera float
        setColor(WHITE);
     }
    return op;
}

void funDisponibles() /// debe revisar si la funcion no esta dada de baja.
{
    cls();
    int cont=0;
    Funcion f;
    Fecha aux;
    Hora ho;
    FILE *p;
    p=fopen("datos/funcion.dat","rb");
    if(p==NULL)
    {
        msj_error("---Error, no se encontró el archivo---");
        anykey();
        fclose(p);
    }

    while(fread(&f,sizeof(Funcion),1,p))
    {
        if(fechaOk(f.getCodigoPelicula())){
        if((f.getFecha()>aux)||(f.getFecha()>=aux && f.getHoraInicio()>ho)){
        f.mostrarFuncion(&f);
        cout<<endl;
        cont++;
    }
    }
}
if(cont==0){
    msj_error("---No hay funciones disponibles para la fecha actual ni posteriores---");
    anykey();
}
else{
    anykey("Presione cualquier tecla para retornar. . .");
  }
}

void funDisponiblesHoy() /// debe revisar si la funcion no esta dada de baja.
{
    cls();
    int cont=0;
    Funcion f;
    Fecha aux;
    Hora ho;
    FILE *p;
    p=fopen("datos/funcion.dat","rb");
    if(p==NULL)
    {
        msj_error("---Error, no se encontró el archivo---");
        anykey();
        fclose(p);
    }

    while(fread(&f,sizeof(Funcion),1,p))
    {
        if(fechaOk(f.getCodigoPelicula())){
        if((f.getFecha()>aux)||(f.getFecha()>=aux && f.getHoraInicio()>ho)){
        if(f.getFecha()==aux){
        f.mostrarFuncion(&f);
        cout<<endl;
        cont++;
    }
    }}
}
if(cont==0){
    msj_error("---No hay funciones disponibles para la fecha actual ni posteriores---");
    anykey();
}
else{
    anykey("Presione cualquier tecla para retornar. . .");
  }
}


int buscarFuncion(int IDFuncion){
   Funcion obj;
  int posicion = 0;
    while(obj.leerDeDisco(posicion)){
      if(obj.getIDfuncion() == IDFuncion){
        return posicion;
      }
      posicion++;
    }
    return -1;
  }

bool aplicarDescuento(Fecha obj){

  bool descuento = false;
                             //Aplicamos descuento los ultimos dias del mes, donde la gente anda mas corta de dinero
  switch(obj.getDia()){
  case 28: descuento = true;
  break;
  case 29: descuento = true;
  break;
  case 30: descuento = true;
  break;
  case 31: descuento = true;
  break;
  }
  return descuento;
}

int consultarAsientosDisponibles(int numFunc){
Funcion obj;
int asDisp;
obj.leerDeDisco(numFunc-1);
asDisp=obj.getAsientosDisponibles();
return asDisp;
}

void actualizarAsientosDisp(int cantEntr, int numFunc){
Funcion aux;
aux.leerDeDisco(numFunc-1);
aux.setAsientosDisponibles(cantEntr);
aux.grabarEnDisco(aux, numFunc);
}



void ingresarFuncion(){
cls();
Funcion objf;
if(objf.cargarFuncion()){
    if(objf.grabarEnDisco(objf)){
    msj_ok("---Función guardada---");
    anykey("---Presione una tecla para continuar---");
    return;
    }
}
    else{
    cls();
    msj_error(" :( ");
    cout << endl;
    msj_error("---Error, no se pudo guardar la función---" );
    cout<<endl<<endl;
    anykey("---Pulse cualquier tecla para volver al menú anterior---");
    return;
    }
}

void listarPeliculas(){
cls();
setColor(LIGHTMAGENTA);
cout << "Listado de todas las películas cargadas en sistema: " << endl;
cout << endl;
setColor(WHITE);
Pelicula obj;
obj.mostrarTodasLasPeliculas();
}

int generarIDPelicula() //ID automático, solucionado por Cris el 2/7
{
    FILE *p = fopen("datos/peliculas.dat","ab");
    fseek(p,SEEK_SET,SEEK_END);
    int ID=((ftell(p)/sizeof(Pelicula))+1);
    fclose(p);
    return ID;
}


bool listadoClientesxApellido(){
    Cliente *vec;
    int cantidadClientes = contarClientes();
    if(cantidadClientes == 0){
        msj_error("No hay clientes grabados en el archivo. ");
        cin.get();
        return false;
    }
    vec = new Cliente[cantidadClientes];
      if(vec == NULL){
        msj_error("No se pudo asignar memoria para el vector dinámico. ");
        cin.get();
        delete vec;
        return false;
      }
      cargarVectorCliente(vec, cantidadClientes);
      ordenarVClienteXApellido(vec, cantidadClientes);
      mostrarVectorCliente(vec, cantidadClientes);
      cout << endl;
      anykey("Presione cualquier tecla para retornar. . .");

      delete vec;
      return true;
  }

bool listadoClientesxFechaNac(){
    Cliente *vec;
    int cantidadClientes = contarClientes();
    if(cantidadClientes == 0){
        msj_error("No hay clientes grabados en el archivo. ");
        cin.get();
        return false;
    }
    vec = new Cliente[cantidadClientes];
      if(vec == NULL){
        msj_error("No se pudo asignar memoria para el vector dinámico. ");
        cin.get();
        delete vec;
        return false;
      }
      cargarVectorCliente(vec, cantidadClientes);
      ordenarVClienteXFechaNac(vec, cantidadClientes);
      mostrarVectorCliente(vec, cantidadClientes);
      cin.get();

      delete vec;
      return true;
  }

  bool crearVectorPelicula(){
    Pelicula *vec;
    int cantidadPeliculas = contarPeliculas();
    if(cantidadPeliculas == 0){
        msj_error("No hay películas grabadas en el archivo. ");
        cin.get();
        return false;
    }
    vec = new Pelicula[cantidadPeliculas];
      if(vec == NULL){
        msj_error("No se pudo asignar memoria para el vector dinámico. ");
        cin.get();
        delete vec;
        return false;
      }
      cargarVectorPelicula(vec, cantidadPeliculas);
      mostrarVectorPelicula(vec, cantidadPeliculas);
      cin.get();

      delete vec;
      return true;
  }

  int contarPeliculas(){
    int cantidadPeliculas;
    FILE *p = fopen("datos/peliculas.dat","rb");
      if(p == NULL){
        msj_error("Error en la apertura del archivo. ");
        cin.get();
        return -1;
      }
      fseek(p, SEEK_SET, SEEK_END);
      cantidadPeliculas = ftell(p)/sizeof (Pelicula);
      return cantidadPeliculas;
  }

  void cargarVectorPelicula(Pelicula * vec, int cantidad){
  if(cantidad == 0){
  msj_error("No se pudo cargar el vector dinámico, ya que no hay películas grabadas en el archivo. ");
  cin.get();
  return;
  }
  for(int i = 0; i<cantidad; i++){
    vec[i].leerDeDisco(i);
 }
    cout << "Listado de películas: " << endl;
    cin.get();
    return;
}

  void mostrarVectorPelicula(Pelicula * vec, int cantidad){
    for(int i = 0; i<cantidad; i++){
      vec[i].mostrarPelicula();
    }
  }

bool listadoPeliculasxTitulo(){
    Pelicula *vec;
    int cantidadPeliculas = contarPeliculas();
    if(cantidadPeliculas == 0){
        msj_error("No hay películas grabadas en el archivo, por lo que no es posible listarlas. ");
        cin.get();
        return false;
    }
    vec = new Pelicula[cantidadPeliculas];
      if(vec == NULL){
        msj_error("No se pudo asignar memoria para el vector dinámico. ");
        cin.get();
        delete vec;
        return false;
      }
      cargarVectorPelicula(vec, cantidadPeliculas);
      ordenarVPeliculaxTitulo(vec, cantidadPeliculas);
      mostrarVectorPelicula(vec, cantidadPeliculas);
      cin.get();

      delete vec;
      return true;
  }

  void ordenarVPeliculaxTitulo(Pelicula * vec, int cantidad){
     if(cantidad == 0){
       msj_error("No hay películas en el archivo. ");
       cin.get();
       return;
     }
     for(int i = 0; i<cantidad-1; i++){
       int posMenor = i;

       for(int j = i+1; j<cantidad; j++){
          if(strcasecmp(vec[j].getTituloPelicula(), vec[posMenor].getTituloPelicula()) < 0){
            posMenor = j;
          }
       }
       Pelicula iAux;
       iAux = vec[i];
       vec[i] = vec[posMenor];
       vec[posMenor] = iAux;
     }
   }

bool listadoPeliculasxFechaEstreno(){
    Pelicula *vec;
    int cantidadPeliculas = contarPeliculas();
    if(cantidadPeliculas == 0){
        msj_error("No hay películas grabadas en el archivo. ");
        cin.get();
        return false;
    }
    vec = new Pelicula[cantidadPeliculas];
      if(vec == NULL){
        msj_error("No se pudo asignar memoria para el vector dinámico. ");
        cin.get();
        delete vec;
        return false;
      }
      cargarVectorPelicula(vec, cantidadPeliculas);
      ordenarVPeliculaxFechaEst(vec, cantidadPeliculas);
      mostrarVectorPelicula(vec, cantidadPeliculas);
      cin.get();

      delete vec;
      return true;
  }

void ordenarVPeliculaxFechaEst(Pelicula * vec, int cantidad){
   if(cantidad == 0){
     msj_error("No hay películas grabadas en el archivo. ");
     cin.get();
     return;
   }
   for(int i = 0; i<cantidad-1; i++){
     int posMayor = i;
   for(int j = i+1; j<cantidad; j++){
     if(vec[j].getFechaEstreno()>vec[posMayor].getFechaEstreno()){ //El listado es de la mas actual a la mas antigua, si se quiere de la otra forma, intercambiar[j] por [posMayor]
       posMayor = j;
       }
    }
      Pelicula iAux;
      iAux = vec[posMayor];
      vec[posMayor] = vec[i];
      vec[i] = iAux;
   }
}

void msj_error(const char *msj, int x, int y){
  if(x == -1 && y == -1){
    y = trows()-1;
    x = 0;
  }
  gotoxy(x, y);
  setColor(LIGHTRED);
  cout << "> " << msj << endl;
  setColor(WHITE);
}

void msj_ok(const char *msj, int x, int y){
  if(x == -1 && y == -1){
    y = trows()-1;
    x = 0;
  }
  gotoxy(x, y);
  cout << "> " << msj << endl;
  setColor(WHITE);
}


int idFuncionAutomatico(){
int cantFunc;
    FILE *p = fopen("datos/funcion.dat","rb");
      if(p == NULL){
        msj_error("Error en la apertura del archivo. ");
        cin.get();
        return -1;
      }
      fseek(p, SEEK_SET, SEEK_END);
      cantFunc = ftell(p)/sizeof (Funcion);
      return cantFunc+1;
}

string convertirGenero(int genero){
  switch(genero){
  case 1:
      return "Masculino";
    break;
  case 2:
      return "Femenino";
    break;
  case 3:
      return "Otro";
    break;
  }
}

string convertirEstado(bool estado){
  if(estado == true){
    return "Activo";
  }
  else{
    return "Inactivo";
  }
}

string devolverGenero(int genero){
  switch(genero){
  case 1:
      return "Terror";
    break;
  case 2:
      return "Acción";
    break;
  case 3:
      return "Comedia";
    break;
  case 4:
      return "Drama";
    break;
  case 5:
      return "Ciencia ficción";
    break;
  case 6:
      return "Infantil";
    break;
  }
}

string devolverTipo(int tipoPeli){
  switch(tipoPeli){
  case 1:
      return "XD";
    break;
  case 2:
      return "2D";
    break;
  case 3:
      return "3D";
    break;
  }
}

int buscarMes(int mes){
  Venta obj;
  int posicion = 0;
    while(obj.leerDeDisco(posicion++)){
      if(obj.getfechaVenta().getMes() == mes /*&& obj.getEstado() == true*/){
        return posicion;
      }
    }
    return -1;
  }

long validarIngresoDNI(){
    long DNI;
    while(!(cin>>DNI)){
        setColor(LIGHTRED);
        cout << endl << "- ERROR, SE ESPERA UN DNI (VALOR ENTRE 3.000.000 Y 50.000.000), INTENTE NUEVAMENTE CON UNO QUE CORRESPONDA: ";
        cin.clear();
        cin.ignore(123,'\n');
        setColor(WHITE);
     }
    return DNI;
}

int validarIngresoMes(){
    int mes;
    while(!(cin>>mes)){
        setColor(LIGHTRED);
        cout << endl << "- ERROR, SE ESPERA UN MES (VALOR ENTRE 1 Y 12), INTENTE NUEVAMENTE CON UNO QUE CORRESPONDA: ";
        cin.clear();
        cin.ignore(123,'\n');
        setColor(WHITE);
     }
    return mes;
}


void msj_promo(){
cls();
setColor(LIGHTCYAN);
gotoxy(10, 5);
cout<<"¡DISFRUTÁ TODOS LOS FINES DE MES DE UN 30% DE"<<endl;
gotoxy(10, 6);
cout<<"   DESCUENTO EN EL VALOR DE TUS ENTRADAS!"<<endl;
gotoxy(10, 10);
cout<<"*Descuento válido desde el 28 al 31 de cada mes*"<<endl;
anykey();
setColor(WHITE);
}

string devolverTitulo(int codPeli){
Pelicula reg;
int pos=buscarPelicula(codPeli)-1;
FILE *p;
p=fopen("datos/peliculas.dat", "rb");
if(p==NULL){
cout<<"Error al leer"<<endl;
anykey();
return "Error";
}
fseek(p, sizeof(Pelicula)*pos, 0);
fread(&reg, sizeof(Pelicula), 1, p);
return reg.getTituloPelicula();
}

bool CrearBackUpClientes(){

    Cliente obj;

    FILE*COPIAR = fopen("datos/clientes.dat", "rb");
    FILE*ACA = fopen("datos/clientes.bkp", "wb");

    if(COPIAR == NULL || ACA == NULL){
        cout << endl;
        msj_error("No se ha podido realizar el backup de clientes.");
        cin.get();
        return false;
    }

    while(fread(&obj, sizeof(Cliente), 1, COPIAR) == 1){

        fwrite(&obj, sizeof(Cliente), 1, ACA);

    }

    fclose(COPIAR);
    fclose(ACA);

    setColor(LIGHTCYAN);
    msj_ok("Se ha generado exitosamente un backup del archivo de clientes.");
    cout << endl;
    setColor(WHITE);
    anykey("Presione cualquier tecla para retornar. . .");
    return true;

}

bool CrearBackUpPeliculas(){

    Pelicula obj;

    FILE*COPIAR = fopen("datos/peliculas.dat", "rb");
    FILE*ACA = fopen("datos/peliculas.bkp", "wb");

    if(COPIAR == NULL || ACA == NULL){
        cout << endl;
        msj_error("No se ha podido realizar el backup de películas.");
        return false;
    }

    while(fread(&obj, sizeof(Pelicula), 1, COPIAR) == 1){

        fwrite(&obj, sizeof(Pelicula), 1, ACA);

    }

    fclose(COPIAR);
    fclose(ACA);

    setColor(LIGHTCYAN);
    msj_ok("Se ha generado exitosamente un backup del archivo de películas.");
    cout << endl;
    setColor(WHITE);
    anykey("Presione cualquier tecla para retornar. . .");

    return true;

}

bool CrearBackUpVentas(){

    Venta obj;

    FILE*COPIAR = fopen("datos/ventas.dat", "rb");
    FILE*ACA = fopen("datos/ventas.bkp", "wb");

    if(COPIAR == NULL || ACA == NULL){
        cout << endl;
        msj_error("No se ha podido realizar el backup de ventas.");
        return false;
    }

    while(fread(&obj, sizeof(Venta), 1, COPIAR) == 1){

        fwrite(&obj, sizeof(Venta), 1, ACA);

    }

    fclose(COPIAR);
    fclose(ACA);

    setColor(LIGHTCYAN);
    msj_ok("Se ha generado exitosamente un backup del archivo de ventas.");
    cout << endl;
    setColor(WHITE);
    anykey("Presione cualquier tecla para retornar. . .");
    return true;

}

bool CrearBackUpFunciones(){

    Funcion obj;

    FILE*COPIAR = fopen("datos/funcion.dat", "rb");
    FILE*ACA = fopen("datos/funcion.bkp", "wb");

    if(COPIAR == NULL || ACA == NULL){
        cout << endl;
        msj_error("No se ha podido realizar el backup de las funciones.");
        return false;
    }

    while(fread(&obj, sizeof(Funcion), 1, COPIAR) == 1){

        fwrite(&obj, sizeof(Funcion), 1, ACA);

    }

    fclose(COPIAR);
    fclose(ACA);

    setColor(LIGHTCYAN);
    msj_ok("Se ha generado exitosamente un backup del archivo de funciones.");
    cout << endl;
    setColor(WHITE);
    anykey("Presione cualquier tecla para retornar. . .");

    return true;

}

void BackUpTodos(){

  CrearBackUpClientes();
  CrearBackUpPeliculas();
  CrearBackUpVentas();
  CrearBackUpFunciones();

    cls();
    msj_ok("Backup general realizado exitosamente");
    cout << endl;
    anykey("Presione cualquier tecla para continuar. . .");

}

bool RestaurarClientes(){

    Cliente obj;

    FILE*copiar = fopen("datos/clientes.bkp","rb");
    FILE*aca = fopen("datos/clientes.dat","wb");

    if(copiar == NULL || aca == NULL){
        cout << endl;
        msj_error("Se ha producido un problema en la restauración de clientes.");
        return false;
    }

    while(fread(&obj, sizeof(Cliente), 1, copiar) == 1){

        fwrite(&obj, sizeof(Cliente), 1, aca);

    }

    fclose(copiar);
    fclose(aca);

    setColor(LIGHTCYAN);
    msj_ok("Se ha restaurado exitosamente el backup del archivo de clientes.");
    cout << endl;
    setColor(WHITE);
    anykey("Presione cualquier tecla para retornar. . .");

    return true;

}

bool RestaurarPeliculas(){

  Pelicula obj;

  FILE *copiar = fopen("datos/peliculas.bkp", "rb");
  FILE *aca = fopen("datos/peliculas.dat", "wb");

  if(copiar == NULL || aca == NULL){
    cout << endl;
    msj_error("Se ha producido un problema al intentar restaurar las películas. ");
    return false;
  }

  while(fread(&obj, sizeof (Pelicula), 1, copiar) == 1){

    fwrite(&obj, sizeof (Pelicula), 1, aca);
  }

  fclose(copiar);
  fclose(aca);

  setColor(LIGHTCYAN);
  msj_ok("Se ha restaurado exitosamente el backup del archivo de películas.");
  cout << endl;
  setColor(WHITE);
  anykey("Presione cualquier tecla para retornar. . .");

  return true;

}

bool RestaurarVentas(){

  Venta obj;

  FILE *copiar = fopen("datos/ventas.bkp", "rb");
  FILE *aca = fopen("datos/ventas.dat", "wb");

  if(copiar == NULL || aca == NULL){
    cout << endl;
    msj_error("Se ha producido un problema al intentar restaurar las ventas. ");
    return false;
  }

  while(fread(&obj, sizeof (Venta), 1, copiar) == 1){

    fwrite(&obj, sizeof (Venta), 1, aca);
  }

  fclose(copiar);
  fclose(aca);

  setColor(LIGHTCYAN);
  msj_ok("Se ha restaurado exitosamente el backup del archivo de ventas.");
  cout << endl;
  setColor(WHITE);
  anykey("Presione cualquier tecla para retornar. . .");

  return true;

}

bool RestaurarFunciones(){

  Funcion obj;

  FILE *copiar = fopen("datos/funcion.bkp", "rb");
  FILE *aca = fopen("datos/funcion.dat", "wb");

  if(copiar == NULL || aca == NULL){
    cout << endl;
    msj_error("Se ha producido un error al intentar restaurar las funciones. ");
    return false;
  }

  while(fread(&obj, sizeof (Funcion), 1, copiar) == 1){

    fwrite(&obj, sizeof (Funcion), 1, aca);
  }

  fclose(copiar);
  fclose(aca);

  setColor(LIGHTCYAN);
  msj_ok("Se ha restaurado exitosamente el backup del archivo de funciones.");
  cout << endl;
  setColor(WHITE);
  anykey("Presione cualquier tecla para retornar. . .");

  return true;

}

void RestaurarTodos(){

  RestaurarClientes();
  RestaurarPeliculas();
  RestaurarVentas();
  RestaurarFunciones();

  cls();
  msj_ok("Restauración de backups general exitosa. ");
  cout << endl;
  anykey("Presione cualquier tecla para continuar. . .");

}

int validarIngresoAnio(){
    int anio;
    while(!(cin>>anio)){
        setColor(LIGHTRED);
        cout << endl << "- ERROR, SE ESPERA UN VALOR ANUAL, (DESDE EL 2010 HASTA LA FECHA), INTENTE NUEVAMENTE";
        cin.clear();
        cin.ignore(123,'\n');
        setColor(WHITE);
     }
    return anio;
}

bool recaudacionAnual(){
  cls();
  Venta obj;
  float acuRecaudado = 0;
  int anio, pos = 0, cantEnt=0;
  cout << "Ingrese el año sobre el cual quiera calcular la recaudación: " << endl;
  anio = validarIngresoAnio();
  cin.ignore();
  Fecha actual;

  if(anio>actual.getAnio()||anio<2010){
    cout << endl;
    msj_error("Error, el año no puede sobrepasar al actual, ni ser inferior al 2010.");
    cout << endl;
    anykey("Presione cualquier tecla para retornar. . .");
    return false;
  }
  while(obj.leerDeDisco(pos++)){
    if(obj.getfechaVenta().getAnio() == anio){
      acuRecaudado += obj.getMonto();
      cantEnt+=obj.getCantidadEntradas();
    }
  }
    if(acuRecaudado!=0){
    cout << endl << "El monto de recaudación registrado para el año ";
    setColor(LIGHTCYAN);
    cout<<anio;
    setColor(WHITE);
    cout<<", es de ";
    setColor(LIGHTGREEN);
    cout<<"$"<<acuRecaudado;
    setColor(WHITE);
    cout<<", el cual corresponde a ";
    setColor(LIGHTCYAN);
    cout<<cantEnt;
    setColor(WHITE);
    cout<<" entradas vendidas."<<endl<<endl<<endl;
    anykey("---Presione cualquier tecla para continuar---");
    return true;
    }
    cout << endl << "No ha habido recaudación alguna para el año " << anio << endl;
    cout << endl<<endl<<endl;
    anykey("---Presione cualquier tecla para volver al menú anterior---");
    return true;
}

bool recaudacionMensual(){
  cls();
  Venta obj;
  float acuRecaudado = 0;
  int mes, anio, pos = 0, cantEnt=0;
  cout << "Ingrese el mes sobre el cual calcular la recaudación (basado en este año): " << endl;
    mes = validarIngresoMes();
    cin.ignore();
    Fecha actual;
    anio = actual.getAnio();
    if(mes>12||mes<1){
        cout << endl;
        msj_error("Mes inválido, el mismo debe consistir de un valor entre 1 y 12 incluidos");
        cout << endl;
        anykey("Presione cualquier tecla para retornar. . .");
        return false;
    }
    while(obj.leerDeDisco(pos++)){
      if(obj.getfechaVenta().getAnio() == anio && obj.getfechaVenta().getMes() == mes){
        acuRecaudado += obj.getMonto();
        cantEnt+=obj.getCantidadEntradas();
      }
    }
    if(acuRecaudado!=0){
    cout << endl << "El monto de recaudación registrado para el mes de ";
    setColor(LIGHTCYAN);
    cout<<devolverMes(mes);
    setColor(WHITE);
    cout<<", del año ";
    setColor(LIGHTCYAN);
    cout<<anio;
    setColor(WHITE);
    cout<<","<<endl<<"es de ";
    setColor(LIGHTGREEN);
    cout<<"$"<<acuRecaudado;
    setColor(WHITE);
    cout<<", el cual corresponde a ";
    setColor(LIGHTCYAN);
    cout<<cantEnt;
    setColor(WHITE);
    cout<<" entradas vendidas."<<endl<<endl<<endl;


    anykey("---Presione cualquier tecla para continuar---");
    return true;
    }
    cout << endl << "No ha habido recaudación alguna para el mes de " << devolverMes(mes) << " del año " << anio << endl;
    cout << endl;
    anykey("---Presione cualquier tecla para volver al menú anterior---");
    return true;


}

void recaudacionPorTitulo(){
cls();
int cantPeliculas = contarPeliculas();
Venta obj;
Pelicula aux;
Funcion reg;
float Acum=0, cantEnt=0;
cout<<"Ingrese el ID de la película a consultar: ";
int id, pos=0;
id = validarIngresoEntero();
cin.ignore();
if(id<=0||id>cantPeliculas){
    cout << endl;
    msj_error("ID inválido, por favor, intente nuevamente.");
    cout << endl;
    anykey("Presione cualquier tecla para continuar. . .");
    return;

}
cout<<endl<<"Película: "<<devolverTitulo(id)<<endl;
while(obj.leerDeDisco(pos++)){
    int nFun=obj.getidFuncion();
    reg.leerDeDisco(nFun-1);
    if(reg.getCodigoPelicula()==id){
        Acum+=obj.getMonto();
        cantEnt+=obj.getCantidadEntradas();
    }
}
setColor(WHITE);
cout<<endl<<"El monto recaudado por la película es de: ";
setColor(LIGHTGREEN);
cout<<"$"<<Acum;
setColor(WHITE);
cout<<", el cual corresponde a ";
setColor(LIGHTGREEN);
cout<<cantEnt;
setColor(WHITE);
cout<<" entradas."<<endl<<endl<<endl;
anykey("---Presione cualquier tecla para continuar---");
}

string buscarTitulo(int numFunc){
Funcion obj;
obj.leerDeDisco(numFunc-1);
string nombre=devolverTitulo(obj.getCodigoPelicula());
return nombre;
}


void recaudacionPorGenero(){
cls();
Venta obj;
Pelicula aux;
Funcion reg;
float Acum=0;
cout<<"1- Terror "<<endl;
cout<<"2- Accion "<<endl;
cout<<"3- Comedia "<<endl;
cout<<"4- Drama "<<endl;
cout<<"5- Ciencia ficcion "<<endl;
cout<<"6- Infantil "<<endl<<endl;

cout<<"Ingrese el género de película a consultar: ";
int genero, pos=0, cantEnt=0;
genero = validarIngresoEntero();
cin.ignore();
if(genero<1||genero>6){
    cout << endl;
    msj_error("Género inválido, por favor, intente nuevamente con uno válido.");
    cout << endl;
    anykey("Presione cualquier tecla para continuar. . .");
    return;
    }
while(obj.leerDeDisco(pos++)){
    int nFun=obj.getidFuncion();
    reg.leerDeDisco(nFun-1);
    int idPelicula=reg.getCodigoPelicula();
    aux.leerDeDisco(idPelicula-1);
    if(aux.getGeneroPelicula()==genero){
        Acum+=obj.getMonto();
        cantEnt+=obj.getCantidadEntradas();
   }
 }
cout<<endl<<"El monto recaudado por el género ";
    setColor(LIGHTCYAN);
    cout<<devolverGenero(genero);
    setColor(WHITE);
    cout<<" es de ";
    setColor(LIGHTGREEN);
    cout<<"$"<<Acum;
    setColor(WHITE);
    cout<<", el cual corresponde a ";
    setColor(LIGHTCYAN);
    cout<<cantEnt;
    setColor(WHITE);
    cout<<" entradas vendidas."<<endl<<endl<<endl;
    anykey("---Presione cualquier tecla para continuar---");
    return;
}

string devolverMes(int mes){
  switch(mes){
  case 1:
      return "enero";
    break;
  case 2:
      return "febrero";
    break;
  case 3:
      return "marzo";
    break;
  case 4:
      return "abril";
    break;
  case 5:
      return "mayo";
    break;
  case 6:
      return "junio";
    break;
  case 7:
      return "julio";
    break;
  case 8:
      return "agosto";
    break;
  case 9:
      return "septiembre";
    break;
  case 10:
      return "octubre";
    break;
  case 11:
      return "noviembre";
    break;
  case 12:
      return "diciembre";
    break;
  }
}

bool recaudacionEntreFechas(){
  Fecha actual;
  Fecha Min;
  Fecha Max;
  Venta obj;
  int pos = 0, cantEnt=0;
  float recaudacion = 0;
  cls();
  cout << "Por favor, ingrese la primera fecha (DD/MM/AAAA): " << endl;
  cout << endl;
  if(!Min.cargarFecha()){
    cls();
    msj_error("Por favor, ingrese fechas válidas, de lo contrario, no podrá generarse el reporte.");
    cout << endl;
    anykey("Presione cualquier tecla para retornar. . .");
    return false;
  }
  if(Min.getAnio()<2010 || Min.getAnio()>actual.getAnio()){
    msj_error("El año no puede sobrepasar al actual, ni ser menor que el 2010 (año de apertura del local).");
    cout << endl;
    anykey("Presione cualquier tecla para retornar. . .");
    return false;
  }
  cls();
  cout << "Favor de ingresar la segunda fecha (DD/MM/AAAA): " << endl;
  cout << endl;
  if(!Max.cargarFecha()){
    cls();
    msj_error("Por favor, ingrese fechas válidas, de lo contrario, no podrá generarse el reporte.");
    cout << endl;
    anykey("Presione cualquier tecla para retornar. . .");
    return false;
  }
  if(Max.getAnio()<2010||Max.getAnio()>actual.getAnio()||Max == Min){
    msj_error("Error, el año no puede sobrepasar al actual, ni ser inferior a 2010, tampoco pueden coincidir ambas fechas.");
    cout << endl;
    anykey("Presione cualquier tecla para retornar. . .");
    return false;
  }

  if(Min>Max){
    actual = Max; //Uso a actual como auxiliar (ya no la necesito), para no tener que declarar objetos aux innecesarios (pensando eficientemente -Cris 9/9)
    Max = Min;
    Min = actual;
  }

  while(obj.leerDeDisco(pos++)){
    if(obj.getfechaVenta()>=Min && obj.getfechaVenta()<=Max){
      recaudacion += obj.getMonto();
      cantEnt+=obj.getCantidadEntradas();
    }
  }
  cls();
  if(recaudacion!=0){
    cout <<endl<< "La recaudación entre las fechas ";
    setColor(LIGHTCYAN);
    cout<<Min.getDia() << "/" << Min.getMes() << "/" << Min.getAnio();
    setColor(WHITE);
    cout<<" y ";
    setColor(LIGHTCYAN);
    cout<<Max.getDia() << "/" << Max.getMes() << "/" << Max.getAnio();
    setColor(WHITE);
    cout<<","<<endl<<"fue de ";
    setColor(LIGHTGREEN);
    cout<<"$"<<recaudacion;
    setColor(WHITE);
    cout<<", el cual corresponde a ";
    setColor(LIGHTCYAN);
    cout<<cantEnt;
    setColor(WHITE);
    cout<<" entradas vendidas."<<endl<<endl<<endl;
    anykey("---Presione cualquier tecla para continuar---");
    return true;
  }
  setColor(LIGHTGREEN);
  cout << "No ha habido recaudación ";
  setColor(LIGHTMAGENTA);
  cout << "alguna entre las fechas ";
  setColor(LIGHTCYAN);
  cout << Min.getDia() << "/" << Min.getMes() << "/" << Min.getAnio();
  setColor(LIGHTMAGENTA);
  cout << " y ";
  setColor(LIGHTCYAN);
  cout << Max.getDia() << "/" << Max.getMes() << "/" << Max.getAnio() << endl;
  setColor(WHITE);
  cout << endl;
  anykey("Presione cualquier tecla para retornar. . .");
  return true;
}

void listarPeliculasDisponibles(){
cls();
setColor(LIGHTMAGENTA);
cout << "Listado de las películas actualmente disponibles en cartelera: " << endl;
cout << endl;
setColor(WHITE);
Pelicula obj;
int pos=0;
while(obj.leerDeDisco(pos++)){
    if(fechaOk(obj.getIdPelicula())){
        obj.mostrarPelicula();
        cout<<endl;
    }
  }
cout<<endl;
anykey("Presione una tecla para continuar...");
}


void verFunciones(){
    cls();
    setColor(LIGHTGREEN);
    cout<<"          ----------------------------------------"<<endl;
    cout<<"         |                 FUNCIONES              |"<<endl;
    cout<<"          ----------------------------------------"<<endl;
    cout<<"         | 1) VER FUNCIONES DEL DÍA DE HOY        |"<<endl;
    cout<<"         | 2) VER TODAS LAS FUNCIONES DISPONIBLES |"<<endl;
    cout<<"         | 3) VER FUNCIONES DE ESTA SEMANA        |"<<endl;
    cout<<"          ----------------------------------------"<<endl;
    setColor(WHITE);
    cout<<endl<<"         Ingrese una opción: ";
    int opcion;
    cin>>opcion;
    switch(opcion){
    case 1:
        funDisponiblesHoy();
        break;
    case 2:
        funDisponibles();
        break;
    case 3:
        funDisponiblesEstaSemana();
        break;
    default:
            cout<<endl;
            msj_error("---Ingreso inválido, inténtelo de nuevo---");
            anykey("---Presione una tecla para volver al menú principal---");
            return;
    }
}

void funDisponiblesEstaSemana() /// debe revisar si la funcion no esta dada de baja.
{
    cls();
    int cont=0;
    Funcion f;
    Fecha aux;
    Hora ho;
    FILE *p;
    p=fopen("datos/funcion.dat","rb");
    if(p==NULL)
    {
        msj_error("---Error, no se encontró el archivo---");
        anykey();
        fclose(p);
    }

    while(fread(&f,sizeof(Funcion),1,p))
    {
        if(fechaOk(f.getCodigoPelicula())){
        if((f.getFecha()>aux)||(f.getFecha()>=aux && f.getHoraInicio()>ho)){
        if((aux.getAnio() == f.getFecha().getAnio() && aux.getMes() == f.getFecha().getMes() && aux.getDia() - f.getFecha().getDia() > -7 && aux.getDia() - f.getFecha().getDia() <= 0) ){
        f.mostrarFuncion(&f);
        cout<<endl;
        cont++;
        }
      }
    }
  }
  if(cont==0){
    msj_error("---No hay funciones disponibles para los próximos 7 días---");
    anykey();
}
else{
    anykey("Presione cualquier tecla para retornar. . .");
  }
 }





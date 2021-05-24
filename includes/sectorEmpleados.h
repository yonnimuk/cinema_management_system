#ifndef SECTOREMPLEADOS_H_INCLUDED
#define SECTOREMPLEADOS_H_INCLUDED
using std::cout;
#include "funcionesGenerales.h"
#include "Pelicula.h"
#include "Funcion.h"
#include "rlutil.h"
using namespace rlutil;

void confABML(); ///tire esto aca por q me decia q no estaba en el scope, perdon no se donde iba xD

//Funciones correspondientes al men� de empleados:

void menuEmpleados(){
    cout<<"              ---------------------------------------"<<endl;
    cout<<"             |           SECTOR EMPLEADOS            |"<<endl;
    cout<<"              ---------------------------------------"<<endl;
    cout<<"             | 1) CARGAR PEL�CULAS EN CARTELERA      |"<<endl;
    cout<<"             | 2) MODIFICAR FECHAS DE PEL�CULA       |"<<endl;
    cout<<"             | 3) LISTAR PEL�CULAS EN SISTEMA        |"<<endl;
    cout<<"             | 4) CARGAR FUNCIONES                   |"<<endl;
    cout<<"             | 5) CARGAR PRECIO DE ENTRADAS          |"<<endl;
    cout<<"             | 6) CONSULTAR VENTA DE ENTRADAS        |"<<endl;
    cout<<"             | 7) LISTAR CLIENTES POR APELLIDO       |"<<endl;
    cout<<"             | 8) REPORTES DE RECAUDACI�N            |"<<endl;
    cout<<"             | 9) CONFIGURACI�N DE LA APP            |"<<endl;
    cout<<"              ---------------------------------------"<<endl;
    cout<<"               Opci�n 0: VOLVER AL MEN� PRINCIPAL   "<<endl<<endl;
    cout<<"             Ingrese una opci�n: ";

}

int sectorEmpleados(){

char contrasena[30]="rocket101", intento[30];
cls();
cout<<"Ingrese la contrase�a de acceso de empleados: ";
setColor(LIGHTCYAN);
cin.getline(intento,30);
setColor(WHITE);
int contInt=0;
while(strcasecmp(contrasena, intento)!=0 && contInt<3){
    msj_error("---Contrase�a incorrecta---");
    contInt++;
    cout<<"---Queda/n "<<3-contInt<<" intento/s---";
    anykey();
    cls();
    if(contInt==3){
    msj_error("---Intentos de ingresos excedidos---");
    return 0;
  }
    cout<<"Ingrese la contrase�a de acceso de empleados: ";
    cin.getline(intento,30);
}

setlocale(LC_ALL, "spanish");

bool continuar=true;
    int opcion;


    while(continuar)
    {
        cls();
        menuEmpleados();
        cin>>opcion;
        cin.ignore();
        switch(opcion)
        {

        case 1:
        {
            ingresarPelicula();
        }break;
        case 2:
            {
            modificarFechasPeliculas();
            }break;
        case 3:
            {
            listarPeliculas();
            }break;
        case 4:
            {
            ingresarFuncion();
            }break;

        case 5:
            {
            cargarPrecios();
            }break;
        case 6:
            {
            consultarVentas();
            }break;
        case 7:
            {
              listadoClientesxApellido();
            }break;
        case 8:
            {
           reportes();
            }break;
        case 9:
            {
            configuracion();
            }break;

        case 0:
        {
            continuar=false;
        }break;

        default:
        {
            cout<<"---Opcion inv�lida---";
            anykey();
        }break;
        }
    }
    return 0;
}

//---------------------------------------------------------------

void menuReportes(){
    cout<<" ---------------------------------------"<<endl;
    cout<<"|         REPORTES DE RECAUDACI�N       |"<<endl;
    cout<<" ---------------------------------------"<<endl;
    cout<<"| 1) RECAUDACI�N POR T�TULO             |"<<endl;
    cout<<"| 2) RECAUDACI�N POR G�NERO             |"<<endl;
    cout<<"| 3) RECAUDACI�N ANUAL                  |"<<endl;
    cout<<"| 4) RECAUDACI�N MENSUAL                |"<<endl;
    cout<<"| 5) RECAUDACI�N ENTRE FECHAS           |"<<endl;
    cout<<" ---------------------------------------"<<endl;
    cout<<"  Opci�n 0: VOLVER AL MEN� DE EMPLEADOS   "<<endl<<endl;
    cout<<"Ingrese una opci�n: ";
}

void reportes(){

bool continuar=true;
int opcion;
while(continuar){
cls();
setColor(LIGHTMAGENTA);
menuReportes();
cin>>opcion;
cin.ignore();
    switch(opcion){
    case 1:
        recaudacionPorTitulo();
        break;
    case 2:
        recaudacionPorGenero();
        break;
    case 3:
        recaudacionAnual();
        break;
    case 4:
        recaudacionMensual();
        break;
    case 5:
        recaudacionEntreFechas();
        break;
    case 0:
        continuar=false;
        setColor(WHITE);
        break;

    }
  }
}

//------------------------------------------------------------------

void menuConfiguracion(){
    cout<<" ---------------------------------------"<<endl;
    cout<<"|              CONFIGURACI�N            |"<<endl;
    cout<<" ---------------------------------------"<<endl;
    cout<<"| 1) REALIZAR BACKUP DE LA APP          |"<<endl;
    cout<<"| 2) RESTAURAR BACKUP DE LA APP         |"<<endl;
    cout<<" ---------------------------------------"<<endl;
    cout<<"  Opci�n 0: VOLVER AL MEN� DE EMPLEADOS   "<<endl<<endl;
    cout<<"Ingrese una opci�n: ";
}

void configuracion(){

bool continuar=true;
int opcion;
while(continuar){
cls();
setColor(LIGHTGREEN);
menuConfiguracion();
cin>>opcion;
cin.ignore();
    switch(opcion){
    case 1:
        confBackup();
        break;
    case 2:
        confRestaurar();
        break;

    case 0:
        continuar=false;
        setColor(WHITE);
        break;

    }
  }
}

//-------------------------------------------------------------------
void menuBackup(){
    cout<<" -------------------------------------------"<<endl;
    cout<<"|                   BACKUP                  |"<<endl;
    cout<<" -------------------------------------------"<<endl;
    cout<<"| 1) REALIZAR BACKUP DE CLIENTES            |"<<endl;
    cout<<"| 2) REALIZAR BACKUP DE FUNCIONES           |"<<endl;
    cout<<"| 3) REALIZAR BACKUP DE PEL�CULAS           |"<<endl;
    cout<<"| 4) REALIZAR BACKUP DE VENTAS              |"<<endl;
    cout<<"| 5) REALIZAR BACKUP DE TODOS LOS ARCHIVOS  |"<<endl;
    cout<<" -------------------------------------------"<<endl;
    cout<<"  Opci�n 0: VOLVER AL MEN� DE EMPLEADOS   "<<endl<<endl;
    cout<<"Ingrese una opci�n: ";
}

void confBackup(){

bool continuar=true;
int opcion;
while(continuar){
cls();
setColor(LIGHTCYAN);
menuBackup();
cin>>opcion;
cin.ignore();
    switch(opcion){
    case 1:
        CrearBackUpClientes();
        break;
    case 2:
        CrearBackUpFunciones();
        break;
    case 3:
        CrearBackUpPeliculas();
        break;
    case 4:
        CrearBackUpVentas();
        break;
    case 5:
        BackUpTodos();
        break;
    case 0:
        continuar=false;
        setColor(WHITE);
        break;

    }
  }
}

//----------------------------------------------------------------

void menuRestaurar(){
    cout<<" --------------------------------------------"<<endl;
    cout<<"|                  RESTAURACI�N              |"<<endl;
    cout<<" --------------------------------------------"<<endl;
    cout<<"| 1) RESTAURAR BACKUP DE CLIENTES            |"<<endl;
    cout<<"| 2) RESTAURAR BACKUP DE FUNCIONES           |"<<endl;
    cout<<"| 3) RESTAURAR BACKUP DE PEL�CULAS           |"<<endl;
    cout<<"| 4) RESTAURAR BACKUP DE VENTAS              |"<<endl;
    cout<<"| 5) RESTAURAR BACKUP DE TODOS LOS ARCHIVOS  |"<<endl;
    cout<<" --------------------------------------------"<<endl;
    cout<<"  Opci�n 0: VOLVER AL MEN� DE EMPLEADOS   "<<endl<<endl;
    cout<<"Ingrese una opci�n: ";
}

void confRestaurar(){

bool continuar=true;
int opcion;
while(continuar){
cls();
setColor(LIGHTCYAN);
menuRestaurar();
cin>>opcion;
cin.ignore();
    switch(opcion){
    case 1:
        RestaurarClientes();
        break;
    case 2:
        RestaurarFunciones();
        break;
    case 3:
        RestaurarPeliculas();
        break;
    case 4:
        RestaurarVentas();
        break;
    case 5:
        RestaurarTodos();
        break;
    case 0:
        continuar=false;
        setColor(WHITE);
        break;

    }
  }
}



#endif // SECTOREMPLEADOS_H_INCLUDED

#ifndef SECTOREMPLEADOS_H_INCLUDED
#define SECTOREMPLEADOS_H_INCLUDED
using std::cout;
#include "funcionesGenerales.h"
#include "Pelicula.h"
#include "Funcion.h"
#include "rlutil.h"
using namespace rlutil;

void confABML(); ///tire esto aca por q me decia q no estaba en el scope, perdon no se donde iba xD

//Funciones correspondientes al menú de empleados:

void menuEmpleados(){
    cout<<"              ---------------------------------------"<<endl;
    cout<<"             |           SECTOR EMPLEADOS            |"<<endl;
    cout<<"              ---------------------------------------"<<endl;
    cout<<"             | 1) CARGAR PELÍCULAS EN CARTELERA      |"<<endl;
    cout<<"             | 2) MODIFICAR FECHAS DE PELÍCULA       |"<<endl;
    cout<<"             | 3) LISTAR PELÍCULAS EN SISTEMA        |"<<endl;
    cout<<"             | 4) CARGAR FUNCIONES                   |"<<endl;
    cout<<"             | 5) CARGAR PRECIO DE ENTRADAS          |"<<endl;
    cout<<"             | 6) CONSULTAR VENTA DE ENTRADAS        |"<<endl;
    cout<<"             | 7) LISTAR CLIENTES POR APELLIDO       |"<<endl;
    cout<<"             | 8) REPORTES DE RECAUDACIÓN            |"<<endl;
    cout<<"             | 9) CONFIGURACIÓN DE LA APP            |"<<endl;
    cout<<"              ---------------------------------------"<<endl;
    cout<<"               Opción 0: VOLVER AL MENÚ PRINCIPAL   "<<endl<<endl;
    cout<<"             Ingrese una opción: ";

}

int sectorEmpleados(){

char contrasena[30]="rocket101", intento[30];
cls();
cout<<"Ingrese la contraseña de acceso de empleados: ";
setColor(LIGHTCYAN);
cin.getline(intento,30);
setColor(WHITE);
int contInt=0;
while(strcasecmp(contrasena, intento)!=0 && contInt<3){
    msj_error("---Contraseña incorrecta---");
    contInt++;
    cout<<"---Queda/n "<<3-contInt<<" intento/s---";
    anykey();
    cls();
    if(contInt==3){
    msj_error("---Intentos de ingresos excedidos---");
    return 0;
  }
    cout<<"Ingrese la contraseña de acceso de empleados: ";
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
            cout<<"---Opcion inválida---";
            anykey();
        }break;
        }
    }
    return 0;
}

//---------------------------------------------------------------

void menuReportes(){
    cout<<" ---------------------------------------"<<endl;
    cout<<"|         REPORTES DE RECAUDACIÓN       |"<<endl;
    cout<<" ---------------------------------------"<<endl;
    cout<<"| 1) RECAUDACIÓN POR TÍTULO             |"<<endl;
    cout<<"| 2) RECAUDACIÓN POR GÉNERO             |"<<endl;
    cout<<"| 3) RECAUDACIÓN ANUAL                  |"<<endl;
    cout<<"| 4) RECAUDACIÓN MENSUAL                |"<<endl;
    cout<<"| 5) RECAUDACIÓN ENTRE FECHAS           |"<<endl;
    cout<<" ---------------------------------------"<<endl;
    cout<<"  Opción 0: VOLVER AL MENÚ DE EMPLEADOS   "<<endl<<endl;
    cout<<"Ingrese una opción: ";
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
    cout<<"|              CONFIGURACIÓN            |"<<endl;
    cout<<" ---------------------------------------"<<endl;
    cout<<"| 1) REALIZAR BACKUP DE LA APP          |"<<endl;
    cout<<"| 2) RESTAURAR BACKUP DE LA APP         |"<<endl;
    cout<<" ---------------------------------------"<<endl;
    cout<<"  Opción 0: VOLVER AL MENÚ DE EMPLEADOS   "<<endl<<endl;
    cout<<"Ingrese una opción: ";
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
    cout<<"| 3) REALIZAR BACKUP DE PELÍCULAS           |"<<endl;
    cout<<"| 4) REALIZAR BACKUP DE VENTAS              |"<<endl;
    cout<<"| 5) REALIZAR BACKUP DE TODOS LOS ARCHIVOS  |"<<endl;
    cout<<" -------------------------------------------"<<endl;
    cout<<"  Opción 0: VOLVER AL MENÚ DE EMPLEADOS   "<<endl<<endl;
    cout<<"Ingrese una opción: ";
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
    cout<<"|                  RESTAURACIÓN              |"<<endl;
    cout<<" --------------------------------------------"<<endl;
    cout<<"| 1) RESTAURAR BACKUP DE CLIENTES            |"<<endl;
    cout<<"| 2) RESTAURAR BACKUP DE FUNCIONES           |"<<endl;
    cout<<"| 3) RESTAURAR BACKUP DE PELÍCULAS           |"<<endl;
    cout<<"| 4) RESTAURAR BACKUP DE VENTAS              |"<<endl;
    cout<<"| 5) RESTAURAR BACKUP DE TODOS LOS ARCHIVOS  |"<<endl;
    cout<<" --------------------------------------------"<<endl;
    cout<<"  Opción 0: VOLVER AL MENÚ DE EMPLEADOS   "<<endl<<endl;
    cout<<"Ingrese una opción: ";
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

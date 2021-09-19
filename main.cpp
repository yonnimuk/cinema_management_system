#include <iostream>
using namespace std;
#include <locale.h>
#include "rlutil.h"
using namespace rlutil;
#include "sectorEmpleados.h"
#include "funcionesGenerales.h"
#include "Hora.h"
#include "sectorClientes.h"
#include "Fecha.h"
#include "Cliente.h"
#include "Funcion.h"
#include "Entrada.h"
///VER SECTOREMPLEADOS.H AL FINAL

int main()
{
setlocale(LC_ALL, "spanish");
bool continuar=true;
setColor(WHITE);
    int opcion;

    while(continuar)
    {
        cls();
        menuClientes();
        opcion = validarIngresoEntero();
        cin.ignore();
        switch(opcion)
        {

        case 1:
            {
            listarPeliculasDisponibles();
            }break;

        case 2:
            {
            verFunciones();
            }break;

        case 3:
            {
            consultarPrecios();
            }break;

        case 4:
            {
            msj_promo();
            }break;
        case 5:
            {
            ingresarNuevoCliente();
            }break;
        case 6:
            {
            consultarCompras();     // 7/7 Codeadas por Cris
                                   // 9/7 Arreglé los listados en consultar compras y ventas, recaudación por mes y año. Testeé y mejoré la parte visual, agregué mensajes al usuario en el sector backup (indicando que fue realizado con éxito x ej). -Cris
            }break;               //TO DO -DARLE COLOR Y CLS DONDE HAGA FALTA A LOS LISTADOS, CONSULTAS, REPORTES (NO CREO QUE FALTEN MAS QUE UN PAR)
        case 7:                  //       -HACER EL MENU DE BACKUPS Y A LA HORA DE REALIZARLO, QUE APAREZCA UN SUBMENU PREGUNTANDO SI ESTA SEGURO (S/N) SI INGRESA S, SE PROCEDE A REALIZARLO, SI INGRESA N, SE RETORNA
            {                   //        -IMPLEMENTAR EN MENUS LO NUEVO (RECAUDACIONES, CONSULTAS, ETC)
            realizarCompra();  //         -DE SER POSIBLE TESTEAR LAS FUNCIONES (TESTEÉ VARIAS, PERO SIEMPRE SE LE PUEDE PASAR POR ALTO ALGO A UNO)
            }break;           //          -REVISAR POR QUÉ EN COMPRA DE ENTRADAS PERMITE COMPRAR CON DNI NO REGISTRADO (CHEQUEARLO EN CONSULTAR VENTA DE ENTRADAS, MES 7)
        case 101:            //           -PROBLEMA DE LA HORA, QUE MUESTRA 0:20, EN VEZ DE 00:20 PONELE
            {
            sectorEmpleados();
            //listadoPeliculasxFechaEstreno(); //Cris (3/7) Ordena por apellido de la A a la Z -TESTEADO
            }break;

        case 0:
        {
            continuar=false;
        }break;

        default:
        {   cls();
            msj_error("Opción inválida");
            cout << endl;
            anykey("Presione cualquier tecla para retornar. . .");
        }break;
        }
    }
    return 0;
}

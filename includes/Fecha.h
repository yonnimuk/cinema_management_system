#ifndef FECHA_H
#define FECHA_H


class Fecha{
  private:
    int dia, mes, anio;
  public:
    Fecha();
    Fecha(int, int, int);
    bool cargarFecha();
    void mostrarFecha();
    bool operator>(Fecha);
    bool operator==(Fecha);
    bool operator<(Fecha);
    bool operator<=(Fecha);
    bool operator>=(Fecha);
    int operator-(Fecha obj);

    //setters
    void setDia(int);
    void setMes(int);
    void setAnio(int);
    void setFecha(Fecha);

    //getters
    int getDia();
    int getMes();
    int getAnio();

 };

#endif // FECHA_H

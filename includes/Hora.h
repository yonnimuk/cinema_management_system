#ifndef HORA_H
#define HORA_H


class Hora{
  private:
    int hora, minutos;
  public:
    Hora();
    Hora(int, int);
    bool cargarHora();
    void mostrarHora();
    //setters
    void setHora(int);
    void setMinutos(int);

    //getters
    int getHora();
    int getMinutos();
    bool operator<(Hora);
    bool operator>(Hora);

 };

#endif // HORA_H

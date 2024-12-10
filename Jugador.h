#ifndef JUGADOR_H
#define JUGADOR_H

#include <cstring>

class Jugador {
private:
    char nombre[50];
    int puntos;

public:
    Jugador();

    Jugador(char* nombre, int puntos);

    const char* getNombre() const;
    int getPuntos() const;
};

#endif // JUGADOR_H

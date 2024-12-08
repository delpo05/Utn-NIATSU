#ifndef JUGADOR_H
#define JUGADOR_H

#include <cstring>

class Jugador {
private:
    char nombre[50];
    int puntos;

public:
    // Constructor por defecto
    Jugador();

    // Constructor con parámetros
    Jugador(char* nombre, int puntos);




    // Getters
    const char* getNombre() const;
    int getPuntos() const;
};

#endif // JUGADOR_H

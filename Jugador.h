#ifndef JUGADOR_H_INCLUDED
#define JUGADOR_H_INCLUDED

#include <iostream>
#include <string>  // Incluye string para usar std::string

class Jugador {
private:
    std::string nombre;
    int puntos;

public:
    // Constructor para inicializar los datos del jugador
    Jugador(std::string n = "", int p = 0);

    // Métodos para establecer y obtener el nombre y los puntos
    void setNombre(const std::string& n);
    void setPuntos(int p);
    std::string getNombre() const;
    int getPuntos() const;

    // Método para mostrar los datos del jugador
    void mostrar() const;
};

#endif // JUGADOR_H_INCLUDED

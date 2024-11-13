#ifndef RANKING_H
#define RANKING_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include "Jugador.h"

class Ranking {
public:
    Ranking(const std::string& archivo);
    void mostrarRanking(sf::RenderWindow& window);

private:
    std::string archivo_;
};

#endif

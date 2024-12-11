#pragma once
#include <SFML/Graphics.hpp>
#include "colision.h"
#include "disparo_padre.h"

class Disparo_enemigo: public disparo_padre
{
public:
    Disparo_enemigo (float x, float y);
    void update();
    void disparo2do() const;
};


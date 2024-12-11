#pragma once
#include <SFML/Graphics.hpp>
#include "colision.h"
#include "disparo_padre.h"

class disparo: public disparo_padre
{
public:
    disparo(float x, float y);
    void update();

};


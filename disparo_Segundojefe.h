#pragma once
#include <SFML/Graphics.hpp>
#include "colision.h"
#include "disparo_padre.h"

class disparo_segundo_jefe: public disparo_padre
{
public:
    disparo_segundo_jefe (float x, float y);
    void update();

};

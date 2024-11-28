#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "disparo_Segundojefe.h"
#include "colision.h"
#include "jefe.h"

class Segundo_jefe : public jefe {
    private:

    std::vector<disparo_segundo_jefe> tiroJ;

    bool bandera_jefe_muerto2;
    bool bandera_pasoPantalla;


public:
    Segundo_jefe ();
    void update();

    const std::vector<disparo_segundo_jefe>& getDisparos() const;

    void disparar();
    void explosion();
    bool getbandera_jefe_muerto2(){return bandera_jefe_muerto2;}


};

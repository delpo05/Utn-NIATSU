#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "disparos_primer_jefe.h"
#include "colision.h"
#include "jefe.h"

class primer_jefe : public jefe {
private:
    std::vector<disparo_primer_jefe> tiroJ;
    bool bandera_jefe_muerto;
    size_t cantidad_de_disparos;
public:
    primer_jefe();
    void update();
    std::vector<disparo_primer_jefe>& getDisparos();
    void disparar();
    void explosion();
    bool getbandera_jefe_muerto(){return bandera_jefe_muerto; }
    size_t getCantidad_de_disparos(){return cantidad_de_disparos;}
    void borrarDisparos();


};

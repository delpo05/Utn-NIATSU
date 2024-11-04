
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "disparos_primer_jefe.h"
#include "colision.h"

class primer_jefe : public sf::Drawable, public collisionable {
    private:
    sf::Sprite _sprite;
    sf::Texture* _texture;
    float _velocidadX;
    float _velocidadY;
    std::vector<disparo_primer_jefe> disparos;
    float disparoTimer;            // Temporizador para controlar el disparo
    float intervaloDisparo;         // Intervalo aleatorio para disparar
    int vida_primer_jefe;
    sf::Sound tiroColi;
    sf::SoundBuffer audiotiroColi;
    sf::Clock timerAparicion;
    sf::Time tiempo_transcurrido;

    int TimerRespawn;
    float _frame;



public:
    primer_jefe ();
    void update();
    void respawn();
    const std::vector<disparo_primer_jefe>& getDisparos() const;
    sf::FloatRect getBounds() const;
    void disparar();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void setVida_primer_jefe (int vida){vida_primer_jefe=vida;}
    int getVida(){return vida_primer_jefe;}

    void explosion();

};

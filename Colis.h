#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Disparo_enemigo.h"
#include "colision.h"

class Colis : public sf::Drawable, public collisionable {
    private:
    sf::Sprite _sprite;
    sf::Texture _texture;
    ///
    sf::Sound _canal;
    sf::SoundBuffer _explosion;

    ///
    float _velocidadX;
    float _velocidadY;
    std::vector<Disparo_enemigo> disparos;
    float disparoTimer;            // Temporizador para controlar el disparo
    float intervaloDisparo;         // Intervalo aleatorio para disparar
    int vida_coli;
    int cantidadDeApariciones;



public:
    Colis();
    void update();
    void respawn();
    const std::vector<Disparo_enemigo>& getDisparos() const;
    sf::FloatRect getBounds() const;
    void disparar();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void setVida_coli(int vida){vida_coli=vida;}
    int getVida(){return vida_coli;}

};

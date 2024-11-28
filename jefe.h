#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "colision.h"

class jefe : public sf::Drawable, public collisionable {
    protected:
        sf::Sprite _sprite;
        sf::Texture _texture;
        float _velocidadX;
        float _velocidadY;
        float disparoTimer;
        float intervaloDisparo;

        int vida_jefe;

        sf::Sound disparoJefe;
        sf::SoundBuffer audiodisparoJefe;
        sf::Sound explosionJefe;
        sf::SoundBuffer audioexplosionJefe;
        sf::Clock timerAparicion;
        sf::Time tiempo_transcurrido;

        int TimerRespawn;
        float _frame;
        int _contador;


        sf::Sound recibetiro;
        sf::SoundBuffer bufferrecibetiro;

    public:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        sf::FloatRect getBounds() const;
        void setVida_jefe(int vida) { vida_jefe = vida; }
        int getVida() { return vida_jefe; }
        void recibedanio();
        bool impacto_img = false;
        sf::Clock timerAparicion_jefe;
        sf::Time tiempo_transcurrido_jefe;

};

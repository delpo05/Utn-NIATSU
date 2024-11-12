#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "disparo_Segundojefe.h"
#include "colision.h"

class Segundo_jefe : public sf::Drawable, public collisionable {
    private:
    sf::Sprite _sprite;
    sf::Texture* _texture;
    float _velocidadX;
    float _velocidadY;
    std::vector<disparo_segundo_jefe> tiroJ;
    float disparoTimer;            // Temporizador para controlar el disparo
    float intervaloDisparo;         // Intervalo aleatorio para disparar
    int vida_segundo_jefe;

    sf::Sound disparoJefe;
    sf::SoundBuffer audiodisparoJefe;

    sf::Sound explosionJefe;
    sf::SoundBuffer audioexplosionJefe;



    sf::Clock timerAparicion;
    sf::Time tiempo_transcurrido;

    int TimerRespawn;
    float _frame;
    int _contador;
    bool bandera_jefe_muerto2;
    bool bandera_pasoPantalla;

    sf::Sound recibetiro;
    sf::SoundBuffer bufferrecibetiro;




public:
    Segundo_jefe ();
    void update();
    void respawn();
    const std::vector<disparo_segundo_jefe>& getDisparos() const;
    sf::FloatRect getBounds() const;
    void disparar();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void setVida_segundo_jefe (int vida){vida_segundo_jefe=vida;}
    int getVida(){return vida_segundo_jefe;}
    void explosion();
    bool getbandera_jefe_muerto2(){return bandera_jefe_muerto2;}
    void recibedanio();
    bool impacto_img;
    sf::Clock timerAparicion_jefe2;
    sf::Time tiempo_transcurrido_jefe2;

};

/// colis.h
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Disparo_enemigo.h"
#include "colision.h"

class Colis : public sf::Drawable, public collisionable {
    private:
    sf::Sprite _sprite;
    sf::Texture* _texture;
    float _velocidadX;
    float _velocidadY;
    std::vector<Disparo_enemigo> tiroC;
    float disparoTimer;            // Temporizador para controlar el disparo
    float intervaloDisparo;         // Intervalo aleatorio para disparar
    int vida_coli;
    sf::Sound tiroColi;
    sf::SoundBuffer audiotiroColi;
    sf::Clock timerAparicion;
    sf::Time tiempo_transcurrido;
    int _CantidadColis;
    int TimerRespawn;
    float _frame;
    size_t cant;



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
    int getCantidadColis(){return _CantidadColis;}
    void setCantidadColis(int cant){_CantidadColis = cant;}
    void explosion();
    void coli2donivel();
    bool banderaSegundoNivel;
    bool banderaAparicionSegundosColis;
    void setBanderaSegundoNivel(bool b){banderaSegundoNivel = b;}
    size_t getCant(){return cant;}
    void borrarDisparos();


};

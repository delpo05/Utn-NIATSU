#pragma once
#include <SFML\Graphics.hpp>
#include "disparo.h"
#include "colision.h"

// La clase Nave representa la nave del jugador y hereda de sf::Drawable y collisionable.
class Nave: public sf::Drawable, public collisionable
{
    sf::Sprite _sprite;  // Sprite de la nave
    sf::Texture _texture; // Textura de la nave, carga la imagen desde un archivo.
    float _velocidad;    // Velocidad de la nave
    std::vector<disparo> tiro;  // Vector que almacena los disparos
    int vida_nave;       // Puntos de vida de la nave
    size_t cantidad_de_disparos;
public:
    Nave();  // Constructor de la nave
    void update();  // Actualiza el estado de la nave
    void disparar();  // Genera un nuevo disparo
    const std::vector<disparo>& getDisparos() const; // Retorna los disparos actuales
    sf::FloatRect getBounds() const;  // Obtiene los límites de la nave (para colisiones)
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override; // Dibuja la nave en pantalla
    void setVida_nave(int vida) { vida_nave = vida; }  // Establece la vida de la nave
    int getVida_nave() { return vida_nave; }  // Obtiene la vida de la nave
    size_t Getcantidad_de_disparos(){return cantidad_de_disparos;};
};


#include "disparo_Segundojefe.h"
//lore
// Constructor del disparo
disparo_segundo_jefe::disparo_segundo_jefe(float x, float y) {
    texture = new sf::Texture;
    texture->loadFromFile("imagen_NIATSU.png");
    sprite.setTexture(*texture);
    sprite.setTextureRect({7,182,97,48});
    sprite.setOrigin(sprite.getGlobalBounds().width/2, sprite.getGlobalBounds().height-10);
    sprite.setPosition(x, y);
    velocidad = 10.0; // Velocidad de movimiento del disparo
}



// Actualizar posición del disparo
void disparo_segundo_jefe::update() {
    sprite.move(0, velocidad); // Movimiento hacia arriba
}

// Dibujar el disparo
void disparo_segundo_jefe::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);

}
// Obtener los límites del disparo (para colisiones)
sf::FloatRect disparo_segundo_jefe::getBounds() const {
    return sprite.getGlobalBounds();
}

disparo_segundo_jefe::~disparo_segundo_jefe() {
    if(sprite.getPosition().y>600){
    delete texture;}
}


#include "disparos_primer_jefe.h"
//lore
// Constructor del disparo
disparo_primer_jefe::disparo_primer_jefe(float x, float y) {
    texture = new sf::Texture;
    texture->loadFromFile("imagen_NIATSU.png");
    sprite.setTexture(*texture);
    sprite.setTextureRect({40,923,35,32});
    sprite.setOrigin(sprite.getGlobalBounds().width/2, sprite.getGlobalBounds().height-10);
    sprite.setPosition(x, y);
    velocidad = 10.0; // Velocidad de movimiento del disparo
}



// Actualizar posición del disparo
void disparo_primer_jefe::update() {
    sprite.move(0, velocidad); // Movimiento hacia arriba
}

// Dibujar el disparo
void disparo_primer_jefe::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);

}
// Obtener los límites del disparo (para colisiones)
sf::FloatRect disparo_primer_jefe::getBounds() const {
    return sprite.getGlobalBounds();
}

disparo_primer_jefe::~disparo_primer_jefe() {
    if(sprite.getPosition().y>600){
    delete texture;}
}

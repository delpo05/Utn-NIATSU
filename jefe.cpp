#include "jefe.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <stdlib.h>


void jefe::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(_sprite, states);
}

sf::FloatRect jefe::getBounds() const {
    return _sprite.getGlobalBounds();
}

void jefe::recibedanio(){
    setVida_jefe (getVida()-1);
    impacto_img = true;
    timerAparicion_jefe.restart();
    recibetiro.play();

}

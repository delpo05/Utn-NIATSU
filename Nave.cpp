#include "Nave.h"


Nave::Nave()
{
    _velocidad = 10;
    _texture.loadFromFile("Nave.png");
    _sprite.setTexture(_texture);
    _sprite.setOrigin(_sprite.getGlobalBounds().width/2, _sprite.getGlobalBounds().height);


}

void Nave::update()
{
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            _sprite.move(0,-_velocidad);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            _sprite.move(-_velocidad,0);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            _sprite.move(0,_velocidad);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            _sprite.move(_velocidad,0);
        }


        if(_sprite.getGlobalBounds().left<0){
            _sprite.setPosition(_sprite.getOrigin().x, _sprite.getPosition().y);
            //_velocidad.x = -_velocidad.x;
        }
        if(_sprite.getGlobalBounds().top<0){
            _sprite.setPosition(_sprite.getPosition().x, _sprite.getOrigin().y);
            //_velocidad.y = -_velocidad.y;
        }
        if(_sprite.getGlobalBounds().top + _sprite.getGlobalBounds().height>600){
            _sprite.setPosition(_sprite.getPosition().x,600 + (_sprite.getGlobalBounds().height - _sprite.getOrigin().y));
            //_velocidad.y = -_velocidad.y;

        }
        if(_sprite.getGlobalBounds().left + _sprite.getGlobalBounds().width>800){
            _sprite.setPosition(800- (_sprite.getGlobalBounds().width - _sprite.getOrigin().x), _sprite.getPosition().y);
            //_velocidad.x = -_velocidad.x;
        }






}


void Nave::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);

}

/*sf::FloatRect Nave::getBounds() const{
    return _sprite.getGlobalBounds();
}*/










#pragma once
#include <SFML/Graphics.hpp>
#include "disparo.h"

class Colis: public sf::Drawable{

       sf::Sprite _sprite;
       sf::Texture _texture;
       int timesRespawn;
       int vida;
       float _velocidad;
       std::vector <disparo> disparos;
       sf::Vector2f _newPosition;

  public:
       Colis();
       void update ();
       void respawn ();
       const std::vector<disparo>& getDisparos() const;
       sf::FloatRect getBounds () const;
       void disparar ();
       void golpeado ();
       void draw(sf::RenderTarget& target, sf::RenderStates states) const override;




};

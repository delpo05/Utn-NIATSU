#pragma once
#include <SFML/Graphics.hpp>

class collisionable{

public:
    virtual sf::FloatRect getBounds() const = 0;
    bool isCollision(collisionable& col) const;
};

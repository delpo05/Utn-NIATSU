#include "colision.h"

bool collisionable::isCollision( collisionable& obj) const{
    return getBounds().intersects(obj.getBounds());
}

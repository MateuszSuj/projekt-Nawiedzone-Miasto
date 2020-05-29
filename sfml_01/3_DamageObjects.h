#ifndef DAMAGEOBJECTS_H
#define DAMAGEOBJECTS_H

#include <sfml\Graphics.hpp>
#include "3_PlayerBullet.h"
#include <vector>

class DamageObjects
{
private:
    float scale;
    std::vector <PlayerBullet> bullets;
    std::vector <sf::CircleShape> zombieShapes;

    float bulletRange;
    float bulletSpeed;

public:
    DamageObjects(float scale, float bulletRange, float bulletSpeed);
    void playerShoot(int direction, sf::Vector2f playerPosition);
    void updateZombiesShapes(std::vector <sf::CircleShape> zombieShapes);
    std::vector <int> shootUpdate(float deltaTime); //std::vector <sf::CircleShape> zombies
    void draw(sf::RenderWindow &window);
};

#endif // DAMAGEOBJECTS_H

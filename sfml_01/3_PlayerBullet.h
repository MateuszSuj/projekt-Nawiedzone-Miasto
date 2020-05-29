#ifndef PLAYERBULLET_H
#define PLAYERBULLET_H

#include <sfml\Graphics.hpp>

class PlayerBullet {
private:
    float bulletRange;
    float bulletSpeed;
    sf::Texture bulletTexture;
    sf::Sprite bulletSprite;
    sf::Vector2f direction;

public:
    PlayerBullet(sf::Vector2f position, sf::Vector2f direction, float rotation, float scale, float bulletRange, float bulletSpeed);
    void move(float deltaTime);
    sf::FloatRect getGlobalBounds();
    float getRange();
    void updateRange(float deltaTime);
    void draw(sf::RenderWindow &window);
};

#endif // PLAYERBULLET_H

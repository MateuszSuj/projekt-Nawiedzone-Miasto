#include "3_PlayerBullet.h"
#include "2_Zombie.h"

PlayerBullet::PlayerBullet(sf::Vector2f position, sf::Vector2f direction, float rotation, float scale, float bulletRange, float bulletSpeed){
    // GET VARIABLES //
    this->bulletRange = bulletRange;
    this->bulletSpeed = bulletSpeed;
    this->direction = direction;
    // TEXTURES //
    bulletTexture.loadFromFile("pics/bullet.png");
    // SPRITE //
    bulletSprite.setOrigin(8,4);
    bulletSprite.setScale(scale,scale);
    bulletSprite.setPosition(position);
    bulletSprite.setRotation(rotation);
}

void PlayerBullet::move(float deltaTime){
    bulletSprite.move(direction.x * bulletSpeed * deltaTime, direction.y * bulletSpeed * deltaTime);
}

sf::FloatRect PlayerBullet::getGlobalBounds(){
    return bulletSprite.getGlobalBounds();
}

float PlayerBullet::getRange(){
    return bulletRange;
}

void PlayerBullet::updateRange(float deltaTime){
    bulletRange -= deltaTime;
}

void PlayerBullet::draw(sf::RenderWindow &window){
    bulletSprite.setTexture(bulletTexture);
    window.draw(bulletSprite);
}

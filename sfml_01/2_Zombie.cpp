#include "2_Zombie.h"

Zombie::Zombie(float scale, int zombieHealth, int zombieSpeed, int zombieDamage)
{
    // GET VARIABLES //
    this->zombieHealth = zombieHealth;
    this->zombieSpeed = zombieSpeed;
    this->zombieDamage = zombieDamage;

    // SHAPE //
    zombieShape.setRadius(r);
    zombieShape.setOrigin(r,r);
    zombieShape.setFillColor(sf::Color(0, 150, 80));
    zombieShape.setOutlineThickness(4);
    zombieShape.setOutlineColor(sf::Color::Black);
    zombieShape.setScale(scale/5, scale/5);
}

void Zombie::setPosition(sf::Vector2f position){
    zombieShape.setPosition(position);
}

void Zombie::move(sf::Vector2f position){
    position.x *= zombieSpeed;
    position.y *= zombieSpeed;
    zombieShape.move(position);
}

sf::Vector2f Zombie::getPosition(){
    return zombieShape.getPosition();
}

sf::CircleShape Zombie::getShape(){
    return zombieShape;
}

int Zombie::getDamage(){
    return zombieDamage;
}

bool Zombie::getIsStunned(){
    return isStunned;
}
void Zombie::setIsStunned(bool isStunned){
    this->isStunned = isStunned;
}

void Zombie::diffStunTime(float diff){
    zombieStunTime -= diff;
}
int Zombie::getStunTime(){
    return zombieStunTime;
}
void Zombie::setStunTime(int stunTime){
    this->zombieStunTime = stunTime;
}
void Zombie::diffHealth(int damageAmount){
    zombieHealth -= damageAmount;
}
int Zombie::getHealth(){
    return zombieHealth;
}
void Zombie::setHealth(int health){
    this->zombieHealth = health;
}

void Zombie::draw(sf::RenderWindow &window){
    window.draw(zombieShape);
}


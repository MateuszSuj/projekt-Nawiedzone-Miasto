#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <sfml\Graphics.hpp>

class Zombie{
private:
        float scale;

        int zombieHealth;
        int zombieSpeed;
        int zombieDamage;

        int r = 40;
        int zombieStunTime;
        sf::CircleShape zombieShape;
        bool isStunned = false;
public:
    Zombie(float scale, int zombieHealth, int zombieSpeed, int zombieDamage);
    void move(sf::Vector2f position);
    void setPosition(sf::Vector2f position);
    sf::Vector2f getPosition();
    sf::CircleShape getShape();
    int getDamage();
    bool getIsStunned();
    void setIsStunned(bool isStunned);
    void diffStunTime(float diff);
    int getStunTime();
    void setStunTime(int stunTime);
    void diffHealth(int damageAmount);
    int getHealth();
    void setHealth(int health);
    void draw(sf::RenderWindow &window);
};

#endif // ZOMBIE_H

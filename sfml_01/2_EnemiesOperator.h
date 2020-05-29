#ifndef ENEMIESOPERATOR_H
#define ENEMIESOPERATOR_H

#include <sfml\Graphics.hpp>

#include <vector>
#include <cmath>

#include "2_Zombie.h"

class EnemiesOperator {
private:
    float scale;
    int zombieHealth;
    int zombieSpeed;
    int zombieDamage;
    int zombieStunTime;
    std::vector <Zombie> zombies;
    std::vector <sf::Vector2f> spawnPoints;
    std::vector <sf::CircleShape> zombieShapes;
public:
    EnemiesOperator(float scale, int zombieHealth, int zombieSpeed, int zombieDamage, int zombieStunTime, std::vector <sf::Vector2f> spawnPoints);
    void spawn(int amount);
    bool checkLevelEnd();
    int updateZombies(sf::Vector2f playerPosition, std::vector<int> zombiesToDealDamage, float deltaTime);
    std::vector <sf::CircleShape> sendZombies();
    void draw(sf::RenderWindow &window);
};

#endif // ZOMBIESOPERATOR_H

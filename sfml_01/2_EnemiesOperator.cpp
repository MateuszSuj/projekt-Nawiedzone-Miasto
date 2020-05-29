#include "2_EnemiesOperator.h"

EnemiesOperator::EnemiesOperator(float scale, int zombieHealth, int zombieSpeed, int zombieDamage, int zombieStunTime, std::vector <sf::Vector2f> spawnPoints)
{
    // GET VARIABLES //
    this->scale = scale;
    this->zombieHealth = zombieHealth;
    this->zombieSpeed = zombieSpeed;
    this->zombieDamage = zombieDamage;
    this->zombieStunTime = zombieStunTime;
    this->spawnPoints = spawnPoints;
}

void EnemiesOperator::spawn(int amount){

    for(int i = 0, j = 0; i < amount; i++, j++){
        if(i > (int)spawnPoints.size()) j = 0;
        Zombie temp(scale, zombieHealth, zombieSpeed, zombieDamage);
        temp.setPosition(spawnPoints[j]);
        zombies.emplace_back(temp);
    }
    /*
    for(int i = 0; i < amount; i++){
        for(int j = 1; j < (int)spawnPoints.size(); j++){
            Zombie temp(scale, zombieHealth, zombieSpeed, zombieDamage);
            temp.setPosition(spawnPoints[i]);
            zombies.emplace_back(temp);
        }
    }
    */
}

bool EnemiesOperator::checkLevelEnd(){
    if(zombies.size() <= 0){
        return true;
    }
    else return false;
}

int EnemiesOperator::updateZombies(sf::Vector2f playerPosition, std::vector<int> zombiesToDealDamage, float deltaTime){

    for(int i = 0; i < (int)zombiesToDealDamage.size(); i++){
        if(zombies[zombiesToDealDamage[i]].getHealth() > 10) zombies[zombiesToDealDamage[i]].diffHealth(10);
        else zombies.erase(zombies.begin() + zombiesToDealDamage[i]);
    }
    zombieShapes.clear();

    int damageDealedAmount = 0;
    sf::Vector2f direction;
    sf::Vector2f positionDifference;
    for(int i = 0; i < (int)zombies.size(); i++){
        zombieShapes.emplace_back(zombies[i].getShape());

        positionDifference = playerPosition - zombies[i].getPosition();

        float distance = sqrt(positionDifference.x * positionDifference.x + positionDifference.y * positionDifference.y);

        direction = {positionDifference.x / (std::abs(positionDifference.x) + std::abs(positionDifference.y)),
                     positionDifference.y / (std::abs(positionDifference.x) + std::abs(positionDifference.y))};

        if(distance < 16 * scale) {
            zombies[i].setIsStunned(true);
            if (zombies[i].getStunTime() == 0){
                zombies[i].setStunTime(zombieStunTime);
                damageDealedAmount += zombies[i].getDamage();
            }
        }

        if(zombies[i].getIsStunned() == true){
            if(zombies[i].getStunTime() == 0)zombies[i].setIsStunned(false);
            else zombies[i].diffStunTime(deltaTime);
        }
        else zombies[i].move(direction*deltaTime);
    }
    return -damageDealedAmount;
}

std::vector <sf::CircleShape> EnemiesOperator::sendZombies(){
    return zombieShapes;
}

void EnemiesOperator::draw(sf::RenderWindow &window){
    for(int i = 0; i < (int)zombies.size(); i++){
        zombies[i].draw(window);
    }
}



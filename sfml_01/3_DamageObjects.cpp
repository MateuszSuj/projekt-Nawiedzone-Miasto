#include "3_DamageObjects.h"
#include <iostream>

DamageObjects::DamageObjects(float scale, float bulletRange, float bulletSpeed)
{
    // GET VARIABLES //
    this->scale = scale;
    this->bulletRange = bulletRange;
    this->bulletSpeed = bulletSpeed;
}

void DamageObjects::playerShoot(int direction, sf::Vector2f playerPosition){

    if     (direction == 0) { PlayerBullet temp(playerPosition, {0, -1}, -90, scale, bulletRange, bulletSpeed); bullets.emplace_back(temp); }
    else if(direction == 1) { PlayerBullet temp(playerPosition, {0, 1}, 90, scale, bulletRange, bulletSpeed); bullets.emplace_back(temp); }
    else if(direction == 2) { PlayerBullet temp(playerPosition, {-1, 0}, 180, scale, bulletRange, bulletSpeed); bullets.emplace_back(temp); }
    else if(direction == 3) { PlayerBullet temp(playerPosition, {1,0}, 0, scale, bulletRange, bulletSpeed); bullets.emplace_back(temp); }
}

void DamageObjects::updateZombiesShapes(std::vector <sf::CircleShape> zombieShapes){
    this->zombieShapes = zombieShapes;
}

std::vector <int> DamageObjects::shootUpdate(float deltaTime){
    std::vector<int> zombiesToDealDamage;
    for(int j = 0; j < (int)bullets.size(); j++){
            bullets[j].move(deltaTime);
            bullets[j].updateRange(deltaTime);
    }

    for(int j = 0; j < (int)bullets.size(); j++){
        if(bullets[j].getRange() < 0) bullets.erase(bullets.begin() + j);
    }

    std::cout << bullets.size() << std::endl;
    for(int i = 0; i < (int)zombieShapes.size(); i++){
        for(int j = 0; j < (int)bullets.size();){
            if(bullets[j].getGlobalBounds().intersects(zombieShapes[i].getGlobalBounds())){
               zombiesToDealDamage.emplace_back(i);
               bullets.erase(bullets.begin() + j);
            }
            else j++;
        }
    }
    return zombiesToDealDamage;
}

void DamageObjects::draw(sf::RenderWindow &window){
    for(int i = 0; i < (int)bullets.size(); i++){
        bullets[i].draw(window);
    }
}



#ifndef PLAYEROPERATOR_H
#define PLAYEROPERATOR_H

#include <sfml\Graphics.hpp>

#include "1_AnimationOperator.h"

class PlayerOperator {
private:
    float scale; //scale of player
    int playerMaxHealth; //maximum health of player
    int playerHealth; //health of player in that moment
    float playerSpeed; //movement speed
    float playerAnimationSpeed; //how fast animation is displayed

    int playerAnimationNumber = 0; //default player animation
    int offset = 8; // 1/2 of 16x16 imagine resolution

    sf::Texture playerTexture;
    Animation playerAnimation;
    sf::Sprite playerSprite;
    sf::Vector2f playerSpawnPoint;
    std::vector <sf::Sprite> collisionElements;

public:
    PlayerOperator(float scale, int playerMaxHealth, float playerSpeed, float playerAnimationSpeed, sf::Vector2f playerSpawnPoint);
    sf::Vector2f getPosition(); //get position of player sprite
    void collisionLoad(std::vector <sf::Sprite> mapLayer2);
    void movement(sf::Vector2f direction); //movement of a player and animate his movement
    void healthUpdate(int changeOfHealth);
    int getHp();
    void animate(float deltaTime);
    void draw(sf::RenderWindow &window); // set animations and draw player
};

#endif // PLAYEROPERATOR_H

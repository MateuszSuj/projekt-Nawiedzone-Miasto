#include "1_PlayerOperator.h"

PlayerOperator::PlayerOperator(float scale, int playerMaxHealth, float playerSpeed, float playerAnimationSpeed, sf::Vector2f playerSpawnPoint) : playerAnimation(&playerTexture, sf::Vector2u(3,5), 0.3f){
    // GET VARIABLES //
    this->scale = scale;
    this->playerMaxHealth = playerMaxHealth;
    this->playerSpeed = playerSpeed;
    this->playerAnimationSpeed = playerAnimationSpeed;
    this->playerSpawnPoint = playerSpawnPoint;
    // SET VARIABLES //
    playerHealth = playerMaxHealth;
    // TEXTURES //
    playerTexture.loadFromFile("pics/character.png");
    // PLAYER SPRITE SETTINGS //
    playerSprite.setTexture(playerTexture);
    playerSprite.setOrigin(6, 7.5);
    playerSprite.setScale(scale, scale);
    playerSprite.setPosition(playerSpawnPoint);
    // PLAYER ANIMATION SETTINGS //
    playerAnimation = {&playerTexture, sf::Vector2u(3,5), 0.3f};
}

sf::Vector2f PlayerOperator::getPosition(){
     return playerSprite.getPosition();
}

void PlayerOperator::collisionLoad(std::vector <sf::Sprite> mapLayer2){
    this->collisionElements = mapLayer2;
}

void PlayerOperator::movement(sf::Vector2f direction){
    if(direction.x != 0 || direction.y !=0){

        bool collision = false;
        playerSprite.move(direction * playerSpeed);

        for(int i = 0; i < (int)collisionElements.size(); i++){
            if(playerSprite.getGlobalBounds().intersects(collisionElements[i].getGlobalBounds())){ collision = true; i = (int)collisionElements.size();}
        }
        if(collision == false){
            if(direction.x < 0) playerAnimationNumber = 1;
            else if(direction.x > 0) playerAnimationNumber = 2;
            else if(direction.y > 0) playerAnimationNumber = 0;
            else if(direction.y < 0) playerAnimationNumber = 3;
        }
        else playerSprite.move(-direction * playerSpeed);
    }
    else playerAnimationNumber = 4;
}

void PlayerOperator::healthUpdate(int changeOfHealth){
    if(changeOfHealth != 0) playerHealth += changeOfHealth;
}

int PlayerOperator::getHp(){
    return playerHealth;
}

void PlayerOperator::animate(float deltaTime){
    playerAnimation.Update(playerAnimationNumber, deltaTime * playerAnimationSpeed);
    playerSprite.setTextureRect(playerAnimation.uvRect);
}

void PlayerOperator::draw(sf::RenderWindow &window){
    window.draw(playerSprite);
}

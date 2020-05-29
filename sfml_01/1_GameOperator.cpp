#include "1_GameOperator.h"
#include <iostream>

GameOperator::GameOperator(int res_x, int res_y, sf::RenderWindow *window,
                           float scale, float MOscale, float DOscale, float POscale, float EOscale,
                           int playerMaxHealth, float playerSpeed, float playerAnimationSpeed, int shootDelay, sf::Vector2f playerSpawnPoint,
                           std::vector <sf::Vector2f> spawnPoints, int zombieHealth, int zombieSpeed, int zombieDamage, int zombieStunTime,
                           float bulletRange, int bulletSpeed)

    : MO(scale*MOscale),
      DO(scale*DOscale, bulletRange, bulletSpeed),
      PO(scale*POscale, playerMaxHealth, playerSpeed, playerAnimationSpeed, playerSpawnPoint),
      EO(scale*EOscale, zombieHealth,  zombieSpeed, zombieDamage, zombieStunTime, spawnPoints),
      GO(sf::Vector2i(res_x,res_y))
{

    this->res_x = res_x;
    this->res_y = res_y;
    this->window = window;

    this->scale = scale;
    this->MOscale = MOscale;
    this->DOscale = DOscale;
    this->POscale = POscale;
    this->EOscale = EOscale;

    this->playerMaxHealth = playerMaxHealth;
    this->playerSpeed = playerSpeed;
    this->playerAnimationSpeed = playerAnimationSpeed;
    this->shootDelay = shootDelay;
    this->playerSpawnPoint = playerSpawnPoint;

    this->spawnPoints = spawnPoints;
    this->zombieHealth = zombieHealth;
    this->zombieSpeed = zombieSpeed;
    this->zombieDamage = zombieDamage;
    this->zombieStunTime = zombieStunTime;

    this->bulletRange = bulletRange;
    this->bulletSpeed = bulletSpeed;
}

void GameOperator::events(int scene){
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) window->close();

        if(event.type == sf::Event::MouseButtonPressed){
            if(event.mouseButton.button == sf::Mouse::Left){
                sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);
                sf::Vector2f worldPos = window->mapPixelToCoords(pixelPos);
                std::cout << worldPos.x << " " << worldPos.y << std:: endl;
            }
        }
        shoot = clock.getElapsedTime();
        if(shoot.asMilliseconds() > shootDelay){
            if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Escape){
                    window->close();
                }
                if (event.key.code == sf::Keyboard::Up && scene == 1)
                {
                    DO.playerShoot(0, PO.getPosition());
                    clock.restart();
                }
                else if (event.key.code == sf::Keyboard::Down && scene == 1)
                {
                    DO.playerShoot(1, PO.getPosition());
                    clock.restart();
                }
                else if (event.key.code == sf::Keyboard::Left && scene == 1)
                {
                    DO.playerShoot(2, PO.getPosition());
                    clock.restart();
                }
                else if (event.key.code == sf::Keyboard::Right && scene == 1)
                {
                    DO.playerShoot(3, PO.getPosition());
                    clock.restart();
                }
            }
        }
    }
}

void GameOperator::updates(float deltaTime){
    std::vector <int> zombiesToDealDamage;
    playerPosition = PO.getPosition();
    GO.updatePlayerPosition(playerPosition);
    DO.updateZombiesShapes(EO.sendZombies());
    zombiesToDealDamage = DO.shootUpdate(deltaTime);
    PO.healthUpdate(EO.updateZombies(playerPosition, zombiesToDealDamage, deltaTime));
    PO.animate(deltaTime);
    GO.addHP(std::to_string(PO.getHp()));
}

void GameOperator::setView(){
    defaultView.setCenter(8 * scale, 8 * scale);
    defaultView.setSize(res_x, res_y);
    defaultView.move(240*scale, 240*scale);
    window->setView(defaultView);
}

void GameOperator::cameraOnPlayerUpdate(){
    cameraOnPlayer.setCenter(8 * scale, 8 * scale);
    cameraOnPlayer.setSize(res_x, res_y);
    cameraOnPlayer.move(playerPosition);
    window->setView(cameraOnPlayer);
}

void GameOperator::draw(){
    shoot = clock.getElapsedTime();
    // CLEAR WINDOW //
    window->clear(sf::Color::Black);

    // DRAW //

    // LAYERMAP1 - Ground //
    MO.drawLayer(1, *window);

    // LAYERMAP2 - Furnitures and walls//
    MO.drawLayer(2, *window);

    // BULLETS //
    DO.draw(*window);

    // ZOMBIES //
    EO.draw(*window);

    // PLAYER //
    PO.draw(*window);

    // LAYERMAP3 - Roof and windows//
    MO.drawLayer(3, *window);
    // GUI //

    // GUI //

    GO.drawGUI(*window);
}

#ifndef GAMEOPERATOR_H
#define GAMEOPERATOR_H
// SFML LIBRARIES //
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
// LIBRARIES //
#include <vector>
// CLASSES //
#include "1_AnimationOperator.h"
#include "1_MapOperator.h"
#include "1_PlayerOperator.h"
#include "2_EnemiesOperator.h"
#include "3_DamageObjects.h"
#include "GUIOperator.h"


class GameOperator {
private:
    // WINDOW VARIABLES //
    int res_x, res_y;
    sf::RenderWindow *window;
    // SCALES //
    float scale;
    float MOscale;
    float DOscale;
    float POscale;
    float EOscale;
    //PLAYER VARIABLES //
    int playerMaxHealth;
    int playerHealth;
    float playerSpeed;
    float playerAnimationSpeed;
    int shootDelay;
    sf::Vector2f playerSpawnPoint;
    // ZOMBIES VARIABLES //
    std::vector <sf::Vector2f> spawnPoints;
    int zombieHealth;
    int zombieSpeed;
    int zombieDamage;
    int zombieStunTime;
    // BULLET VARIABLES //
    float bulletRange;
    float bulletSpeed;

    sf::Event event;
    sf::View cameraOnPlayer;
    sf::View defaultView;
    //std::vector <sf::CircleShape> zombies;
    sf::Vector2f playerPosition;
    sf::Clock clock;
    sf::Time shoot;

public:
    MapOperator MO;
    DamageObjects DO;
    PlayerOperator PO;
    EnemiesOperator EO;
    GUIOperator GO;

    GameOperator(int res_x, int res_y, sf::RenderWindow *window,
                 float scale, float MOscale, float DOscale, float POscale, float EOscale,
                 int playerMaxHealth, float playerSpeed, float playerAnimationSpeed, int shootDelay, sf::Vector2f playerSpawnPoint,
                 std::vector <sf::Vector2f> spawnPoints, int zombieHealth, int zombieSpeed, int zombieDamage, int zombieStunTime,
                 float bulletRange, int bulletSpeed);
    void events(int scene);
    void updates(float deltaTime);
    void setView();
    void cameraOnPlayerUpdate();
    void draw();
};

#endif // GAMEOPERATOR_H

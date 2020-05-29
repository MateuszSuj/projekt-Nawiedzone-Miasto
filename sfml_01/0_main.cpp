// SFML LIBRARIES //
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
// LIBRARIES //
#include <iostream>
#include <vector>
#include <string>
// CLASSES //
#include "1_AnimationOperator.h"
#include "1_MapOperator.h"
#include "1_PlayerOperator.h"
#include "2_EnemiesOperator.h"
#include "1_GameOperator.h"
#include "LevelOperator.h"

// LINKS //
//https://opengameart.org/content/roguelikerpg-pack-1700-tiles

// MAIN //
int main() {

        // SETTINGS - VARIABLES //

        int res_x = 1600; // x variable of window
        int res_y = 900; // y variable of window
        float scale = 1; //scale of all objects
        int framerate = 300;
        float MOscale = 3; // map objects scale
        float DOscale = 3; // damage objects scale
        float POscale = 3; // player scale
        float EOscale = 3; // enemies objects scale

        // PLAYER VARIABLES //
        int playerMaxHealth = 100; // maximum health of player
        float playerSpeed = 3; // movement speed
        float playerAnimationSpeed = 2; //how fast animation is displayed
        int shootDelay = 200; // time between player shoots in miliseconds
        sf::Vector2f playerSpawnPoint = {240*scale, 240*scale};

        // ZOMBIES VARIABLES //
        int zombieHealth = 30;
        int zombieSpeed = 200;
        int zombieDamage = 10;
        int zombieStunTime = framerate;
        std::vector <sf::Vector2f> spawnPoints = // spawn points of zombies
        {
            sf::Vector2f(240*scale,0*scale),
            sf::Vector2f(0*scale,240*scale),
            sf::Vector2f(480*scale,240*scale),
            sf::Vector2f(240*scale,480*scale)
        };

        // BULLETS VARIABLES //
        float bulletRange = 0.2;
        float bulletSpeed = 1000;

    // RENDER WINDOW //
    sf::RenderWindow window(sf::VideoMode(res_x, res_y), "THE GAME");// , sf::Style::Fullscreen
    window.setFramerateLimit(framerate); //set framerate

    // GAME OPERATOR //
    GameOperator GO(res_x, res_y, &window,
                    scale, MOscale, DOscale, POscale, EOscale,
                    playerMaxHealth, playerSpeed, playerAnimationSpeed, shootDelay, playerSpawnPoint,
                    spawnPoints, zombieHealth, zombieSpeed, zombieDamage, zombieStunTime,
                    bulletRange, bulletSpeed);

    // VARIABLES IN MAIN //
    LevelOperator LO;
    int stage = 0;
    bool once = false;
    int scene = 0;
    sf::Vector2f scaleToRes = {(float)res_x/1920, (float)res_y/1080 };

    // BEFORE WHILE VARIABLES //
    sf::Clock delayLevelClock; //delay between levels
    sf::Clock deltaTimeClock; //deltaTime Offset
    sf::Clock theEndClock;
    float delayLevel = 0.0f;
    float deltaTime = 0.0f; // Delta time describes the time difference between the previous frame that was drawn and the current frame.
    float theEnd = 0.0f;
    // BEFORE GAME LOAD //
    GO.MO.load(); // load map
    GO.PO.collisionLoad(GO.MO.showLayer(2)); // load collision layer
    while (window.isOpen()) {
        if(scene == 0){
            GO.events(scene);
            sf::Text playText;
            sf::Font font;
            font.loadFromFile("fonts/font.ttf");
            playText.setFont(font);
            playText.setCharacterSize(200 * scaleToRes.x);
            playText.setOrigin(300 * scaleToRes.x, 150 * scaleToRes.x);
            playText.setPosition(res_x/2, res_y/2);
            playText.setString("PLAY");
            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
            sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
            if(worldPos.x > 660 * scaleToRes.x && worldPos.x < 1246 * scaleToRes.x && worldPos.y > 450 * scaleToRes.y && worldPos.y < 590 * scaleToRes.y){
                playText.setFillColor(sf::Color::Red);
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) scene = 1;
            }
            window.clear(sf::Color::Black);
            window.draw(playText);
            window.display();
        }
        if(scene == 1){
            if(GO.PO.getHp() <= 0){ scene = 2; theEndClock.restart(); }
            deltaTime = deltaTimeClock.restart().asSeconds(); // restart delta time clock
            GO.events(scene);

            // PLAYER MOVEMENT //
            sf::Vector2f direction = {0, 0};
                 if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&  sf::Keyboard::isKeyPressed(sf::Keyboard::D)) direction = sf::Vector2f(deltaTime *  70, -deltaTime *  70);
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&  sf::Keyboard::isKeyPressed(sf::Keyboard::A)) direction = sf::Vector2f(-deltaTime *  70, -deltaTime *  70);
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&  sf::Keyboard::isKeyPressed(sf::Keyboard::D)) direction = sf::Vector2f(deltaTime *  70, deltaTime *  70);
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&  sf::Keyboard::isKeyPressed(sf::Keyboard::A)) direction = sf::Vector2f(-deltaTime *  70, deltaTime *  70);
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S)) direction = sf::Vector2f(0.f, -deltaTime * 100);
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::W)) direction = sf::Vector2f(0.f, deltaTime *  100);
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)) direction = sf::Vector2f(-deltaTime * 100, 0.f);
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A)) direction = sf::Vector2f(deltaTime *  100, 0.f);
            GO.PO.movement(direction);
            GO.updates(deltaTime);
            if(GO.EO.checkLevelEnd()){
                if(once == false) { delayLevelClock.restart(); once = true; }
                delayLevel = delayLevelClock.getElapsedTime().asMilliseconds();
                if(delayLevel > 20){
                    once = false;
                    std::cout << "LEVEL " << stage+1 << std::endl << "Zombies to spawn: " << LO.levels[stage].waves * LO.levels[stage].zombieAmount << " in " << LO.levels[stage].waves << " waves" << std::endl;
                    if(LO.levels[stage].waves > 0) { GO.EO.spawn(LO.levels[stage].zombieAmount); LO.levels[stage].waves--; }
                    if(LO.levels[stage].waves == 0) {stage++; GO.GO.addLevel(std::to_string(stage)); }
                }
            }
            GO.cameraOnPlayerUpdate();
            GO.draw();
            window.display();
        }
        if(scene == 2){
            theEnd = theEndClock.getElapsedTime().asSeconds();
            if(theEnd > 3) scene = 0;
            GO.events(scene);
            GO.setView();
            sf::Text theEndText;
            sf::Font font;
            font.loadFromFile("fonts/font.ttf");
            theEndText.setFont(font);
            theEndText.setCharacterSize(200 * scaleToRes.x);
            theEndText.setOrigin(1000 * scaleToRes.x, 350 * scaleToRes.x);
            theEndText.setPosition(res_x/2, res_y/2);
            theEndText.setString("THE END");
            window.clear(sf::Color::Black);
            window.draw(theEndText);
            window.display();
        }
    }
    return 0;
}

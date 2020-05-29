#include "GUIOperator.h"
#include <iostream>

GUIOperator::GUIOperator(sf::Vector2i res) {
    font.loadFromFile("fonts/font.ttf");
    this->res = res;

    sf::Text temp;
    texts.emplace_back(temp);
    texts.emplace_back(temp);
}

void GUIOperator::updatePlayerPosition(sf::Vector2f playerPosition){
    this->playerPosition = playerPosition;
}

void GUIOperator::addHP(std::string text){
    sf::Text temp;
    temp.setFont(font);
    temp.setCharacterSize(100);
    temp.setPosition(playerPosition.x + 0.34*res.x, playerPosition.y + 0.34*res.y);
    temp.setString(text);
    texts[0] = temp;
}

void GUIOperator::addLevel(std::string text){
    sf::Text temp;
    temp.setFont(font);
    temp.setCharacterSize(200);
    temp.setPosition(-150, -300);
    temp.setString("LEVEL: " + text);
    texts[1] = temp;
}

void GUIOperator::drawGUI(sf::RenderWindow &window){
    for(int i = 0; i < (int)texts.size(); i++){
        window.draw(texts[i]);
    }
}

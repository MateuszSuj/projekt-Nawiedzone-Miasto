#ifndef GUI
#define GUI

#include <sfml\Graphics.hpp>

class GUIOperator {
private:
    // Declare and load a font
    sf::Font font;
    // Create a text
    std::vector <sf::Text> texts;
    sf::Vector2f playerPosition;
    sf::Vector2i res;
public:
    GUIOperator(sf::Vector2i res);
    void updatePlayerPosition(sf::Vector2f playerPosition);
    void addHP(std::string text);
    void addLevel(std::string text);
    void drawGUI(sf::RenderWindow &window);
};

#endif // GUI

#ifndef MAPOPERATOR_H
#define MAPOPERATOR_H

#include <sfml\Graphics.hpp>

#include <vector>
#include <fstream>

class MapOperator {
private:
    std::vector <sf::Sprite> mapLayer1;
    std::vector <sf::Sprite> mapLayer2;
    std::vector <sf::Sprite> mapLayer3;
    float scale;
    sf::Texture mapTexture;
public:
    MapOperator(float scale);
    void load();
    std::vector <sf::Sprite> showLayer(int number);
    void drawLayer(int layer, sf::RenderWindow &window);
};

#endif // MAPLOADER_H

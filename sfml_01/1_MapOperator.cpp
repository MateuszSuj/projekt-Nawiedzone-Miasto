#include "1_MapOperator.h"

MapOperator::MapOperator(float scale){
    // GET VARIABLES //
    this->scale = scale;
    // TEXTURES //
    mapTexture.loadFromFile("pics/Sheet.png");
}

void MapOperator::load(){
    std::fstream mapFile;
    int map_x, map_y;
    int sheetPos_x, sheetPos_y;
    mapFile.open ("maps/mapDefault.txt", std::ios::in);


    if( mapFile.good() == true )
    {
        mapFile >> map_x >> map_y; // taking size of the map
        for(int i = 0; i < map_x * map_y; i++){
            mapFile >> sheetPos_x >> sheetPos_y;
            sf::Sprite temp(mapTexture, sf::IntRect(0+17*sheetPos_x,0+17*sheetPos_y,16,16));
            temp.setPosition((i % map_x)*16*scale, (i/map_x)*16*scale);
            temp.setScale(scale,scale);
            mapLayer1.emplace_back(temp);
        }

        for(int i = 0; i < map_x * map_y; i++){
            mapFile >> sheetPos_x >> sheetPos_y;
            if(sheetPos_x != 0 && sheetPos_y !=5){
                sf::Sprite temp(mapTexture, sf::IntRect(0+17*sheetPos_x,0+17*sheetPos_y,16,16));
                //temp.setOrigin(8,8);
                temp.setPosition((i % map_x)*16*scale, (i/map_x)*16*scale);
                temp.setScale(scale,scale);
                mapLayer2.emplace_back(temp);
            }
        }

        for(int i = 0; i < map_x * map_y; i++){
            mapFile >> sheetPos_x >> sheetPos_y;
            if(sheetPos_x != 0 && sheetPos_y !=5){
                sf::Sprite temp(mapTexture, sf::IntRect(0+17*sheetPos_x,0+17*sheetPos_y,16,16));
                temp.setPosition((i % map_x)*16*scale, (i/map_x)*16*scale);
                temp.setScale(scale,scale);
                mapLayer3.emplace_back(temp);
            }
        }
    } //else std::cout << "mapFile error!" << std::endl;
    mapFile.close();
}

std::vector <sf::Sprite> MapOperator::showLayer(int number){
    if(number == 1) return mapLayer1;
    else if(number == 2) return mapLayer2;
    else if(number == 3) return mapLayer3;
    else return mapLayer2;

}

void MapOperator::drawLayer(int layer, sf::RenderWindow &window){
    // LAYERMAP1 - Ground //
    if(layer == 1) for(int i = 0; i < (int)mapLayer1.size(); i++) window.draw(mapLayer1[i]);

    // LAYERMAP2 - Furnitures //
    else if(layer == 2) for(int i = 0; i < (int)mapLayer2.size(); i++) window.draw(mapLayer2[i]);

    // LAYERMAP3 - Roof //
    else if(layer == 3) for(int i = 0; i < (int)mapLayer3.size(); i++) window.draw(mapLayer3[i]);
}

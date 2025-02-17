#include "1_AnimationOperator.h"

Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime){
    // GET VARIABLES //
    this->imageCount = imageCount;
    this->switchTime = switchTime;
    // SET VARIABLES //
    totalTime = 0.0f;
    currentImage.x = 0;

    uvRect.width = texture->getSize().x / float(imageCount.x);
    uvRect.height = texture->getSize().y / float(imageCount.y);
}


void Animation::Update(int row, float deltaTime){
    currentImage.y = row;
    totalTime += deltaTime;

    if(totalTime >= switchTime){
        totalTime -= switchTime;
        currentImage.x++;
        if(currentImage.x >= imageCount.x){
            currentImage.x = 0;
        }
    }

    uvRect.left = currentImage.x * uvRect.width;
    uvRect.top = currentImage.y * uvRect.height;
}

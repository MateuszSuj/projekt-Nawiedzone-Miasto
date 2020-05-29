#ifndef ANIMATION_H
#define ANIMATION_H

#include <sfml\Graphics.hpp>

class Animation
{
public:
    Animation(sf::Texture* texture, sf::Vector2u ImageCount, float switchTime);

    sf::IntRect uvRect;

    void Update(int row, float deltaTime);

private:
    sf::Vector2u imageCount;
    sf::Vector2u currentImage;

    float totalTime;
    float switchTime;
};

#endif // ANIMATION_H

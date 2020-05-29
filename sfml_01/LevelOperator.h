#ifndef LEVELS_H
#define LEVELS_H

#include <sfml\Graphics.hpp>

struct Level{
    int waves;
    int zombieAmount;
};

class LevelOperator {
public:
    std::vector <Level> levels;
    LevelOperator();
};
#endif // LEVELS_H

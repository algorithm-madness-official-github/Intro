#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
class GameOfLifeSim{
public:
    GameOfLifeSim(unsigned x, unsigned y);
    void draw(sf::RenderWindow& window);

private:
    bool** m_arr;
    unsigned sizeX, sizeY;
    void update();

    sf::Clock timer;
};
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <string>

class CodeAnimation{
public:
    CodeAnimation(std::string typed, std::string to_type);

    void draw(sf::RenderWindow& window, std::string ep, std::string title_str);

private:
    std::string m_typed, m_to_type;
    sf::Font m_font;
    unsigned iter = 0;

    sf::Clock timer;
    sf::Image bg;
};
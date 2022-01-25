#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <cstdlib>
#include <ctime>

class TriangleAnimation{
public:
    TriangleAnimation();

    void draw(sf::RenderWindow& window);

private:
    sf::Font m_font;
    sf::Vector2f m_point[3];
    float m_radius;
    float m_angle_a, m_angle_b, m_angle_c;

    void update();
    float calArea(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c);
    float calAngle(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c);
    void updatePoints(float angle_a, float angle_b, float angle_c);
};
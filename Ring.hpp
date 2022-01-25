#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

const float pi = 3.14159265358f;

class Ring{
private:
    float m_radius, m_a, m_b;
    sf::Color m_color;
    float m_x, m_y;

public:
    Ring(float radius) : m_radius(radius), m_a(0), m_b(2 * pi){}
    Ring(float radius, float a, float b) : m_radius(radius), m_a(a), m_b(b){}

    float x() const {return m_x;}
    float y() const {return m_x;}
    float& x(){return m_x;}
    float& y(){return m_x;}

    void setPosition(float x, float y){m_x = x; m_y = y;}
    void setColor(sf::Color color){m_color = color;}

    void draw(sf::RenderWindow& window);

};
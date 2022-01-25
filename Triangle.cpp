#include "Triangle.hpp"
#include "Ring.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>

float TriangleAnimation::calArea(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c){
    float x1 = b.x - a.x, x2 = c.x - a.x, y1 = b.y - a.y, y2 = c.y - a.y;
    return std::fabs(x1 * y2 - y1 * x2) / 2;
}

float TriangleAnimation::calAngle(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c){
    float x1 = b.x - a.x, x2 = c.x - a.x, y1 = b.y - a.y, y2 = c.y - a.y;
    return std::fabs(std::atan2(x2, y2) - atan2(x1, y1)) / M_PI * 180;
}

TriangleAnimation::TriangleAnimation(){
    srand(time(NULL));
    m_angle_a = ((float)rand()) / (float)RAND_MAX * 2 * M_PI;
    m_angle_b = ((float)rand()) / (float)RAND_MAX * 2 * M_PI;
    m_angle_c = ((float)rand()) / (float)RAND_MAX * 2 * M_PI;

    m_radius = 200;

    m_font.loadFromFile("Pulang.ttf");

    updatePoints(m_angle_a, m_angle_b, m_angle_c);
}

void TriangleAnimation::updatePoints(float angle_a, float angle_b, float angle_c){
    m_point[0].x = std::cos(angle_a) * m_radius;
    m_point[0].y = std::sin(angle_a) * m_radius;
    m_point[1].x = std::cos(angle_b) * m_radius;
    m_point[1].y = std::sin(angle_b) * m_radius;
    m_point[2].x = std::cos(angle_c) * m_radius;
    m_point[2].y = std::sin(angle_c) * m_radius;
}

void TriangleAnimation::draw(sf::RenderWindow& window){
    updatePoints(m_angle_a, m_angle_b, m_angle_c);

    window.clear();
    sf::Vector2f sizes((float)window.getSize().x / 2, (float)window.getSize().y / 2);

    Ring ring(200);
    ring.setPosition(sizes.x, sizes.y);
    ring.setColor(sf::Color::Green);

    ring.draw(window);

    for(unsigned i = 0; i < 3; i++){
        sf::CircleShape point(4);
        point.setFillColor(sf::Color::Blue);
        point.setOrigin(4, 4);
        point.setOutlineColor(sf::Color::Black);
        point.setOutlineThickness(1);
        point.setPosition(m_point[i].x + sizes.x, m_point[i].y + sizes.y);

        window.draw(point);

        sf::VertexArray line(sf::Lines, 2);
        line[0] = sf::Vertex(sf::Vector2f(m_point[i].x + sizes.x, m_point[i].y + sizes.y), sf::Color::White);

        if(i < 2)
            line[1] =sf::Vertex(sf::Vector2f(m_point[i+1].x + sizes.x, m_point[i+1].y + sizes.y), sf::Color::White);
        else
            line[1] = sf::Vertex(sf::Vector2f(m_point[0].x + sizes.x, m_point[0].y + sizes.y), sf::Color::White);
        
        window.draw(line);
    }

    float a = std::atan2(m_point[0].y - m_point[1].y, m_point[0].x - m_point[1].x) - pi;
    float b = std::atan2(m_point[0].y - m_point[2].y, m_point[0].x - m_point[2].x) - pi;
    float ma = std::min(a, b), mb = std::max(a, b);

    Ring angle(50, ma, mb);
    angle.setColor(sf::Color::White);
    angle.setPosition(m_point[0].x + sizes.x, m_point[0].y + sizes.y);
    angle.draw(window);

    sf::Text text1("a", m_font, 20);
    text1.setFillColor(sf::Color::White);
    text1.setString("a");
    text1.setPosition(m_point[0].x + sizes.x, m_point[0].y + sizes.y);
    window.draw(text1);
    text1.setString("b");
    text1.setPosition(m_point[1].x + sizes.x, m_point[1].y + sizes.y);
    window.draw(text1);
    text1.setString("c");
    text1.setPosition(m_point[2].x + sizes.x, m_point[2].y + sizes.y);
    window.draw(text1);

    sf::Text text2("Area of the triangle: " + std::to_string(calArea(m_point[0], m_point[1], m_point[2])), m_font, 30);
    text2.setOrigin(text2.getLocalBounds().width / 2, text2.getLocalBounds().height / 2);
    text2.setFillColor(sf::Color::White);
    text2.setPosition(sizes.x, sizes.y + m_radius + 100);
    window.draw(text2);

    sf::Text text3("Angle BAC: " + std::to_string(calAngle(m_point[0], m_point[1], m_point[2])) + " [deg]", m_font, 30);
    text3.setOrigin(text3.getLocalBounds().width / 2, text3.getLocalBounds().height / 2);
    text3.setFillColor(sf::Color::White);
    text3.setPosition(sizes.x, sizes.y + m_radius + text3.getLocalBounds().height + 120);
    window.draw(text3);

    window.display();

    m_angle_a += 0.0004;
    m_angle_b -= 0.0008;
    m_angle_c += 0.0012;
}

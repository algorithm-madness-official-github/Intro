#include "Ring.hpp"
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <iostream>

void Ring::draw(sf::RenderWindow &window){
    float step = (m_b - m_a) / 100;
    sf::VertexArray v_arr(sf::LineStrip, 360);
    unsigned t = 0;

    if(m_b == 0)
        return;

    for(float i = m_a; i <= m_b; i += step){
        sf::Vertex v(sf::Vector2f(std::cos(i) * m_radius + m_x, std::sin(i) * m_radius + m_y), m_color);
        v_arr[t] = v;
        t++;
    }

    if(m_a == 0 && m_b == 2 * pi)
        v_arr[t] = v_arr[0];
    else
        t--;

    v_arr.resize(t + 1);

    window.draw(v_arr);
}

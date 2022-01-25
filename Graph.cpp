#include "Graph.hpp"
#include "Ring.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>

GraphAnimation::GraphAnimation(){
    srand(time(NULL));

    dfs();

    v_curr_vertices.resize(27);

    for(unsigned i = 0; i < 27; i++){
        do{
            m_move_coefficients[i] = -0.004 + (float)rand() / (float)RAND_MAX * 0.008;
        }while(std::fabs(m_move_coefficients[i]) < 1e-5);
        m_move_multipliers[i] = 0;
    }
}

void GraphAnimation::dfs(unsigned v){
    m_visited[v] = true;
    v_path.push_back(v);
    
    for(auto& p : v_edges[v]){
        if(m_visited[p] == 0){
            dfs(p);
        }
    }
    return;
}

void GraphAnimation::draw(sf::RenderWindow &window){
    unsigned i = 0;
    for(auto& v : v_vertices){
        m_move_multipliers[i] += m_move_coefficients[i];
        sf::CircleShape circle(3);
        auto pos = sf::Vector2f(std::cos(m_move_multipliers[i]) * 50 + v.x, std::sin(m_move_multipliers[i]) * 50 + v.y);
        circle.setOrigin(3, 3);
        circle.setPosition(pos);
        circle.setFillColor(sf::Color::White);
        window.draw(circle);

        Ring ring(7);
        ring.setColor(sf::Color::White);
        ring.setPosition(pos.x, pos.y);
        ring.draw(window);

        v_curr_vertices[i] = pos;

        i++;
    }

    for(auto& edge : v_edges){
        unsigned i = edge[0];
        auto a = v_vertices[i];
        auto start = v_curr_vertices[i];

        for(unsigned j : edge){
            if(i != j){
                sf::VertexArray v_arr(sf::Lines, 2);
                v_arr[0] = sf::Vertex(start, sf::Color::White);
                v_arr[1] = sf::Vertex(v_curr_vertices[j], sf::Color::White);

                window.draw(v_arr);
            }
        }
    }

    unsigned tres = 200;

    if(timer.getElapsedTime().asMilliseconds() < tres){
        float mul = (float)timer.getElapsedTime().asMilliseconds() / tres;
        unsigned i = v_path[m_current] , j = v_path[m_current + 1];
        sf::Vector2f pos((v_curr_vertices[i].x - v_curr_vertices[j].x) * mul, (v_curr_vertices[i].y - v_curr_vertices[j].y) * mul);

        sf::VertexArray v_arr(sf::Lines, 2);
        v_arr[0] = sf::Vertex(v_curr_vertices[i], sf::Color::Green);
        v_arr[1] = sf::Vertex(sf::Vector2f(v_curr_vertices[i].x - pos.x, v_curr_vertices[i].y - pos.y), sf::Color::Green);

        window.draw(v_arr);

        Ring ring(7);
        ring.setPosition(v_curr_vertices[i].x, v_curr_vertices[i].y);
        ring.setColor(sf::Color::Green);
        ring.draw(window);
    }else if(timer.getElapsedTime().asMilliseconds() < tres * 2) {
        float mul = ( (float)timer.getElapsedTime().asMilliseconds() - tres) / tres;
        unsigned i = v_path[m_current] , j = v_path[m_current + 1];

        sf::VertexArray v_arr(sf::Lines, 2);
        v_arr[0] = sf::Vertex(v_curr_vertices[i], sf::Color::Green);
        v_arr[1] = sf::Vertex(sf::Vector2f(v_curr_vertices[j].x, v_curr_vertices[j].y), sf::Color::Green);
        
        window.draw(v_arr);

        Ring ring(7, 0, 2 * pi * mul);
        ring.setPosition(v_curr_vertices[j].x, v_curr_vertices[j].y);
        ring.setColor(sf::Color::Green);
        ring.draw(window);
    }else {
        timer.restart();
        m_current++;
    }
}
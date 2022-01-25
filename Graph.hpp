#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
class GraphAnimation{
public:
    GraphAnimation();

    void draw(sf::RenderWindow& window);

private:
    void dfs(unsigned v = 0);
    std::vector<unsigned> v_path;

    sf::Clock timer;
    unsigned m_current = 0;

    std::vector<sf::Vector2f> v_vertices{
        sf::Vector2f(300, 500), // A 0      starting point
        sf::Vector2f(420, 400), // B 1
        sf::Vector2f(455, 556), // C 2
        sf::Vector2f(389, 671), // D 3
        sf::Vector2f(639, 767), // E 4
        sf::Vector2f(764, 607), // F 5
        sf::Vector2f(636, 460), // G 6
        sf::Vector2f(956, 376), // H 7
        sf::Vector2f(1017, 514), // I 8
        sf::Vector2f(1087, 653), // J 9
        sf::Vector2f(1223, 594), // K 10
        sf::Vector2f(1265, 460), // L 11
        sf::Vector2f(1300, 721), // M 12
        sf::Vector2f(927, 731), // N 13
        sf::Vector2f(1420, 577), // O 14
        sf::Vector2f(712, 267), // P 15
        sf::Vector2f(959, 146), // Q 16
        sf::Vector2f(830, 834), // R 17
        sf::Vector2f(573, 920), // S 18
        sf::Vector2f(773, 739), // T 19
        sf::Vector2f(1153, 746), // U 20
        sf::Vector2f(1231, 844), // V 21
        sf::Vector2f(1174, 359), // W 22
        sf::Vector2f(1269, 211), // Z 23
        sf::Vector2f(523, 237), // A1 24
        sf::Vector2f(683, 130), // B1 25
        sf::Vector2f(832, 418) // C1 26
    };

    std::vector<sf::Vector2f> v_curr_vertices;

    float m_move_coefficients[27]{0};
    float m_move_multipliers[27]{0};
    bool m_visited[27]{0};

    std::vector<std::vector<unsigned> > v_edges{
        {0, 1, 2},
        {1, 3, 24},
        {2, 1, 4, 6, 7},
        {3, 0},
        {4, 3, 5, 6, 18, 19},
        {5, 8, 12, 19},
        {6, 1, 24, 26},
        {7, 8, 15, 16},
        {8, 10},
        {9, 10, 11},
        {10, 7, 12, 14},
        {11, 14},
        {12, 14},
        {13, 8, 9, 21},
        {14, 14},
        {15, 16, 26},
        {16, 25},
        {17, 4, 13, 20},
        {18, 3, 17},
        {19, 17},
        {20, 9, 12},
        {21, 10, 20},
        {22, 8, 11, 16},
        {23, 22, 16},
        {24, 15, 25},
        {25, 15},
        {26, 5, 7}
    };
};
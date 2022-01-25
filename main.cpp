#include "CodeTyping.hpp"
#include "Fluid.hpp"
#include "GameOfLife.hpp"
#include "Graph.hpp"
#include "Triangle.hpp"
#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Cursor.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <stdexcept>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Intro", sf::Style::Fullscreen);
    auto sizes = window.getSize();

    sf::Clock timer;

    window.setMouseCursorVisible(false);

    TriangleAnimation triangle;
    GraphAnimation graph;
    FluidSimulation fluid(3, 0, 0, {{sf::Color(0, 0, 0), 0}, {sf::Color(255, 0, 0), 0.5}, {sf::Color(0, 0, 255), 1}});
    GameOfLifeSim GameOfLife(sizes.x, sizes.y);
    CodeAnimation code("float Q_rsqrt( float number )\n{\n\tlong i;\n\tfloat x2, y;\n\t", "const float threehalfs = 1.5F;\n\n\tx2 = number * 0.5F;\n\ty  = number;\n\ti  = * ( long * ) &y;                       // evil floating point bit level hacking\n\ti  = 0x5f3759df - ( i >> 1 );               // what the fuck? \n\ty  = * ( float * ) &i;\n\ty  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration\n//	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed\n\n\treturn y;\n}");

    sf::Music music;
    music.openFromFile("sound.wav");
    music.play();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::KeyPressed){
                switch (event.key.code) {
                    case sf::Keyboard::Escape: window.close(); break;
                }
            }
        }
        window.clear();

        if(timer.getElapsedTime().asMilliseconds() < 3000)
            triangle.draw(window);
        else if(timer.getElapsedTime().asMilliseconds() < 6000)
            graph.draw(window);
        else if(timer.getElapsedTime().asMilliseconds() < 12000)
            fluid.draw(window);
        else if(timer.getElapsedTime().asMilliseconds() < 18000)
            GameOfLife.draw(window);
        else
            code.draw(window, "Ep. 0.0: ", "Introdution to world of computer science.\nTime and space complexity.");

        if(music.getStatus() == sf::Music::Stopped)
            window.close();

        window.display();
    }

    return EXIT_SUCCESS;
}

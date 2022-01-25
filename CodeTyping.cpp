#include "CodeTyping.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>

CodeAnimation::CodeAnimation(std::string typed, std::string to_type) : m_typed(typed), m_to_type(to_type){
    m_font.loadFromFile("emulogic.ttf");
    bg.loadFromFile("julia-set-2.png");
}

void CodeAnimation::draw(sf::RenderWindow &window, std::string ep, std::string title_str){
    auto sizes = window.getSize();
        unsigned tres = 36000;

    if(timer.getElapsedTime().asMilliseconds() % 10 == 0 && timer.getElapsedTime().asMilliseconds() < 27000)
        iter++;
    
    std::string str = m_to_type.substr(0, iter);

    sf::Text text(m_typed + str, m_font, 25);
    text.setFillColor(sf::Color::Green);
    text.setPosition(100, 100);

    if(timer.getElapsedTime().asMilliseconds() > 24000)
        text.move(0, -((float)timer.getElapsedTime().asMilliseconds() - 24000) / 2);

    window.draw(text);

    sf::Texture texture;
    texture.loadFromImage(bg);

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setOrigin(400, 150);

    if(sizes.y - ((float)timer.getElapsedTime().asMilliseconds() - 24000) / 2 > 0)
        sprite.setPosition(0, sizes.y - ((float)timer.getElapsedTime().asMilliseconds() - 24000) / 2);
    else
        sprite.setPosition(0, 0);
    
    if(timer.getElapsedTime().asMilliseconds() < 36000)
        window.draw(sprite);

    if(timer.getElapsedTime().asMilliseconds() > 27000){
        sf::VertexArray channel_banner(sf::Quads, 4);
        channel_banner[0] = sf::Vertex(sf::Vector2f(0, 300), sf::Color(192, 192, 192, 150));
        channel_banner[1] = sf::Vertex(sf::Vector2f(0, 500), sf::Color(192, 192, 192, 150));
        channel_banner[2] = sf::Vertex(sf::Vector2f(0, 500), sf::Color(192, 192, 192, 150));
        channel_banner[3] = sf::Vertex(sf::Vector2f(0, 300), sf::Color(192, 192, 192, 150));

        sf::Font font;
        font.loadFromFile("Pulang.ttf");

        sf::Text channel("Algorithm Madness Channel Presents: ", font, 50);
        channel.setFillColor(sf::Color(50, 50, 50, 175));
        channel.setPosition(-channel.getLocalBounds().width - 200, 400 - (float)channel.getLocalBounds().height / 2);

        if(timer.getElapsedTime().asMilliseconds() < 27600){
            channel_banner[2] = sf::Vertex(sf::Vector2f((timer.getElapsedTime().asMilliseconds() - 27200) * 2, 500), sf::Color(192, 192, 192, 150));
            channel_banner[3] = sf::Vertex(sf::Vector2f((timer.getElapsedTime().asMilliseconds() - 27000) * 2, 300), sf::Color(192, 192, 192, 150));
            channel.setPosition(timer.getElapsedTime().asMilliseconds() - 27700, 400 - (float)channel.getLocalBounds().height / 2);
        }else{
            channel_banner[2] = sf::Vertex(sf::Vector2f(900, 500), sf::Color(192, 192, 192, 150));
            channel_banner[3] = sf::Vertex(sf::Vector2f(1100, 300), sf::Color(192, 192, 192, 150));
            channel.setPosition(100, 400 - (float)channel.getLocalBounds().height / 2);
        }

        sf::VertexArray epizode(sf::Quads, 4);

        epizode[0] = sf::Vertex(sf::Vector2f(sizes.x, 450), sf::Color(200, 0, 0, 175));
        epizode[1] = sf::Vertex(sf::Vector2f(sizes.x, 550), sf::Color(200, 0, 0, 175));
        epizode[2] = sf::Vertex(sf::Vector2f(sizes.x, 550), sf::Color(200, 0, 0, 175));
        epizode[3] = sf::Vertex(sf::Vector2f(sizes.x, 450), sf::Color(200, 0, 0, 175));

        sf::Text epizode_num(ep, m_font, 40);
        epizode_num.setPosition(sizes.x, 500 - (float)channel.getLocalBounds().height / 2);
        epizode_num.setFillColor(sf::Color(255, 255, 255, 200));

        if(timer.getElapsedTime().asMilliseconds() > 27800 && timer.getElapsedTime().asMilliseconds() < 28400){
            epizode[2] = sf::Vertex(sf::Vector2f(sizes.x - (sizes.x - 900) * (float(timer.getElapsedTime().asMilliseconds() - 27800) / 600), 550), sf::Color(200, 0, 0, 175));
            epizode[3] = sf::Vertex(sf::Vector2f(sizes.x - (sizes.x - 1000) * (float(timer.getElapsedTime().asMilliseconds() - 27800) / 600), 450), sf::Color(200, 0, 0, 175));
            epizode_num.setPosition(sizes.x - (sizes.x - 1100) * (float(timer.getElapsedTime().asMilliseconds() - 27800) / 600), 500 - (float)channel.getLocalBounds().height / 2);
        }else if(timer.getElapsedTime().asMilliseconds() > 27800){
            epizode[2] = sf::Vertex(sf::Vector2f(900, 550), sf::Color(200, 0, 0, 175));
            epizode[3] = sf::Vertex(sf::Vector2f(1000, 450), sf::Color(200, 0, 0, 175));
            epizode_num.setPosition(1100, 500 - (float)channel.getLocalBounds().height / 2);
        }

        sf::VertexArray title(sf::Quads, 4);
        title[0] = sf::Vertex(sf::Vector2f(0, 1000), sf::Color(255, 100, 0, 200));
        title[1] = sf::Vertex(sf::Vector2f(0, 1000), sf::Color(255, 100, 0, 200));
        title[2] = sf::Vertex(sf::Vector2f(1200, 1000), sf::Color(255, 100, 0, 200));
        title[3] = sf::Vertex(sf::Vector2f(1200, 1000), sf::Color(255, 100, 0, 200));

        if(timer.getElapsedTime().asMilliseconds() > 28600 && timer.getElapsedTime().asMilliseconds() < 29100){
            title[0] = sf::Vertex(sf::Vector2f(0, 1000 - 150 * (float(timer.getElapsedTime().asMilliseconds() - 28600) / 500)), sf::Color(255, 100, 0, 200));
            title[3] = sf::Vertex(sf::Vector2f(1200, 1000 - 150 * (float(timer.getElapsedTime().asMilliseconds() - 28600) / 500)), sf::Color(255, 100, 0, 200));
            iter = 0;
        }else if(timer.getElapsedTime().asMilliseconds() > 29100){
            title[0] = sf::Vertex(sf::Vector2f(0, 850), sf::Color(255, 100, 0, 200));
            title[3] = sf::Vertex(sf::Vector2f(1200, 850), sf::Color(255, 100, 0, 200));
        }

        if(timer.getElapsedTime().asMilliseconds() < tres){
            window.draw(channel_banner);
            window.draw(channel);
            window.draw(epizode);
            window.draw(epizode_num);
            window.draw(title);
        }

        if(timer.getElapsedTime().asMilliseconds() > 29500){

            if(timer.getElapsedTime().asMilliseconds() % 5 == 0)
                iter++;

            str = title_str.substr(0, iter);
            sf::Text text2(str, m_font, 25);

            text2.setFillColor(sf::Color::Black);
            text2.setPosition(50, 925 - (float)text2.getLocalBounds().height / 2);
            
            if(timer.getElapsedTime().asMilliseconds() < tres)
                window.draw(text2);
        }
        
        if(timer.getElapsedTime().asMilliseconds() > tres){
            sprite.move(0, -(timer.getElapsedTime().asMilliseconds() - tres));
            channel.move(timer.getElapsedTime().asMilliseconds() - tres, 0);

            channel_banner[0].position.x += timer.getElapsedTime().asMilliseconds() - tres;
            channel_banner[1].position.x += timer.getElapsedTime().asMilliseconds() - tres;
            channel_banner[2].position.x += timer.getElapsedTime().asMilliseconds() - tres;
            channel_banner[3].position.x += timer.getElapsedTime().asMilliseconds() - tres;

            epizode_num.move(-(timer.getElapsedTime().asMilliseconds() - tres), 0);

            epizode[0].position.x -= timer.getElapsedTime().asMilliseconds() - tres;
            epizode[1].position.x -= timer.getElapsedTime().asMilliseconds() - tres;
            epizode[2].position.x -= timer.getElapsedTime().asMilliseconds() - tres;
            epizode[3].position.x -= timer.getElapsedTime().asMilliseconds() - tres;

            sf::Text text2(title_str, m_font, 25);
            text2.setFillColor(sf::Color::Black);
            text2.setPosition(50, 925 - (float)text2.getLocalBounds().height / 2);
            text2.move(0, timer.getElapsedTime().asMilliseconds() - tres);

            title[0].position.y += timer.getElapsedTime().asMilliseconds() - tres;
            title[1].position.y += timer.getElapsedTime().asMilliseconds() - tres;
            title[2].position.y += timer.getElapsedTime().asMilliseconds() - tres;
            title[3].position.y += timer.getElapsedTime().asMilliseconds() - tres;

            window.draw(sprite);
            window.draw(channel_banner);
            window.draw(channel);
            window.draw(epizode);
            window.draw(epizode_num);
            window.draw(title);
            window.draw(text2);
        }
    
    if(timer.getElapsedTime().asMilliseconds() > 38000){
        sf::Texture iconTexture;
        iconTexture.loadFromFile("icon.png");

        sf::Sprite iconSprite;
        iconSprite.setTexture(iconTexture);
        iconSprite.setOrigin(iconSprite.getLocalBounds().width / 2, iconSprite.getLocalBounds().height / 2);
        iconSprite.setPosition((float)sizes.x / 2, (float)sizes.y / 2);
        
        if(timer.getElapsedTime().asMilliseconds() < 39000){
            auto c = iconSprite.getColor();
            iconSprite.setColor(sf::Color(c.r, c.g, c.b, (255.f / 1000) * (timer.getElapsedTime().asMilliseconds() - 38000)));
        }

        window.draw(iconSprite);
    }

    }
}

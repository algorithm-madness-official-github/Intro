#include "GameOfLife.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

GameOfLifeSim::GameOfLifeSim(unsigned x, unsigned y){
    srand(time(NULL));
    sizeX = x / 10;
    sizeY = y / 10;

    m_arr = new bool*[sizeX];

    for(unsigned i = 0; i < sizeX; i++){
        m_arr[i] = new bool[sizeY]{0};
        for(unsigned j = 0; j < sizeY; j++){
            m_arr[i][j] = rand() % 2;
        }
    }

    /*m_arr[25][1] = 1;
    m_arr[23][2] = 1; m_arr[25][2] = 1;
    m_arr[13][3] = 1; m_arr[14][3] = 1; m_arr[21][3] = 1; m_arr[22][3] = 1; m_arr[35][3] = 1; m_arr[36][3] = 1;
    m_arr[12][4] = 1; m_arr[16][4] = 1; m_arr[21][4] = 1; m_arr[22][4] = 1; m_arr[35][4] = 1; m_arr[36][4] = 1;
    m_arr[1][5] = 1; m_arr[2][5] = 1; m_arr[11][5] = 1; m_arr[17][5] = 1; m_arr[21][5] = 1; m_arr[22][5] = 1;
    m_arr[1][6] = 1; m_arr[2][6] = 1; m_arr[11][6] = 1; m_arr[15][6] = 1; m_arr[17][6] = 1; m_arr[18][6] = 1; m_arr[23][6] = 1; m_arr[25][6] = 1;
    m_arr[11][7] = 1; m_arr[17][7] = 1; m_arr[25][7] = 1;
    m_arr[12][8] = 1; m_arr[16][8] = 1;
    m_arr[13][9] = 1; m_arr[14][9] = 1;*/
}

void GameOfLifeSim::update(){
    bool** tarr;
    tarr = new bool*[sizeX];

    for(unsigned i = 0; i < sizeX; i++){
        tarr[i] = new bool[sizeY]{0};
        for(unsigned j = 0; j < sizeY; j++){
            tarr[i][j] = m_arr[i][j];
        }
    }

    for(unsigned i = 1; i < sizeX - 1; i++){
        for(unsigned j = 1; j < sizeY - 1; j++){
            unsigned c = 0;
            
            for(int k = -1; k <= 1; k++){
                for(int l = -1; l <= 1; l++){
                    if(tarr[i+k][j+l] == 1 && k != 0 && k != l)
                        c++;
                }
            }

            if(tarr[i][j]){
                if(c < 2 || c > 3)
                    m_arr[i][j] = 0;
            }else{
                if(c == 3)
                    m_arr[i][j] = 1;
            }
        }
    }
    

    for(unsigned i = 0; i < sizeX; i++){
        delete[] tarr[i];
    }
    
    delete[] tarr;
}

void GameOfLifeSim::draw(sf::RenderWindow &window){
    if(timer.getElapsedTime().asMilliseconds() % 50 == 0)
        update();
    
    for(unsigned i = 0; i < sizeX; i++){
        for(unsigned j = 0; j < sizeY; j++){
            sf::RectangleShape rect;
            rect.setSize(sf::Vector2f(10, 10));
            rect.setPosition(sf::Vector2f(i * 10, j * 10));
            
            if(m_arr[i][j])
                rect.setFillColor(sf::Color::White);
            else
                rect.setFillColor(sf::Color::Black);
            
            window.draw(rect);
        }
    }
}

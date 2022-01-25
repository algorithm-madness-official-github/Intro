#pragma once

#include "Vector2D.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <initializer_list>
#include <vector>
class FluidSimulation{
struct Dye{
    sf::Color color;
    float treshold;
};

public:
    FluidSimulation(float dt, float diff, float visc, std::initializer_list<Dye> list);
    void draw(sf::RenderWindow& window);

    ~FluidSimulation();

private:
    const unsigned N = 600;
    const unsigned iter = 1;

    void update();
    void visualize(sf::RenderWindow& window);
    void addDensity(unsigned x, unsigned y, float amount);
    void addVelocity(unsigned x, unsigned y, float vx, float vy);
    void lin_solve(int b, float** x, float** x0, float a, float c);
    void set_bnd(int b, float** x);
    void diffuse(int b, float** x, float** x0, float c);
    void project(float** velocX, float** velocY, float** p, float** div); 
    void advect(int b, float** d, float** d0,  float** velocX, float** velocY);

    sf::Color getColor(float treshold);
    sf::Image mapLegend;
    
    float** m_density;
    float** m_s;
    std::vector<Dye> m_color;

    float** m_x;
    float** m_y;

    float** m_x0;
    float** m_y0;

    float m_dt, m_diffusion, m_viscosity;
};
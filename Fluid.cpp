#include "Fluid.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <vector>

sf::Color FluidSimulation::getColor(float treshold){
    unsigned i = 0;
    while (m_color.size() > i && m_color[i].treshold < treshold) i++;

    if(i == m_color.size())
        return m_color[m_color.size() - 1].color;

    if(i == 0)
        return m_color[0].color;

    if(m_color[i].treshold == treshold)
        return m_color[i].color;
    
    sf::Color color;
    float t = m_color[i].treshold - m_color[i - 1].treshold;
    t = (treshold - m_color[i - 1].treshold) / t;

    auto c1 = m_color[i - 1].color, c2 = m_color[i].color;
    color.r = c1.r * (1 - t) + c2.r * t;
    color.g = c1.g * (1 - t) + c2.g * t;
    color.b = c1.b * (1 - t) + c2.b * t;

    return color;
}

void FluidSimulation::addDensity(unsigned x, unsigned y, float amount){
    m_density[x][y] += amount;
}

void FluidSimulation::addVelocity(unsigned x, unsigned y, float vx, float vy){
    m_x[x][y] += vx;
    m_y[x][y] += vy;
}

void FluidSimulation::set_bnd(int b, float** x){
    for(int i = 1; i < N - 1; i++) {
        x[i][0] = b == 2 ? -x[i][1] : x[i][1];
        x[i][N-1] = b == 2 ? -x[i][N-2] : x[i][N-2];
    }
    for(int j = 1; j < N - 1; j++) {
        x[0][j] = b == 1 ? -x[1][j] : x[1][j];
        x[N-1][j] = b == 1 ? -x[N-2][j] : x[N-2][j];
    }
    
    x[0][0]         = 0.33f * (x[1][0] + x[0][1]);
    x[0][N-1]       = 0.33f * (x[1][0] + x[0][N-2]);
    x[N-1][0]       = 0.33f * (x[N-2][0] + x[N-1][1]);
    x[N-1][N-1]     = 0.33f * (x[N-2][N-1] + x[N-1][N-2]);
}

void FluidSimulation::lin_solve(int b, float** x, float** x0, float a, float c){
    float cRecip = 1.f / c;

    for(unsigned k = 0; k < iter; k++){
        for(unsigned i = 1; i < N - 1; i++){
            for(unsigned j = 1; j < N - 1; j++){
                x[i][j] = (x0[i][j] + a * (x[i+1][j] + x[i-1][j] + x[i][j+1] + x[i][j-1])) * cRecip;
            }
        }
    }
    set_bnd(b, x);
}

void FluidSimulation::diffuse(int b, float** x, float** x0, float c){
    float a = m_dt * c * (N - 2) * (N - 2);
    lin_solve(b, x, x0, a, 1 + 6 * a);
}

void FluidSimulation::project(float** velocX, float** velocY, float** p, float** div){
    for (int i = 1; i < N - 1; i++) {
        for (int j = 1; j < N - 1; j++) {
            div[i][j] = -0.5f * ( velocX[i+1][j] - velocX[i-1][j] + velocY[i][j+1] - velocY[i][j-1]) / N;
            p[i][j] = 0;
        }
    }
    set_bnd(0, div); 
    set_bnd(0, p);
    lin_solve(0, p, div, 1, 6);
    
    for (int j = 1; j < N - 1; j++) {
        for (int i = 1; i < N - 1; i++) {
            velocX[i][j] -= 0.5f * (  p[i+1][j] - p[i-1][j]) * N;
            velocY[i][j] -= 0.5f * (  p[i][j+1] - p[i][j-1]) * N;
        }
    }
    
    set_bnd(1, velocX);
    set_bnd(2, velocY);
}

void FluidSimulation::advect(int b, float** d, float** d0,  float** velocX, float** velocY){
    float i0, i1, j0, j1;
    
    float dtx = m_dt * (N - 2);
    float dty = m_dt * (N - 2);
    
    float s0, s1, t0, t1;
    float tmp1, tmp2, x, y;
    
    float Nfloat = N - 2;
    float ifloat, jfloat, kfloat;
    int i, j;
    
    for(i = 1, ifloat = 1; i < N - 1; i++, ifloat++) { 
        for(j = 1, jfloat = 1; j < N - 1; j++, jfloat++) {
            tmp1 = dtx * velocX[i][j];
            tmp2 = dty * velocY[i][j];
            x    = ifloat - tmp1; 
            y    = jfloat - tmp2;
            
            if(x < 0.5f) x = 0.5f; 
            if(x > Nfloat + 0.5f) x = Nfloat + 0.5f; 

            i0 = std::floor(x); 
            i1 = i0 + 1.0f;

            if(y < 0.5f) y = 0.5f; 
            if(y > Nfloat + 0.5f) y = Nfloat + 0.5f; 

            j0 = std::floor(y);
            j1 = j0 + 1.0f;
            
            s1 = x - i0; 
            s0 = 1.0f - s1; 
            t1 = y - j0; 
            t0 = 1.0f - t1;
                
            int i0i = i0;
            int i1i = i1;
            int j0i = j0;
            int j1i = j1;
                
            d[i][j] = s0 *      ( t0 * d0[i0i][j0i] + 
                                ( t1 * d0[i0i][j1i] ) ) + 
                      s1 *      ( t0 * d0[i1i][j0i] + 
                                ( t1 * d0[i1i][j1i] ) );
        }
    }
    set_bnd(b, d);
}



void FluidSimulation::update(){
    diffuse(1, m_x0, m_x, m_viscosity);
    diffuse(2, m_y0, m_y, m_viscosity);
    
    project(m_x0, m_y0, m_x, m_y);
    
    advect(1, m_x, m_x0, m_x0, m_y0);
    advect(2, m_y, m_y0, m_x0, m_y0);
    
    project(m_x, m_y, m_x0, m_y0);
    
    diffuse(0, m_s, m_density, m_diffusion);
    advect(0, m_density, m_s, m_x, m_y);
}

void FluidSimulation::draw(sf::RenderWindow &window){
    update();
    sf::Image image;
    image.create(N, N, sf::Color::Black);

    for(unsigned i = 0; i < N; i++){
        for(unsigned j = 0; j < N; j++){
            float t = m_density[i][j];
            image.setPixel(i, j, getColor(t));
        }
    }
    auto sizes = window.getSize();

    sf::Texture texture;
    texture.loadFromImage(image);

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setOrigin((float)N / 2, (float)N / 2);
    sprite.setPosition((float)sizes.x / 2, (float)sizes.y / 2);

    window.draw(sprite);

    texture.loadFromFile("equations.png");

    sf::Sprite eq;
    eq.setTexture(texture);
    eq.setOrigin((float)texture.getSize().x / 2, (float)texture.getSize().y / 2);
    eq.setPosition((float)sizes.x / 2, (float)sizes.y / 2 + (float)N / 2 + 150);

    window.draw(eq);

    texture.loadFromImage(mapLegend);
    sf::Sprite legend;
    legend.setTexture(texture);
    legend.setOrigin(10, (float)N / 2);
    legend.setPosition((float)sizes.x / 2 - (float)N / 2 - 100, (float)sizes.y / 2);

    window.draw(legend);
}

FluidSimulation::FluidSimulation(float dt, float diff, float visc, std::initializer_list<Dye> list) : m_dt(dt), m_diffusion(diff), m_viscosity(visc){
    m_x = new float*[N];
    m_y = new float*[N];
    m_x0 = new float*[N];
    m_y0 = new float*[N];
    m_density = new float*[N];
    m_s = new float*[N];

    for(unsigned i = 0; i < N; i++){
        m_x[i] = new float[N]{0};
        m_y[i] = new float[N]{0};
        m_x0[i] = new float[N]{0};
        m_y0[i] = new float[N]{0};
        m_density[i] = new float[N]{0};
        m_s[i] = new float[N]{0};
    }
    float prev = 0;
    for(auto& l : list){
        if(l.treshold < prev)
            throw std::runtime_error("Check your treshold order!\n");
        else if(l.treshold > 1 || l.treshold < 0)
            throw std::runtime_error("Wrong treshold!\n");
        m_color.push_back(l);
    }

    srand(time(NULL));

    for(unsigned i = 0; i < N; i++){
        for(unsigned j = 0; j < N; j++){
            m_x[i][j] = -10 + rand() % 21;
            m_y[i][j] = -10 + rand() % 21;
            m_density[i][j] = (float)i / N;
        }
    }

    mapLegend.create(20, N, sf::Color::Black);

    unsigned i = N - 1;
    for(float t = 0; i > 0; t += 1.f / N){
        sf::Color color = getColor(t);
        for(unsigned j = 0; j < 20; j++){
            mapLegend.setPixel(j, i, color);
        }
        i--;
    }
}

FluidSimulation::~FluidSimulation(){
    for(unsigned i = 0; i < N; i++){
        delete[] m_x[i];;
        delete[] m_y[i];
        delete[] m_x0[i];
        delete[] m_y0[i];
        delete[] m_density[i];
        delete[] m_s[i];
    }

    delete[] m_x;
    delete[] m_y;
    delete[] m_x0;
    delete[] m_y0;
    delete[] m_density;
    delete[] m_s;
}

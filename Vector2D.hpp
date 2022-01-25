//plik Vector2D.hpp

	/*! \file Vector2D.hpp
	*
	* \brief Zawiera deklarację klasy Polygon
	*
	* Plik zawiera deklarację klasy Vector2D.
	* Klasa przchowuje wspólrzędne wektora, oblicza elementarne jego właściwości oraz umożliwia podstawowe operacje arytmetyczne na wektorach
	* Klasa zawiera kilka metod skladowych
	*
	* \author Adam Ratajczak
	* \date 2022.01.13
	* \version 1.00.00
	*/

#pragma once
#include <cmath>

class Vector2D{
public:
    // konstruktory
    Vector2D() : m_x(.0), m_y(.0){}
    Vector2D(double x, double y) : m_x(x), m_y(y){}

    // dostęp do składowych wektora
    double& x(){ return m_x;}
    double& y(){ return m_y;}

    double x() const{ return m_x;}
    double y() const{ return m_y;}

    // zwraca długość wektora
    double magnitude() const{ return std::sqrt(m_x * m_x + m_y * m_y); }

    // zwraca kąt
    double theta() const{ return std::atan2(m_y, m_x); }
    
    // zwraca wektor jednostkowy
	Vector2D unitVector() const;

    // dodawanie i odejmowanie wektorów
    Vector2D operator+(Vector2D x);

    Vector2D operator-(Vector2D x);

    void operator+=(Vector2D x);

    void operator-=(Vector2D x);

    // cross product
    double operator*(Vector2D x);

    // mnożenie przez skalar
    Vector2D operator*(double x);

    void operator*=(double x);

private:
    // współrzędne wektora
    double m_x, m_y;
};
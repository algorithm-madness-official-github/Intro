#include "Vector2D.hpp"

Vector2D Vector2D::unitVector() const {
	double mag = magnitude();
	if (mag != 0.) 
        return Vector2D(m_x / mag, m_y / mag);
	return Vector2D();
}

// dodawanie i odejmowanie wektorów
Vector2D Vector2D::operator+(Vector2D x){
    Vector2D result = *this;    result.m_x += x.m_x;
    result.m_y += x.m_y;

    return result;
}

Vector2D Vector2D::operator-(Vector2D x){
    Vector2D result = *this;
    result.m_x -= x.m_x;
    result.m_y -= x.m_y;

    return result;
}

void Vector2D::operator+=(Vector2D x){
    m_x += x.m_x;
    m_y += x.m_y;
}

void Vector2D::operator-=(Vector2D x){
    m_x -= x.m_x;
    m_y -= x.m_y;
}

// cross product
double Vector2D::operator*(Vector2D x){
    return m_x * x.m_y - m_y * x.m_x;
}

// mnożenie przez skalar
Vector2D Vector2D::operator*(double x){
    Vector2D result = *this;
    result.m_x *= x;
    result.m_y *= x;

    return result;
}

void Vector2D::operator*=(double x){
    m_x *= x;
    m_y *= x;
}
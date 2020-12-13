/*
 * Hex.hpp
 *
 *  Created on: Nov 25, 2020
 *      Author: raphael
 */

#ifndef SRC_HEX_HPP_
#define SRC_HEX_HPP_

#include <iostream>
#include <cmath>
#include <functional>

#include <SFML/Graphics.hpp>

#include "Geometry.hpp"
#include "AbstractClickable.hpp"

static const float COS_PI_3  = std::cos(M_PI/3);
static const float COS_2PI_3 = std::cos(2*M_PI/3);
static const float COS_PI    = std::cos(M_PI);
static const float COS_4PI_3 = std::cos(4*M_PI/3);
static const float COS_5PI_3 = std::cos(5*M_PI/3);
static const float COS_2PI   = std::cos(2*M_PI);


static const float SIN_PI_3  = std::sin(M_PI/3);
static const float SIN_2PI_3 = std::sin(2*M_PI/3);
static const float SIN_PI    = std::sin(M_PI);
static const float SIN_4PI_3 = std::sin(4*M_PI/3);
static const float SIN_5PI_3 = std::sin(5*M_PI/3);
static const float SIN_2PI   = std::sin(2*M_PI);


class Hex : public AbstractClickable
{
public:
    Hex() : _radius(0), _center(0,0), _shape(6)
{
        computeShape();
};

float getRadius() const {return _radius;};
void setRadius(float radius)
{
    _radius = radius;
    computeShape();
};

const sf::Vector2f& getCenter() const {return _center;};
void setCenter(const sf::Vector2f& center)
{
    _center = center;
    computeShape();
}

sf::ConvexShape& getShape() { return _shape;};

// Clickable itf
bool isInside(sf::Vector2f mousePosition) const override
{
    return Geometry::isInsidePolygon(mousePosition, _shape.getPoints());
}

virtual ~Hex(){};


private:
    void computeShape()
    {
        _shape.setPoint(0, sf::Vector2f(_center.x + _radius * COS_PI_3,  _center.y + _radius * SIN_PI_3));
        _shape.setPoint(1, sf::Vector2f(_center.x + _radius * COS_2PI_3, _center.y + _radius * SIN_2PI_3));
        _shape.setPoint(2, sf::Vector2f(_center.x + _radius * COS_PI,    _center.y + _radius * SIN_PI));
        _shape.setPoint(3, sf::Vector2f(_center.x + _radius * COS_4PI_3, _center.y + _radius * SIN_4PI_3));
        _shape.setPoint(4, sf::Vector2f(_center.x + _radius * COS_5PI_3, _center.y + _radius * SIN_5PI_3));
        _shape.setPoint(5, sf::Vector2f(_center.x + _radius * COS_2PI,   _center.y + _radius * SIN_2PI));
    };
private:
    float _radius;
    sf::Vector2f _center;
    sf::ConvexShape _shape;

};



#endif /* SRC_HEX_HPP_ */

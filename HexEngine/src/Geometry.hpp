/*
 * Geometry.hpp
 *
 *  Created on: Nov 26, 2020
 *      Author: raphael
 */

#ifndef SRC_GEOMETRY_HPP_
#define SRC_GEOMETRY_HPP_

#include <vector>

#include "SFML/Graphics.hpp"

namespace Geometry
{

bool almostEqual(float lhs, float rhs)
{
    return std::abs(rhs - lhs) < std::numeric_limits<float>::epsilon();
}

bool isInsidePolygon(sf::Vector2f point, std::vector<sf::Vector2f> polygon)
{
    std::cout<<__FUNCTION__<<":\n";
    for(const auto& point: polygon)
    {
        std::cout<<"\t" << point.x << "\t" <<point.y<<"\n";
    }

    if(polygon.size() < 3)
    {
        return false;
    }

    int nbOfIntersections = 0;

    // On calcule le nombre d'intersections entre les aretes du polygone et la demi-droite partant de point et allant à l'infini sur l'axe x
    for(int i = 0 ; i < polygon.size(); i++)
    {
        auto& edgePoint1 = polygon[i];
        auto& edgePoint2 = polygon[(i+1)%polygon.size()];

        if(almostEqual(edgePoint1.y,edgePoint2.y))
        {
            // arete horizontale :s'il y a une intersection ici elle sera detectee aux aretes voisines : on peut l'ignorer
        }
        else if(almostEqual(edgePoint1.x, edgePoint2.x))
        {
            // arete verticale
            if(edgePoint1.x >= point.x
                    && point.y <= std::max(edgePoint1.y, edgePoint2.y)
                    && point.y >= std::min(edgePoint1.y, edgePoint2.y))
            {
                std::cout<<"arete verticale at " << edgePoint1.x <<"\n";
                nbOfIntersections++;
            }
        }
        else
        {
            //cas general, on calcule l'abscisse du point d'intersection
            float x_intersection = edgePoint1.x + (point.y - edgePoint1.y) * ( edgePoint2.x - edgePoint1.x) / (edgePoint2.y - edgePoint1.y);

            // ça serait cool de ré-ecrire ça en branchless
            if (x_intersection >= point.x)
            {
                if(edgePoint1.x < edgePoint2.x)
                {
                    if(x_intersection >= edgePoint1.x &&
                       x_intersection <  edgePoint2.x)
                    {
                        nbOfIntersections++;
                    }
                }
                else
                {
                    if(x_intersection <= edgePoint1.x &&
                       x_intersection >  edgePoint2.x)
                    {
                        nbOfIntersections++;
                    }
                }
            }
        }
    }

    std::cout<<"nbOfIntersections " << nbOfIntersections<<"\n";

    return (nbOfIntersections%2);
}


} // namespace Geometry


#endif /* SRC_GEOMETRY_HPP_ */

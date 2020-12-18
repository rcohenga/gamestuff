/*
 * Coordinates.hpp
 *
 *  Created on: Dec 17, 2020
 *      Author: raphael
 */

#ifndef HEXENGINE_SRC_COORDINATES_HPP_
#define HEXENGINE_SRC_COORDINATES_HPP_

#include <tuple>

namespace HE
{
namespace Coord
{
    class Axial
    {
    public:
        Axial(int _r, int _q);
        Axial();

        int r() const; // row
        int q() const; // qolumn

        int& r();
        int& q();

        Axial operator+(const Axial& rhs) const;
        Axial& operator+=(const Axial& rhs);

        friend bool operator==(const Axial& lhs, const Axial& rhs);
        friend bool operator!=(const Axial& lhs, const Axial& rhs);

        friend bool operator<(const Axial& lhs, const Axial& rhs);
        friend bool operator>(const Axial& lhs, const Axial& rhs);


    private:
        std::tuple<int,int> data;
    };
}

}



#endif /* HEXENGINE_SRC_COORDINATES_HPP_ */

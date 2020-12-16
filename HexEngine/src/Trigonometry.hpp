/*
 * Trigonometry.hpp
 *
 *  Created on: Dec 15, 2020
 *      Author: raphael
 */

#ifndef HEXENGINE_SRC_TRIGONOMETRY_HPP_
#define HEXENGINE_SRC_TRIGONOMETRY_HPP_


#include <cmath>

namespace Geometry
{

constexpr float cos(int p, int q) { return std::cos((float)p * M_PI / q); }
constexpr float sin(int p, int q) { return std::sin((float)p * M_PI / q); }

}



#endif /* HEXENGINE_SRC_TRIGONOMETRY_HPP_ */

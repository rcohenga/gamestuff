/*
 * Grid.hpp
 *
 *  Created on: Dec 17, 2020
 *      Author: raphael
 */

#ifndef HEXENGINE_SRC_GRID_HPP_
#define HEXENGINE_SRC_GRID_HPP_

#include <map>

#include "Axial.hpp"

namespace HE
{

template<class TileType>
class Grid
{

private:
    std::map<Coord::Axial, TileType> tiles;
};

}



#endif /* HEXENGINE_SRC_GRID_HPP_ */

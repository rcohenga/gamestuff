/*
 * Tile.hpp
 *
 *  Created on: Dec 13, 2020
 *      Author: raphael
 */

#ifndef SRC_HEXAGO_TILE_HPP_
#define SRC_HEXAGO_TILE_HPP_

namespace HexaGo
{



class Tile
{
public:
    enum class EValue
    {
        Empty,
        White,
        Black
    };

    EValue value;
};
}



#endif /* SRC_HEXAGO_TILE_HPP_ */

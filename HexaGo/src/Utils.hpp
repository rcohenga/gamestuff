/*
 * Utils.hpp
 *
 *  Created on: Dec 23, 2020
 *      Author: raphael
 */

#ifndef HEXAGO_SRC_UTILS_HPP_
#define HEXAGO_SRC_UTILS_HPP_

#include "Tile.hpp"
#include "Board.hpp"

namespace HexaGo
{
    EPlayer valueToPlayer(Tile::EValue);
    Tile::EValue playerToValue(EPlayer);

    EPlayer otherPlayer(EPlayer);


    std::string toString(EPlayer);
    std::string toString(Tile::EValue);
}



#endif /* HEXAGO_SRC_UTILS_HPP_ */

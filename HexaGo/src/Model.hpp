/*
 * Model.hpp
 *
 *  Created on: Dec 13, 2020
 *      Author: raphael
 */

#ifndef SRC_HEXAGO_MODEL_HPP_
#define SRC_HEXAGO_MODEL_HPP_

#include <tuple>
#include <map>

#include "Tile.hpp"

namespace HexaGo
{

typedef std::tuple<int, int> AxialCoord;




class Model
{
public:
    enum class ECurrentPlayer
    {
        White,
        Black
    };
public:
    Model(unsigned int gridRadius);

    bool layTile(AxialCoord coord);

    const std::map<AxialCoord, Tile>& getTiles() const;
    const ECurrentPlayer getCurrentPlayer() const;
private:
    std::map<AxialCoord, Tile> m_tiles;
    ECurrentPlayer m_currentPlayer;
};


}



#endif /* SRC_HEXAGO_MODEL_HPP_ */

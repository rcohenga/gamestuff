/*
 * Board.hpp
 *
 *  Created on: Dec 23, 2020
 *      Author: raphael
 */

#ifndef HEXAGO_SRC_BOARD_HPP_
#define HEXAGO_SRC_BOARD_HPP_

#include <map>


// HexEngine dependencies
#include "Axial.hpp"

// HexaGo dependencies
#include "Tile.hpp"

namespace HexaGo
{

enum class EPlayer
{
    Black,
    White
};


class Board
{
public:
    Board(unsigned int gridRadius);
    const std::map<HE::Coord::Axial, Tile>& getTiles() const;
    const EPlayer getCurrentPlayer() const;
    float getScore(EPlayer player) const;

    std::map<HE::Coord::Axial, Tile>& getTiles();
    EPlayer& getCurrentPlayer();
    float& getScore(EPlayer player);

private:
    std::map<HE::Coord::Axial, Tile> m_tiles;
    EPlayer m_currentPlayer;
    std::map<EPlayer, float> m_score;
};


}



#endif /* HEXAGO_SRC_BOARD_HPP_ */

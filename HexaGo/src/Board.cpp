/*
 * Board.cpp
 *
 *  Created on: Dec 23, 2020
 *      Author: raphael
 */

#include "Board.hpp"

namespace HexaGo
{


Board::Board(unsigned int gridRadius):
        m_currentPlayer(EPlayer::Black)
{
    // initializing tiles
    if(gridRadius > 0)
    {
        int gridRadiusMinusOne = gridRadius -1;
        for(int q = - gridRadiusMinusOne; q <= gridRadiusMinusOne ; q++)
        {
            for(int r = - gridRadiusMinusOne; r <= gridRadiusMinusOne ; r++)
            {
                if(std::abs(r + q) <= gridRadiusMinusOne)
                {
                    Tile tile;
                    tile.value = Tile::EValue::Empty;

                    m_tiles.emplace(HE::Coord::Axial(q,r), tile);
                }
            }
        }
    }

    // initializing score
    m_score.emplace(EPlayer::White, 0);
    m_score.emplace(EPlayer::Black, 0);
}

const EPlayer Board::getCurrentPlayer() const
{
    return m_currentPlayer;
}

float Board::getScore(EPlayer player) const
{
    return m_score.at(player);
}

const std::map<HE::Coord::Axial, Tile>& Board::getTiles() const
{
    return m_tiles;
}

EPlayer& Board::getCurrentPlayer()
{
    return m_currentPlayer;
}

float& Board::getScore(EPlayer player)
{
    return m_score.at(player);
}

std::map<HE::Coord::Axial, Tile>& Board::getTiles()
{
    return m_tiles;
}

}



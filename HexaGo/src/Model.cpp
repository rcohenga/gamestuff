/*
 * Model.cpp
 *
 *  Created on: Dec 13, 2020
 *      Author: raphael
 */

#include <iostream>

#include "Model.hpp"

namespace HexaGo
{
Model::Model(unsigned int gridRadius):
        m_currentPlayer(ECurrentPlayer::White)
{

    if(gridRadius > 0)
    {
        int gridRadiusMinusOne = gridRadius -1;
        for(int q = - gridRadiusMinusOne; q <= gridRadiusMinusOne ; q++)
        {
            for(int r = - gridRadiusMinusOne; r <= gridRadiusMinusOne ; r++)
            {
                Tile tile;
                tile.value = Tile::EValue::Empty;

                m_tiles.emplace(AxialCoord(q,r), tile);
            }
        }
    }
}

bool Model::layTile(AxialCoord coord)
{
    std::cout<<__FUNCTION__ << " " << std::get<0>(coord) << ";"<< std::get<1>(coord)<<"\n";
    auto tilePair = m_tiles.find(coord);
    if(tilePair == m_tiles.end())
    {
        return false;
    }

    if(tilePair->second.value != Tile::EValue::Empty)
    {
        return false;
    }

    if(getCurrentPlayer() == ECurrentPlayer::White)
    {
        tilePair->second.value = Tile::EValue::White;
    }
    else
    {
        tilePair->second.value = Tile::EValue::Black;
    }

    endTurn();

    return true;
}

const Model::ECurrentPlayer Model::getCurrentPlayer() const
{
    return m_currentPlayer;
}

const std::map<AxialCoord, Tile>& Model::getTiles() const
{
    return m_tiles;
}


void Model::endTurn()
{
    if(m_currentPlayer == Model::ECurrentPlayer::White)
    {
        m_currentPlayer = Model::ECurrentPlayer::Black;
    }
    else
    {
        m_currentPlayer = Model::ECurrentPlayer::White;
    }
}

}



/*
 * BoardOperations.cpp
 *
 *  Created on: Dec 23, 2020
 *      Author: raphael
 */
#include <sstream>
#include <iostream>

#include "BoardOperations.hpp"
#include "Utils.hpp"

namespace HexaGo
{

/******** ChangeTileContent ********/

ChangeTileContent::ChangeTileContent(HE::Coord::Axial coord, Tile::EValue newValue, Tile::EValue oldValue):
        m_coord(coord)
        ,m_oldValue(oldValue)
        ,m_newValue(newValue)
{}

bool ChangeTileContent::execute(Board& board) const
{
    auto it = board.getTiles().find(m_coord);
    if(it == board.getTiles().end())
    {
        return false;
    }
    else
    {
        if(board.getTiles().at(m_coord).value != m_oldValue)
        {
            return false;
        }
        else
        {
            board.getTiles().at(m_coord).value = m_newValue;
            return true;
        }
    }
}

std::shared_ptr<IBoardOperation> ChangeTileContent::reverse() const
{
    return std::make_shared<ChangeTileContent>(m_coord, m_oldValue, m_newValue);
}


std::string ChangeTileContent::getInfo() const
{
    std::ostringstream ss;
    ss << "ChangeTileContent (" << m_coord.r() << ";" << m_coord.q() << ") from " << toString(m_oldValue)<< " to " << toString(m_newValue);
    return ss.str();
}


/******** ChangeCurrentPlayer ********/

ChangeCurrentPlayer::ChangeCurrentPlayer(EPlayer newValue, EPlayer oldValue):
        m_oldValue(oldValue), m_newValue(newValue){};
bool ChangeCurrentPlayer::execute(Board& board) const
{
    std::cout<<"executing " << this->getInfo()<<"\n";
    if(board.getCurrentPlayer() != m_oldValue) return false;
    board.getCurrentPlayer() = m_newValue;
    return true;
}
std::shared_ptr<IBoardOperation> ChangeCurrentPlayer::reverse() const
{
    return std::make_shared<ChangeCurrentPlayer>(m_oldValue, m_newValue);
}
std::string ChangeCurrentPlayer::getInfo() const
{
    std::ostringstream ss;
    ss << "ChangeCurrentPlayer from " << toString(m_oldValue) << " to " << toString(m_newValue);
    return ss.str();
}

/******** ChangeScore ********/

ChangeScore::ChangeScore(EPlayer player, float delta):
        m_player(player), m_delta(delta)
{}
bool ChangeScore::execute(Board& board) const
{
    std::cout<<"current score: " << board.getScore(m_player) <<"\n";
    board.getScore(m_player) += m_delta;
    return true;
}
std::shared_ptr<IBoardOperation> ChangeScore::reverse() const
{
    return std::make_shared<ChangeScore>(m_player, -m_delta);
}
std::string ChangeScore::getInfo() const
{
    std::ostringstream ss;
    ss << "ChangeScore of player " << toString(m_player) << " by " << m_delta;
    return ss.str();
}



}




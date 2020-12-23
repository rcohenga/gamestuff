/*
 * BoardOperations.hpp
 *
 *  Created on: Dec 23, 2020
 *      Author: raphael
 */

#ifndef HEXAGO_SRC_BOARDOPERATIONS_HPP_
#define HEXAGO_SRC_BOARDOPERATIONS_HPP_

#include <memory>
#include "IBoardOperation.hpp"
#include "Board.hpp"


namespace HexaGo
{
class ChangeTileContent : public IBoardOperation
{
public:
    ChangeTileContent(HE::Coord::Axial coord, Tile::EValue newValue, Tile::EValue oldValue);
    bool execute(Board& board) const override;
    std::shared_ptr<IBoardOperation> reverse() const override;
    std::string getInfo() const override;

private:
    HE::Coord::Axial m_coord;
    Tile::EValue m_oldValue;
    Tile::EValue m_newValue;
};

class ChangeCurrentPlayer : public IBoardOperation
{
public:
    ChangeCurrentPlayer(EPlayer newValue, EPlayer oldValue);
    bool execute(Board& board) const override;
    std::shared_ptr<IBoardOperation> reverse() const override;
    std::string getInfo() const override;

private:
    EPlayer m_oldValue;
    EPlayer m_newValue;
};

class ChangeScore : public IBoardOperation
{
public:
    ChangeScore(EPlayer player, float delta);
    bool execute(Board& board) const override;
    std::shared_ptr<IBoardOperation> reverse() const override;
    std::string getInfo() const override;

private:
    EPlayer m_player;
    float m_delta;
};




} // HexaGo



#endif /* HEXAGO_SRC_BOARDOPERATIONS_HPP_ */

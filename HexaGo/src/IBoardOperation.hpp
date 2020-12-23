/*
 * IBoardOperation.hpp
 *
 *  Created on: Dec 23, 2020
 *      Author: raphael
 */

#ifndef HEXAGO_SRC_IBOARDOPERATION_HPP_
#define HEXAGO_SRC_IBOARDOPERATION_HPP_

#include <memory>

namespace HexaGo
{

class Board;

//enum class EBoardOperation
//{
//
//};

class IBoardOperation
{
public:
    // check preconditions, if not met return false, otherwise change board state and return true;
    virtual bool execute(Board& board) const = 0;
    virtual std::shared_ptr<IBoardOperation> reverse() const = 0;
    virtual std::string getInfo() const = 0;
    //EBoardOperation getEnum() const = 0;

    virtual ~IBoardOperation(){};
};


} // HexaGo



#endif /* HEXAGO_SRC_IBOARDOPERATION_HPP_ */

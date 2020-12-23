/*
 * BoardAction.cpp
 *
 *  Created on: Dec 23, 2020
 *      Author: raphael
 */

#ifndef HEXAGO_SRC_BOARDACTION_CPP_
#define HEXAGO_SRC_BOARDACTION_CPP_

#include <BoardAction.hpp>

namespace HexaGo
{

bool BoardAction::execute(Board& board)
{
    for(int i = 0; i < m_operations.size() ; i++)
    {
        if(!m_operations[i]->execute(board))
        {
            // reversing operations and exiting...
            BoardAction partialAction;
            for(int j = 0 ; j < i; j++)
            {
                partialAction.addOperation(m_operations[j]);
            }

            partialAction.reverse()->execute(board);
            return false;
        }
    }
    return true;
}

void BoardAction::addOperation(std::shared_ptr<IBoardOperation> operation)
{
    m_operations.push_back(operation);
}


std::shared_ptr<BoardAction> BoardAction::reverse() const
{
    auto reversed = std::make_shared<BoardAction>();

    for(int i = m_operations.size() -1 ; i >= 0; i--)
    {
        reversed->addOperation(m_operations[i]->reverse());
    }

    return reversed;
}

}



#endif /* HEXAGO_SRC_BOARDACTION_CPP_ */

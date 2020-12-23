/*
 * AtomicAction.hpp
 *
 *  Created on: Dec 23, 2020
 *      Author: raphael
 */

#ifndef HEXAGO_SRC_BOARDACTION_HPP_
#define HEXAGO_SRC_BOARDACTION_HPP_

#include <memory>
#include <vector>

#include "IBoardOperation.hpp"

namespace HexaGo
{
    class BoardAction
    {
    public:
        bool execute(Board& board);
        void addOperation(std::shared_ptr<IBoardOperation> operation);
        std::shared_ptr<BoardAction> reverse() const;
    private:
        std::vector<std::shared_ptr<IBoardOperation>> m_operations;
    };

}



#endif /* HEXAGO_SRC_BOARDACTION_HPP_ */

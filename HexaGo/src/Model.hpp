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
#include <vector>

// HexEngine dependencies
#include "Axial.hpp"

// HexaGo dependencies
#include "ModelItf.hpp"
#include "Board.hpp"
#include "BoardAction.hpp"
#include "Tile.hpp"

namespace HexaGo
{

class Model
{
public:

    struct Rules //TODO
    {
        float whiteAdvantage;
        int boardRadius;
    };

public:
    Model(unsigned int gridRadius);

    bool layTile(HE::Coord::Axial coord);
    bool reverse();
    const std::map<HE::Coord::Axial, Tile>& getTiles() const;
    const EPlayer getCurrentPlayer() const;
    float getScore(EPlayer player) const;

private:
    void endTurn();
    void checkForDeadClusters();
    void changePlayer();
private:
    // GameState
    Board m_board;

    std::shared_ptr<BoardAction> m_currentAction; // Action being created, will be inserted in m_previousActions upon completion
    std::vector<std::shared_ptr<BoardAction>> m_previousActions;




    // Other stuff

};


}



#endif /* SRC_HEXAGO_MODEL_HPP_ */

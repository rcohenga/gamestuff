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

// HexEngine dependencies
#include "Axial.hpp"

// HexaGo dependencies
#include "ModelItf.hpp"
#include "Tile.hpp"

namespace HexaGo
{

class Model
{
public:
    enum class EPlayer
    {
        White,
        Black
    };
public:
    Model(unsigned int gridRadius);

    bool layTile(HE::Coord::Axial coord);
    const std::map<HE::Coord::Axial, Tile>& getTiles() const;
    const EPlayer getCurrentPlayer() const;

private:
    void endTurn();
    void checkForDeadClusters();
    void changePlayer();
private:
    // GameState
    std::map<HE::Coord::Axial, Tile> m_tiles;
    EPlayer m_currentPlayer;

    // Other stuff

};


}



#endif /* SRC_HEXAGO_MODEL_HPP_ */

/*
 * Model.cpp
 *
 *  Created on: Dec 13, 2020
 *      Author: raphael
 */
#include <vector>
#include <set>
#include <iostream>
#include <algorithm>

#include "GridUtils.hpp"

#include "Model.hpp"
#include "BoardOperations.hpp"
#include "Utils.hpp"

namespace HexaGo
{



Model::Model(unsigned int gridRadius):
        m_board(gridRadius)
{}

bool Model::layTile(HE::Coord::Axial coord)
{
    if(m_board.getTiles().find(coord) == m_board.getTiles().end()) return false;

    m_currentAction = std::make_shared<BoardAction>();
    auto iv_changeTileContentOperation = std::make_shared<ChangeTileContent>(
            coord,
            playerToValue(this->getCurrentPlayer()),
            m_board.getTiles().at(coord).value
    );

    if(!iv_changeTileContentOperation->execute(m_board))return false;

    m_currentAction->addOperation(iv_changeTileContentOperation);
    endTurn();
    m_previousActions.push_back(m_currentAction);

    return true;
}


bool Model::reverse()
{
    //TODO navigation de l'arbre
    if(!m_previousActions.empty())
    {
        auto lastAction = m_previousActions.back();
        return lastAction->reverse()->execute(m_board);
    }
    else
    {
        return false;
    }
}

const EPlayer Model::getCurrentPlayer() const
{
    return m_board.getCurrentPlayer();
}


float Model::getScore(EPlayer player) const
{
    return m_board.getScore(player);
}

const std::map<HE::Coord::Axial, Tile>& Model::getTiles() const
{
    return m_board.getTiles();
}

void Model::endTurn()
{
    checkForDeadClusters();
    changePlayer();
}

void Model::checkForDeadClusters()
{
    std::cout<<__FUNCTION__<<"\n";
    // Create clusters
    std::map<HE::Coord::Axial, int> clusterNumber;
    auto clusters = HE::clusterize<Tile>(m_board.getTiles(), [](const Tile& rhs, const Tile& lhs){return rhs.value == lhs.value;});

    std::cout<<"clusters:\n";
    for(int i = 0 ; i < clusters.size() ; i++)
    {
        const auto& cluster = clusters[i];
        if(m_board.getTiles().at(*cluster.begin()).value != Tile::EValue::Empty)
        {
            std::cout<<"\tcluster "<<i<< "\t" << (m_board.getTiles().at(*cluster.begin()).value == Tile::EValue::Black ? "Black" : "White") <<"\n";
            for(const auto& tile : cluster)
            {
                std::cout<<"\t\t"<<tile.r()<<"\t"<<tile.q()<<"\n";
            }
        }
    }

    // Compute DF for each

    std::set<std::pair<int, EPlayer>> clustersWithNoFreedom;
    for(int i = 0 ; i < clusters.size() ; i++)
    {
        const auto& cluster = clusters[i];
        if(!cluster.empty() && m_board.getTiles().at(*cluster.begin()).value != Tile::EValue::Empty)
        {
            bool hasFreedom = false;
            for(auto& tile : cluster)
            {
                // explore neighbors
                std::set<HE::Coord::Axial> neighbors = HE::getNeighbors(tile, m_board.getTiles());

                for(auto& neighbor : neighbors)
                {
                    auto itNeighbor = m_board.getTiles().find(neighbor);
                    if(itNeighbor != m_board.getTiles().end() && itNeighbor->second.value == Tile::EValue::Empty)
                    {
                        hasFreedom = true;
                        break;
                    }
                }

                if(hasFreedom){break;}
            }

            if(!hasFreedom){clustersWithNoFreedom.emplace(i, (m_board.getTiles().at(*cluster.begin()).value == Tile::EValue::Black ? EPlayer::Black : EPlayer::White));}
        }
    }

    // Delete dead clusters
    if(!clustersWithNoFreedom.empty())
    {
        EPlayer currentOpponent = otherPlayer(getCurrentPlayer());
        // If opponent has clusters with 0 DDL, we delete his, otherwise we delete currentplayer's
        EPlayer playerLosingClusters = (std::find_if(
                clustersWithNoFreedom.begin(),
                clustersWithNoFreedom.end(),
                [currentOpponent](std::pair<int, EPlayer> p){return p.second == currentOpponent;}) !=  clustersWithNoFreedom.end() ?
                        currentOpponent : getCurrentPlayer());

        for(auto& [clusterId, clusterOwner] : clustersWithNoFreedom)
        {
            if(clusterOwner == playerLosingClusters)
            {
                auto& cluster = clusters[clusterId];
                auto scoreOperation = std::make_shared<ChangeScore>(playerLosingClusters, -(float)cluster.size());
                scoreOperation->execute(m_board);
                m_currentAction->addOperation(scoreOperation);

                for(auto& tile : cluster)
                {
                    auto removeOperation = std::make_shared<ChangeTileContent>(tile, Tile::EValue::Empty, playerToValue(playerLosingClusters));
                    removeOperation->execute(m_board);
                    m_currentAction->addOperation(removeOperation);
                }
            }
        }
    }
}

void Model::changePlayer()
{
    auto changePlayer = std::make_shared<ChangeCurrentPlayer>(otherPlayer(m_board.getCurrentPlayer()), m_board.getCurrentPlayer());
    changePlayer->execute(m_board);
    m_currentAction->addOperation(changePlayer);
}

}



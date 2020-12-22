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


namespace HexaGo
{



Model::Model(unsigned int gridRadius):
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

bool Model::layTile(HE::Coord::Axial coord)
{
    auto tilePair = m_tiles.find(coord);
    if(tilePair == m_tiles.end())
    {
        return false;
    }

    if(tilePair->second.value != Tile::EValue::Empty)
    {
        return false;
    }

    if(getCurrentPlayer() == EPlayer::White)
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

const Model::EPlayer Model::getCurrentPlayer() const
{
    return m_currentPlayer;
}


float Model::getScore(EPlayer player) const
{
    return m_score.at(player);
}

const std::map<HE::Coord::Axial, Tile>& Model::getTiles() const
{
    return m_tiles;
}

void Model::endTurn()
{
    checkForDeadClusters();
    changePlayer();
}

class Cluster
{
public:
    std::set<HE::Coord::Axial> tiles;
    Model::EPlayer owner;
    int number;
};



void Model::checkForDeadClusters()
{
    std::cout<<__FUNCTION__<<"\n";
    // Create clusters
    std::map<HE::Coord::Axial, int> clusterNumber;
    auto clusters = HE::clusterize<Tile>(m_tiles, [](const Tile& rhs, const Tile& lhs){return rhs.value == lhs.value;});

    std::cout<<"clusters:\n";
    for(int i = 0 ; i < clusters.size() ; i++)
    {
        const auto& cluster = clusters[i];
        if(m_tiles.at(*cluster.begin()).value != Tile::EValue::Empty)
        {
            std::cout<<"\tcluster "<<i<< "\t" << (m_tiles.at(*cluster.begin()).value == Tile::EValue::Black ? "Black" : "White") <<"\n";
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
        if(!cluster.empty() && m_tiles.at(*cluster.begin()).value != Tile::EValue::Empty)
        {
            bool hasFreedom = false;
            for(auto& tile : cluster)
            {
                // explore neighbors
                std::set<HE::Coord::Axial> neighbors = HE::getNeighbors(tile, m_tiles);

                for(auto& neighbor : neighbors)
                {
                    auto itNeighbor = m_tiles.find(neighbor);
                    if(itNeighbor != m_tiles.end() && itNeighbor->second.value == Tile::EValue::Empty)
                    {
                        hasFreedom = true;
                        break;
                    }
                }

                if(hasFreedom){break;}
            }

            if(!hasFreedom){clustersWithNoFreedom.emplace(i, (m_tiles.at(*cluster.begin()).value == Tile::EValue::Black ? EPlayer::Black : EPlayer::White));}
        }
    }

    // Delete dead clusters
    if(!clustersWithNoFreedom.empty())
    {
        EPlayer currentOpponent = m_currentPlayer == EPlayer::Black ? EPlayer::White : EPlayer::Black;
        // If opponent has clusters with 0 DDL, we delete his, otherwise we delete currentplayer's
        EPlayer playerLosingClusters = (std::find_if(
                clustersWithNoFreedom.begin(),
                clustersWithNoFreedom.end(),
                [currentOpponent](std::pair<int, EPlayer> p){return p.second == currentOpponent;}) !=  clustersWithNoFreedom.end() ?
                        currentOpponent : m_currentPlayer);

        for(auto& clusterId : clustersWithNoFreedom)
        {
            auto& cluster = clusters.at(clusterId.first);
            if(clusterId.second == playerLosingClusters)
            {

                m_score.at(playerLosingClusters)-=cluster.size();
                for(auto& tile : cluster)
                {
                    m_tiles.at(tile).value = Tile::EValue::Empty;
                }
            }
        }
    }
}

void Model::changePlayer()
{
    if(m_currentPlayer == Model::EPlayer::White)
    {
        m_currentPlayer = Model::EPlayer::Black;
    }
    else
    {
        m_currentPlayer = Model::EPlayer::White;
    }
}

}



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

#include "Model.hpp"

namespace HexaGo
{



Model::Model(unsigned int gridRadius):
        m_currentPlayer(EPlayer::White)
{

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
}

bool Model::layTile(HE::Coord::Axial coord)
{
    std::cout<<__FUNCTION__ << " " << coord.r() << ";"<< coord.q()<<"\n";
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
    //TODO
    // Create clusters
    std::map<HE::Coord::Axial, int> clusterNumber;
    std::vector<Cluster> clusters;

    for(const auto& [coord, tile] : m_tiles)
    {
        clusterNumber.emplace(coord, -1);
    }

    for(const auto& [coord, tile] : m_tiles)
    {
        if(clusterNumber.at(coord) == -1
         &&tile.value != Tile::EValue::Empty)
        {
            Cluster newCluster;
            newCluster.owner = (tile.value == Tile::EValue::Black ? EPlayer::Black : EPlayer::White);
            newCluster.tiles.insert(coord);
            newCluster.number = clusters.size();
            clusters.push_back(newCluster);
            clusterNumber.at(coord) = newCluster.number;

            // explore neighbors
            std::set<HE::Coord::Axial> neighbors;
            neighbors.insert(coord + HE::Coord::Axial(1 ,0));
            neighbors.insert(coord + HE::Coord::Axial(-1,0));
            neighbors.insert(coord + HE::Coord::Axial(0 ,1));
            neighbors.insert(coord + HE::Coord::Axial(0,-1));
            neighbors.insert(coord + HE::Coord::Axial(1,-1));
            neighbors.insert(coord + HE::Coord::Axial(-1,1));

            std::set<HE::Coord::Axial> neighborsOfSameColor;
            for(auto& neighbor : neighbors)
            {
                auto itNeighbor = m_tiles.find(neighbor);
                if(itNeighbor != m_tiles.end() && itNeighbor->second.value == tile.value)
                {
                    neighborsOfSameColor.insert(neighbor);
                }
            }

            std::set<int> clustersToMerge;
            clustersToMerge.insert(clusterNumber.at(coord));
            for(auto& neighbor : neighborsOfSameColor)
            {
                if(clusterNumber.at(neighbor) == -1)
                {
                    clusterNumber.at(neighbor) = clusterNumber.at(coord);
                }
                else
                {
                    clustersToMerge.insert(clusterNumber.at(neighbor));

                }
            }

            if(clustersToMerge.size() > 1)
            {
                auto clusterIt = (clustersToMerge.begin())++;
                while(clusterIt != clustersToMerge.end())
                {
                    Cluster& clusterToMergeInto = clusters[*clustersToMerge.begin()];
                    Cluster& clusterToMergeFrom = clusters[*clusterIt];

                    for(auto tile : clusterToMergeFrom.tiles)
                    {
                        clusterNumber.at(tile) = clusterToMergeInto.number;
                        clusterToMergeInto.tiles.insert(tile);
                    }
                    clusterToMergeFrom.tiles.clear();
                    clusterIt++;
                }
            }
        }
    }


    std::cout<<"number of clusters: " << std::count_if(clusters.begin(), clusters.end(), [](const Cluster& c){return !c.tiles.empty();} );

    // Compute DF for each

    // Delete dead clusters
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



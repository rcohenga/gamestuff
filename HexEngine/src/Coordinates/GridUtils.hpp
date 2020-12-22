/*
 * GridUtils.hpp
 *
 *  Created on: Dec 22, 2020
 *      Author: raphael
 */

#ifndef HEXENGINE_SRC_COORDINATES_GRIDUTILS_HPP_
#define HEXENGINE_SRC_COORDINATES_GRIDUTILS_HPP_

#include <set>
#include <map>
#include <vector>
#include <functional>

#include "Axial.hpp"

namespace HE
{
template<class T>
std::set<Coord::Axial> getNeighbors(const Coord::Axial& coord, const std::map<Coord::Axial, T>& grid)
{
    std::set<Coord::Axial> neighbors;
    std::set<Coord::Axial> adjacencies = {
            {1,0},
            {-1,0},
            {0,1},
            {0,-1},
            {1,-1},
            {-1,1}
    };

    for(const auto& delta : adjacencies)
    {
        auto potentialNeighbor = coord + delta;
        if(grid.find(potentialNeighbor) != grid.end()) neighbors.insert(potentialNeighbor);
    }

    return neighbors;
}

template<class T>
void clusterize_aux(const Coord::Axial& currentTile,
        std::vector<std::set<Coord::Axial>>& clusters,
        std::map<Coord::Axial, bool>& hasBeenVisited,
        std::map<Coord::Axial, int>& clusterNumbers,
        const std::map<Coord::Axial, T> grid,
        std::function<bool(const T&, const T&)> isEquivalent)
{
    if(hasBeenVisited.at(currentTile))
    {
        return;
    }
    else
    {
        hasBeenVisited.at(currentTile) = true;
    }

    //std::cout<<"visiting " << currentTile.r()<<"\t"<<currentTile.q()<<"\n";

    if(clusterNumbers.at(currentTile) == -1)
    {
        clusters.emplace_back();
        auto& newCluster = clusters.back();
        newCluster.insert(currentTile);
        clusterNumbers.at(currentTile) = clusters.size() -1;
        //std::cout<<"\tcreated cluster" << clusterNumbers.at(currentTile)<<"\n";
    }

    auto neighbors = getNeighbors(currentTile, grid);

    for(const auto& neighbor : neighbors)
    {
        if(isEquivalent(grid.at(currentTile), grid.at(neighbor)))
        {
            clusterNumbers.at(neighbor) = clusterNumbers.at(currentTile);
            clusters[clusterNumbers.at(neighbor)].insert(neighbor);
            //std::cout<<"\tadding to cluster "<< clusterNumbers.at(neighbor) << "the tile " << neighbor.r()<<"\t"<<neighbor.q()<<"\n";
            clusterize_aux<T>(neighbor, clusters, hasBeenVisited, clusterNumbers, grid, isEquivalent);
        }
    }
}

template<class T>
std::vector<std::set<Coord::Axial>> clusterize(const std::map<Coord::Axial, T> grid, std::function<bool(const T&, const T&)> isEquivalent)
{
    std::vector<std::set<Coord::Axial>> clusters;

    if(!grid.empty())
    {
        std::map<Coord::Axial, int> clusterNumbers;
        std::map<Coord::Axial, bool> hasBeenVisited;
        for(const auto& [coord, tile] : grid)
        {

            clusterNumbers.emplace(coord, -1);
            hasBeenVisited.emplace(coord, false);
        }

        for(const auto& [coord, tile] : grid)
        {
            clusterize_aux<T>(coord, clusters, hasBeenVisited, clusterNumbers, grid, isEquivalent);
        }
    }

    std::vector<std::set<Coord::Axial>> nonEmptyClusters;
    for(const auto& cluster : clusters)
    {
        if(!cluster.empty())
        {
            nonEmptyClusters.push_back(cluster);
        }
    }

    return nonEmptyClusters;
}

} // namespace HE



#endif /* HEXENGINE_SRC_COORDINATES_GRIDUTILS_HPP_ */

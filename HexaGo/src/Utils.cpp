/*
 * Utils.cpp
 *
 *  Created on: Dec 23, 2020
 *      Author: raphael
 */


#include "Utils.hpp"


namespace HexaGo
{
    EPlayer valueToPlayer(Tile::EValue value)
    {
        if(value == Tile::EValue::Black) return EPlayer::Black;
        else return EPlayer::White;
    }

    Tile::EValue playerToValue(EPlayer player)
    {
        if(player == EPlayer::Black) return Tile::EValue::Black;
        else return Tile::EValue::White;
    }

    EPlayer otherPlayer(EPlayer player)
    {
        return (player == EPlayer::Black ? EPlayer::White : EPlayer::Black);
    }

    std::string toString(EPlayer player)
    {
        switch(player)
        {
        case(EPlayer::Black): return "Black";
        case(EPlayer::White): return "White";
        default: return "";
        }
    }

    std::string toString(Tile::EValue value)
    {
        switch(value)
        {
        case(Tile::EValue::Black): return "Black";
        case(Tile::EValue::Empty): return "Empty";
        case(Tile::EValue::White): return "White";
        default: return "";
        }
    }
}

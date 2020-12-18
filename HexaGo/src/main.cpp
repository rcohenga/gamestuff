/*
 * main.cpp
 *
 *  Created on: Dec 13, 2020
 *      Author: raphael
 */


#include <iostream>

#include "Axial.hpp"

#include "Model.hpp"
#include "View.hpp"

int main()
{
//    HE::Coord::Axial a(0,2), b;
//
//    std::cout<<(a == b ? "equal" : "different") <<"\n";


    auto p_model = std::make_shared<HexaGo::Model>(8);
    auto p_view  = std::make_shared<HexaGo::View>(p_model);
    p_view->start();
}

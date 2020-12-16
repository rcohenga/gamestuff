/*
 * main.cpp
 *
 *  Created on: Dec 13, 2020
 *      Author: raphael
 */


#include <iostream>

#include "Model.hpp"
#include "View.hpp"

int main()
{
    auto p_model = std::make_shared<HexaGo::Model>(5);
    auto p_view  = std::make_shared<HexaGo::View>(p_model);
    p_view->start();

}

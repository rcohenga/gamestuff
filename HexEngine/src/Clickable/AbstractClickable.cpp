/*
 * AbstractClickable.cpp
 *
 *  Created on: Nov 28, 2020
 *      Author: raphael
 */

#include "AbstractClickable.hpp"


void AbstractClickable::onMouseEvent(IClickable::EMouseEventType eventType)
{
    auto it = _callbacks.find(eventType);
    if(it != _callbacks.end())
    {
        it->second();
    }
}

void AbstractClickable::setCallback(IClickable::EMouseEventType eventType, std::function<void(void)> callback)
{
    _callbacks.emplace(eventType, callback);
}

/*
 * Clickable.hpp
 *
 *  Created on: Nov 25, 2020
 *      Author: raphael
 */

#ifndef SRC_ICLICKABLE_HPP_
#define SRC_ICLICKABLE_HPP_

#include <functional>

#include <SFML/Graphics.hpp>

#include "IClickable.hpp"



class IClickable
{
public:
    enum class EMouseEventType
    {
        RightClick,
        RightRelease,

        LeftClick,
        LeftRelease,

        MiddleClick,
        MiddleRelease,

        Hover,
        HoverRelease
    };
public:
    virtual bool isInside(sf::Vector2f) const = 0;
    virtual void onMouseEvent(EMouseEventType) = 0;
    virtual void setCallback(EMouseEventType, std::function<void(void)>) = 0;

    virtual ~IClickable(){};
};



#endif /* SRC_ICLICKABLE_HPP_ */

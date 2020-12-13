/*
 * AbstractClickable.hpp
 *
 *  Created on: Nov 28, 2020
 *      Author: raphael
 */

#ifndef SRC_ABSTRACTCLICKABLE_HPP_
#define SRC_ABSTRACTCLICKABLE_HPP_

#include <map>

#include "IClickable.hpp"


class AbstractClickable : public IClickable
{
public:
    void onMouseEvent(EMouseEventType) override;
    void setCallback(EMouseEventType, std::function<void(void)>) override;

private:
    std::map<IClickable::EMouseEventType, std::function<void(void)>> _callbacks;
};



#endif /* SRC_ABSTRACTCLICKABLE_HPP_ */

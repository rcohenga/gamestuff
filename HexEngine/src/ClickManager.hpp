/*
 * ClickManager.hpp
 *
 *  Created on: Nov 28, 2020
 *      Author: raphael
 */

#ifndef SRC_CLICKMANAGER_HPP_
#define SRC_CLICKMANAGER_HPP_

#include <set>

#include "SFML/Graphics.hpp"

#include "IClickable.hpp"

class ClickManager
{
public:
    ClickManager(sf::Window& window):
        _window(window)
        ,_currentHover(nullptr)
    {
        for(int ibutton = 0 ; ibutton < (int)sf::Mouse::ButtonCount; ibutton++)
        {
            auto button = static_cast<sf::Mouse::Button>(ibutton);
            _isPressed.emplace(button, sf::Mouse::isButtonPressed(button));
        }
    }


    void addClickable(IClickable* clickable){_clickables.insert(clickable);};
    void remCliclable(IClickable* clickable){_clickables.erase(clickable);};


    void mouseEvent(const sf::Event& event)
    {
        // resolve which (if any) clickable was clicked
        IClickable* iv_clicked = nullptr;

        for(IClickable* ivp_clickable : _clickables)
        {
            if(ivp_clickable->isInside(sf::Vector2f(sf::Mouse::getPosition(_window).x, sf::Mouse::getPosition(_window).y)))
            {
                iv_clicked = ivp_clickable;
            }
        }



        if(true)
        {
            switch(event.type)
            {
            case sf::Event::MouseMoved:
            {
                std::cout<<"MouseMoved\n";
                sf::Vector2f mousePosition(sf::Mouse::getPosition(_window).x, sf::Mouse::getPosition(_window).y);
                if(_currentHover)
                {
                    if(!_currentHover->isInside(mousePosition))
                    {
                        _currentHover->onMouseEvent(IClickable::EMouseEventType::HoverRelease);
                        _currentHover = nullptr;
                    }
                }

                if(iv_clicked && !_currentHover)
                {
                    _currentHover = iv_clicked;
                    iv_clicked->onMouseEvent(IClickable::EMouseEventType::Hover);
                }

                break;
            }

            case sf::Event::MouseButtonReleased:
            {

                std::cout<<"MouseButtonReleased\n";
                std::set<sf::Mouse::Button> newlyReleasedButtons;
                for(int ibutton = 0; ibutton < (int)sf::Mouse::ButtonCount; ibutton++)
                {
                    auto button = static_cast<sf::Mouse::Button>(ibutton);
                    std::cout<<"button " << ibutton << " " << (sf::Mouse::isButtonPressed(button) ? "pressed" : "not pressed") <<"\n";
                    if(_isPressed.at(button) != sf::Mouse::isButtonPressed(button))
                    {
                        newlyReleasedButtons.insert(button);
                        _isPressed.at(button) = !_isPressed.at(button);
                    }
                }
                break;
            }

            case sf::Event::MouseButtonPressed:
            {
                std::cout<<"MouseButtonPressed\n";
                std::set<sf::Mouse::Button> newlyPressedButtons;
                for(int ibutton = 0; ibutton < (int)sf::Mouse::ButtonCount; ibutton++)
                {
                    auto button = static_cast<sf::Mouse::Button>(ibutton);
                    std::cout<<"button " << ibutton << " " << (sf::Mouse::isButtonPressed(button) ? "pressed" : "not pressed") <<"\n";
                    if(_isPressed.at(button) != sf::Mouse::isButtonPressed(button))
                    {
                        newlyPressedButtons.insert(button);
                        _isPressed.at(button) = !_isPressed.at(button);
                    }
                }

                for(sf::Mouse::Button button : newlyPressedButtons)
                {
                    switch(button)
                    {
                    case sf::Mouse::Left:
                        if(iv_clicked)
                        {
                            iv_clicked->onMouseEvent(IClickable::EMouseEventType::LeftClick);
                        }
                        std::cout<<"left click\n";
                        break;
                    case sf::Mouse::Right:
                        std::cout<<"right click\n";
                        if(iv_clicked)
                        {
                            iv_clicked->onMouseEvent(IClickable::EMouseEventType::RightClick);
                        }
                        break;
                    }
                }
                break;
            }

            default:
                break;
            }
        }
    }

public:
    std::set<IClickable*> _clickables;
private:
    sf::Window& _window;
    std::map<sf::Mouse::Button, bool> _isPressed;
    //sf::Vector2i _mousePosition;
    IClickable* _currentHover;
};



#endif /* SRC_CLICKMANAGER_HPP_ */

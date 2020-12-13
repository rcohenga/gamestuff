#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <set>

//class Hex;

#include "Hex.hpp"
#include "ClickManager.hpp"



int main()
{



    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");


    Hex hex;
    hex.setCenter(sf::Vector2f(100,100));
    hex.setRadius(10);
    hex.getShape().setFillColor(sf::Color::White);

    hex.setCallback(IClickable::EMouseEventType::LeftClick ,[&hex](){hex.setRadius(hex.getRadius() * 1.1);});
    hex.setCallback(IClickable::EMouseEventType::RightClick,[&hex](){hex.setRadius(hex.getRadius() / 1.1);});
    hex.setCallback(IClickable::EMouseEventType::Hover,[&hex](){hex.getShape().setFillColor(sf::Color::Red);});
    hex.setCallback(IClickable::EMouseEventType::HoverRelease,[&hex](){hex.getShape().setFillColor(sf::Color::White);});

    ClickManager iv_clickManager(window);
    iv_clickManager.addClickable(&hex);

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        int nbEvents = 0;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            switch(event.type)
            {
            case(sf::Event::Closed):
                window.close();
                break;
            case(sf::Event::MouseButtonPressed):
            case(sf::Event::MouseButtonReleased):
            case(sf::Event::MouseMoved):
                iv_clickManager.mouseEvent(event);
                break;
            default:
                break;
            }
        }

        sf::Vector2f delta;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))  delta +=  sf::Vector2f(0,1);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))    delta +=  sf::Vector2f(0,-1);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))  delta +=  sf::Vector2f(-1,0);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) delta +=  sf::Vector2f(1,0);

        //shape.setPosition(shape.getPosition() + sf::Vector2f(0.1 * delta.x,0.1 * delta.y));
        hex.setCenter(hex.getCenter() + sf::Vector2f(0.1 * delta.x,0.1 * delta.y));

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        // window.draw(...);

        //window.draw(shape);
        window.draw(hex.getShape());


        // end the current frame
        window.display();
    }

    return 0;
}

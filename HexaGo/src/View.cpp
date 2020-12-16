/*
 * View.cpp
 *
 *  Created on: Dec 15, 2020
 *      Author: raphael
 */

#include <tuple>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "ClickManager.hpp"
#include "Hex.hpp"

#include "View.hpp"

namespace HexaGo
{

View::View(std::shared_ptr<Model> model):
        m_model(model)
{

};


void View::start()
{
    // create the window

    unsigned int width = 800;
    unsigned int height = 600;
    unsigned int radius = 30;


    sf::RenderWindow window(sf::VideoMode(width, height), "My window");
    ClickManager iv_clickManager(window);

    sf::Vector2f middle(width/2, height/2);

    std::map<AxialCoord, Hex> iv_hexes;
    for(const auto& [coord, tile] : m_model->getTiles())
    {
        std::get<0>(coord);
        Hex hex;
        hex.setCenter(middle
                + sf::Vector2f(2 * radius * (float)std::get<0>(coord)                     , 0)
                + sf::Vector2f(2 * radius * (float)std::get<1>(coord) * Geometry::cos(1,3), 2 * radius * (float)std::get<1>(coord) * Geometry::sin(1,3)));
        hex.setOrientation(Hex::EOrientation::Pointy);
        hex.setRadius(radius);
        hex.getShape().setFillColor(sf::Color::Yellow);
        hex.getShape().setOutlineColor(sf::Color::Black);
        hex.getShape().setOutlineThickness(1);

        std::cout<< std::get<0>(coord) << ";" << std::get<1>(coord) << "=>" << hex.getCenter().x <<";" << hex.getCenter().y<<"\n";

        iv_hexes.emplace(coord, hex);
    }

    for(auto& [coord, hex] : iv_hexes)
    {
        auto coordCopy = coord;
        hex.setCallback(IClickable::EMouseEventType::LeftClick,[this, coordCopy](){this->m_model->layTile(coordCopy);});
        hex.setCallback(IClickable::EMouseEventType::RightClick,[&hex](){
            hex.setOrientation(static_cast<Hex::EOrientation>(1-static_cast<int>(hex.getOrientation())));
        });
        iv_clickManager.addClickable(&hex);
    }

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

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        // window.draw(...);

        //window.draw(shape);
        for(auto& [coord, hex] : iv_hexes)
        {
            sf::Color iv_hexColor;
            switch(m_model->getTiles().at(coord).value)
            {
            case Tile::EValue::Empty:
                iv_hexColor = sf::Color::Yellow;
                break;
            case Tile::EValue::Black:
                iv_hexColor = sf::Color::Blue;
                break;
            case Tile::EValue::White:
                iv_hexColor = sf::Color::White;
                break;
            default:
                break;
            }

            hex.getShape().setFillColor(iv_hexColor);
            window.draw(hex.getShape());
        }


        // end the current frame
        window.display();
    }
}


}


/*
 * View.cpp
 *
 *  Created on: Dec 15, 2020
 *      Author: raphael
 */

#include <tuple>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

//HexEngine
#include "Axial.hpp"

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
    unsigned int radius = 20;


    sf::RenderWindow window(sf::VideoMode(width, height), "My window");
    ClickManager iv_clickManager(window);

    sf::Vector2f middle(width/2, height/2);

    std::map<HE::Coord::Axial, Hex> iv_hexes;
    for(const auto& [coord, tile] : m_model->getTiles())
    {
        Hex hex;
        hex.setCenter(middle
                + sf::Vector2f(2 * radius * (float)coord.r()                     , 0)
                + sf::Vector2f(2 * radius * (float)coord.q() * Geometry::cos(1,3), 2 * radius * (float)coord.q() * Geometry::sin(1,3)));
        hex.setOrientation(Hex::EOrientation::Pointy);
        hex.setRadius(radius);
        hex.getShape().setFillColor(sf::Color::Yellow);
        hex.getShape().setOutlineColor(sf::Color::Black);
        hex.getShape().setOutlineThickness(1);

        //std::cout<< coord.r() << ";" << coord.q() << "=>" << hex.getCenter().x <<";" << hex.getCenter().y<<"\n";

        iv_hexes.emplace(coord, hex);
    }

    // hover stuff
    m_tileOnHover.currentlyHovering = false;


    for(auto& [coord, hex] : iv_hexes)
    {
        auto coordCopy = coord;
        hex.setCallback(IClickable::EMouseEventType::LeftClick,[this, coordCopy](){this->m_model->layTile(coordCopy);});
        hex.setCallback(IClickable::EMouseEventType::RightClick,[&hex](){
            hex.setOrientation(static_cast<Hex::EOrientation>(1-static_cast<int>(hex.getOrientation())));
        });
        hex.setCallback(IClickable::EMouseEventType::Hover,[this, coordCopy](){this->m_tileOnHover.currentlyHovering = true ; m_tileOnHover.coord = coordCopy;});
        hex.setCallback(IClickable::EMouseEventType::HoverRelease,[this](){this->m_tileOnHover.currentlyHovering = false;});

        iv_clickManager.addClickable(&hex);
    }

    // run the program as long as the window is open
    float blackScore = m_model->getScore(EPlayer::Black);
    float whiteScore = m_model->getScore(EPlayer::White);

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
            case(sf::Event::KeyPressed):
                    if(event.key.code == sf::Keyboard::Key::Z)
                    {
                        std::cout<<"Z pressed\n";
                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl))
                        {
                            std::cout<<"LControl pressed\n";
                            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
                            {
                                std::cout<<"LShift pressed\n";
                                m_model->unReverse();
                            }
                            else
                            {
                                m_model->reverse();
                            }
                        }
                    }
                break;
            default:
                break;
            }
        }


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

        // hover
        if(m_tileOnHover.currentlyHovering)
        {
            //std::cout<<"currently hovering over " << m_tileOnHover.coord.r() << "\t" << m_tileOnHover.coord.q()<<"\n";
            if(m_model->getTiles().at(m_tileOnHover.coord).value == Tile::EValue::Empty)
            {

                auto& hexShape = iv_hexes.at(m_tileOnHover.coord).getShape();
                hexShape.setFillColor(m_model->getCurrentPlayer() ==
                        EPlayer::Black ? sf::Color::Blue : sf::Color::White);

                window.draw(hexShape);
            }
        }


        if(m_model->getScore(EPlayer::Black) != blackScore || m_model->getScore(EPlayer::White) != whiteScore)
        {
            blackScore = m_model->getScore(EPlayer::Black);
            whiteScore = m_model->getScore(EPlayer::White);

            std::cout<<"Black\t"<<m_model->getScore(EPlayer::Black)<<"\n";
            std::cout<<"White\t"<<m_model->getScore(EPlayer::White)<<"\n";
        }

        // end the current frame
        window.display();
    }
}


}



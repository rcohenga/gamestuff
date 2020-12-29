/*
 * main.cpp
 *
 *  Created on: Dec 24, 2020
 *      Author: raphael
 */
#include <chrono>
#include <thread>
#include <iostream>
#include <cstring>

#include "SFML/Network.hpp"

int main()
{
    std::cout<<"server poc\n";

    sf::TcpListener listener;


    int port = 53001;
    int nbAttempts = 0;
    // bind the listener to a port
    while(listener.listen(port) != sf::Socket::Done)
    {
        std::cout<<"error... " << nbAttempts++ << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    std::cout<<"listener bound to port " << port<<"\n";


    // accept a new connection
    sf::TcpSocket client;
    if (listener.accept(client) != sf::Socket::Done)
    {
        // error...
        std::cout<<"unspecified connection error\n";
    }
    else
    {
        std::cout<<"connection established...\n";
    }

    while(true)
    {
        sf::Packet packet;

        if(client.receive(packet) != sf::Socket::Done)
        {
            std::cout<<"Error receiving data\n";
        }
        else
        {
            sf::Int32 i;
            packet >> i;
            std::cout<<"received " << i <<  "\n";

            std::this_thread::sleep_for(std::chrono::milliseconds(100));

            i++;
            sf::Packet newPacket;
            newPacket >> i;
            if(client.send(newPacket) != sf::Socket::Done)
            {
                std::cout<<"Error sending data\n";
            }
            else
            {
                std::cout<<"sent " << i <<"\n";
            }
        }
    }


}


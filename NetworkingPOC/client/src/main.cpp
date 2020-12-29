/*
 * main.cpp
 *
 *  Created on: Dec 24, 2020
 *      Author: raphael
 */

#include <chrono>
#include <thread>
#include <iostream>

#include "SFML/Network.hpp"

int main()
{
    std::cout<<"networking poc\n";

    sf::TcpSocket socket;
    sf::Socket::Status status;

    //std::string ip = "192.168.0.5";
    std::string ip = "0.0.0.0";
    int port = 53001;


    do
    {
        std::cout<<"try connect to " << ip<<":"<<port<<"\n";
        status = socket.connect(ip, port);

        if(status != sf::Socket::Done)
        {
            std::cout<<"connected!\n";
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    while (status != sf::Socket::Done);

    sf::Packet initial;
    int i = 0;

    initial << sf::Int32(0);
    std::cout<<"sending " << i <<"\n";
    socket.send(initial);

    while(true)
    {
        std::cout<<"Client is connected... ";
        sf::Packet packet;
        if(socket.receive(packet) != sf::Socket::Done)
        {
            std::cout<<"Error receiving data\n";
        }
        else
        {
            packet >> i;
            std::cout<<"received data "<<i<<"\n";

            std::this_thread::sleep_for(std::chrono::milliseconds(100));

            i++;
            sf::Packet newPacket;
            newPacket << i;
            if(socket.send(newPacket) != sf::Socket::Done)
            {
                std::cout<<"Error sending data\n";
            }
            else
            {
                std::cout<<"successfully sent " << i <<"\n";
            }
        }
    }
}

